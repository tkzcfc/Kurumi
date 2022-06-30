#include "GFightService.h"

// 战斗服务

const char* FIGHT_SVR_IP_KEY = "ip";
const char* FIGHT_SVR_PORT_KEY = "port";


uint32_t GFightService::onInit()
{
	m_applyGroupSeed = 0;

	G_CHECK_SERVICE(GNetService);
	G_CHECK_SERVICE(GMasterNodeService);
	G_CHECK_SERVICE(GRoleMngService);
	G_CHECK_SERVICE(GPlayerMngService);

	m_pNetService = m_serviceMgr->getService<GNetService>();
	m_pMasterNodeService = m_serviceMgr->getService<GMasterNodeService>();
	m_pPlayerMngService = m_serviceMgr->getService<GPlayerMngService>();
	m_pRoleMngService = m_serviceMgr->getService<GRoleMngService>();

	ON_PB_MSG_CLASS_CALL(m_pMasterNodeService->noticeCenter(), svr_msg::NewFightAck, onMsg_NewFightAck);

	ON_PB_MSG_CLASS_CALL(m_pNetService->noticeCenter(), msg::StartPVEFightReq, onMsg_StartPVEFightReq);
	ON_PB_MSG_CLASS_CALL(m_pNetService->noticeCenter(), msg::StartPVPFightReq, onMsg_StartPVPFightReq);
	ON_PB_MSG_CLASS_CALL(m_pNetService->noticeCenter(), msg::StopPVPMatchReq, onMsg_StopPVPMatchReq);

	GApplication::getInstance()->getScheduler()->schedule(std::bind(&GFightService::onUpdate_PVPCheck, this, std::placeholders::_1), this, 0.5f, false, "pvp_check");

	return SCODE_START_SUCCESS;
}

void GFightService::onUpdate(float)
{}

const SlaveNodeInfo* GFightService::getFightSvr()
{
	const auto& nodes = m_pMasterNodeService->arrSlaveNodInfos();
	if (nodes.empty())
		return NULL;

	const SlaveNodeInfo* pNode = &nodes[std::rand() % nodes.size()];

	if (pNode->infoJson.HasMember(FIGHT_SVR_IP_KEY) && 
		pNode->infoJson.HasMember(FIGHT_SVR_PORT_KEY) && 
		pNode->infoJson.FindMember(FIGHT_SVR_IP_KEY)->value.GetType() == rapidjson::Type::kStringType &&
		pNode->infoJson.FindMember(FIGHT_SVR_PORT_KEY)->value.GetType() == rapidjson::Type::kNumberType)
	{
		return pNode;
	}
	LOG(ERROR) << "[GFightService] GlaveNodeInfo config err: " << pNode->info;
	return NULL;
}

int32_t GFightService::newFightGroup(ROLE_ID* arrRole, int32_t roleCount, int32_t fightType)
{
	m_applyGroupSeed++;

	FightApplyGroup group;
	memset(&group, 0, sizeof(group));
	group.time = ::time(NULL);
	group.count = roleCount;
	group.fightType = fightType;

	for (auto i = 0; i < roleCount; ++i)
	{
		group.roleid[i] = arrRole[i];
	}

	m_applyGroupMap[m_applyGroupSeed] = group;

	return m_applyGroupSeed;
}

GFightService::FightApplyGroup* GFightService::getRoleApplyGroup(ROLE_ID roleid, int32_t fightType)
{
	for (auto& it : m_applyGroupMap)
	{
		if (it.second.fightType == fightType)
		{
			for (auto i = 0; i < it.second.count; ++i)
			{
				if (it.second.roleid[i] == roleid)
					return &it.second;
			}
		}
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GFightService::onMsg_NewFightAck(uint32_t sessionID, const svr_msg::NewFightAck& msg)
{
	auto it = m_applyGroupMap.find(msg.tag());
	if (it == m_applyGroupMap.end())
	{
		return;
	}

	SlaveNodeInfo* slaveInfo = m_pMasterNodeService->getSlaveNodeInfo(sessionID);

	msg::StartFightNTF ntf;
	if (slaveInfo == NULL)
	{
		ntf.set_code(err::Code::FIGHT_SVR_NOT_FOUND);
	}
	else
	{
		ntf.set_code(msg.code());
		if (msg.code() == err::Code::SUCCESS)
		{
			ntf.set_nettype(msg.nettype());
			ntf.set_fightuuid(msg.uuid());
			ntf.set_fightip(slaveInfo->infoJson.FindMember(FIGHT_SVR_IP_KEY)->value.GetString());
			ntf.set_fightport(slaveInfo->infoJson.FindMember(FIGHT_SVR_PORT_KEY)->value.GetInt());
		}
	}

	// 推送玩家信息到客户端
	for (auto i = 0; i < it->second.count; ++i)
	{
		auto role = m_pRoleMngService->getRole(it->second.roleid[i]);
		if (role)
		{
			for (auto j = 0; j < it->second.count; ++j)
			{
				auto curRole = m_pRoleMngService->getRole(it->second.roleid[j]);
				m_pPlayerMngService->sendRoleInfoToPlayer(role->getPlayer(), curRole);
			}
		}
	}

	// 向客户端发送开始战斗通知
	for (auto i = 0; i < it->second.count; ++i)
	{
		auto role = m_pRoleMngService->getRole(it->second.roleid[i]);
		if (role)
		{
			SEND_PB_MSG(m_pNetService, role->getSessionID(), ntf);
		}
	}

	m_applyGroupMap.erase(msg.tag());
}

void GFightService::onMsg_StartPVEFightReq(uint32_t sessionID, const msg::StartPVEFightReq& msg)
{
	auto pRole = m_pPlayerMngService->getRoleBySessionID(sessionID);
	G_CHECK_NULL_RETURN(pRole);

	// 分配战斗服
	auto fightNode = getFightSvr();

	msg::StartPVEFightAck ack;
	if (msg.roles_size() <= 0)
	{
		ack.set_code(err::Code::ROLE_NOT_EXIST);
	}
	else
	{
		if (fightNode == NULL)
		{
			ack.set_code(err::Code::FIGHT_SVR_NONE);
		}
		else
		{
			ack.set_code(err::Code::SUCCESS);
		}

		for (auto i = 0; i < msg.roles_size(); ++i)
		{
			if (m_pRoleMngService->getRole(msg.roles().Get(i).roleid()) == NULL)
			{
				ack.set_code(err::Code::ROLE_NOT_EXIST);
				break;
			}
		}
	}
	SEND_PB_MSG(m_pNetService, sessionID, ack);

	if (ack.code() != err::Code::SUCCESS)
		return;

	ROLE_ID* arrRoles = new ROLE_ID[msg.roles_size()];
	for (auto i = 0; i < msg.roles_size(); ++i)
	{
		arrRoles[i] = msg.roles().Get(i).roleid();
	}

	auto groupId = newFightGroup(arrRoles, msg.roles_size(), FightType::FIGHT_PVE);
	
	// 提交新建战斗请求
	svr_msg::NewFightReq req;
	req.set_tag(groupId);
	req.set_mapid(msg.carbonid());
	req.set_fighttype(FightType::FIGHT_PVE);
	req.set_isofflinemode(msg.isofflinemode());

	for (auto i = 0; i < msg.roles_size(); ++i)
	{
		auto pRoleInfo = m_pRoleMngService->getRole(msg.roles().Get(i).roleid());
		
		auto pRole = req.add_roles();
		pRole->set_roleid(pRoleInfo->getRoleId());
		pRole->set_occ(pRoleInfo->getOcc());
	}
	SEND_PB_MSG(m_pMasterNodeService, fightNode->sessionID, req);
}

void GFightService::onMsg_StartPVPFightReq(uint32_t sessionID, const msg::StartPVPFightReq& msg)
{
	auto pRole = m_pPlayerMngService->getRoleBySessionID(sessionID);
	G_CHECK_NULL_RETURN(pRole);
	
	if (getRoleApplyGroup(pRole->getRoleId(), FightType::FIGHT_PVP) != NULL)
	{
		// 通知客户端匹配成功
		msg::StartPVPFightAck ack;
		ack.set_code(err::Code::PVP_MATCH_SUC);
		SEND_PB_MSG(m_pNetService, sessionID, ack);
		return;
	}

	m_pvpSet.insert(pRole->getRoleId());

	// 通知客户端匹配中
	msg::StartPVPFightAck ack;
	ack.set_code(err::Code::PVP_MATCHING);
	SEND_PB_MSG(m_pNetService, sessionID, ack);
}

void GFightService::onMsg_StopPVPMatchReq(uint32_t sessionID, const msg::StopPVPMatchReq& msg)
{
	auto pRole = m_pPlayerMngService->getRoleBySessionID(sessionID);
	G_CHECK_NULL_RETURN(pRole);

	if (m_pvpSet.count(pRole->getRoleId()) == 0)
	{
		// 已经匹配了
		bool find = false;
		for (auto it = m_applyGroupMap.begin(); it != m_applyGroupMap.end(); ++it)
		{
			for (auto i = 0; i < it->second.count; ++i)
			{
				if (it->second.roleid[i] == pRole->getRoleId())
				{
					find = true;
					break;
				}
			}

			if (find)
			{
				for (auto i = 0; i < it->second.count; ++i)
				{
					if (it->second.roleid[i] != pRole->getRoleId())
					{
						auto pRoleInfo = m_pRoleMngService->getRole(it->second.roleid[i]);
						if (pRoleInfo)
						{
							// 通知其他玩家对手取消匹配
							msg::StartPVPFightAck ack;
							ack.set_code(err::Code::PVP_RIVAL_EXIT);
							SEND_PB_MSG(m_pNetService, pRoleInfo->getSessionID(), ack);
						}
					}
				}
				// 删除该组
				m_applyGroupMap.erase(it);
				break;
			}
		}
	}
	else
	{
		m_pvpSet.erase(pRole->getRoleId());
	}

	// 通知客户端取消成功
	msg::StopPVPMatchAck ack;
	ack.set_code(err::Code::SUCCESS);
	SEND_PB_MSG(m_pNetService, sessionID, ack);
}

void GFightService::onUpdate_PVPCheck(float dt)
{
	if (m_pvpSet.empty())
		return;

	// 清理离线玩家
	do
	{
		bool tag = true;

		for (auto it = m_pvpSet.begin(); it != m_pvpSet.end(); )
		{
			auto pRole = m_pRoleMngService->getRole(*it);
			if (pRole == NULL || pRole->getIsOnline() == false)
			{
				m_pvpSet.erase(pRole->getRoleId());
				tag = false;
				break;
			}
			else
			{
				++it;
			}
		}

		if (tag) break;
	} while (true);
	
	// 匹配战斗
	while (m_pvpSet.size() > 1)
	{
		auto p1 = *m_pvpSet.begin();
		m_pvpSet.erase(p1);

		auto p2 = *m_pvpSet.begin();
		m_pvpSet.erase(p2);

		const auto roleCount = 2;
		ROLE_ID arrRole[roleCount] = { p1, p2 };
		
		// 分配战斗服
		msg::StartPVPFightAck ack;
		auto fightNode = getFightSvr();
		if (fightNode == NULL)
		{
			ack.set_code(err::Code::PVP_MATCH_SUC_NO_SVR);
		}
		else
		{
			ack.set_code(err::Code::PVP_MATCH_SUC);
		}

		for (auto i = 0; i < roleCount; ++i)
		{
			auto pRoleInfo = m_pRoleMngService->getRole(arrRole[i]);
			SEND_PB_MSG(m_pNetService, pRoleInfo->getSessionID(), ack);
		}

		if (fightNode)
		{
			// 玩家分组
			auto groupId = newFightGroup(arrRole, roleCount, FightType::FIGHT_PVP);

			// 提交新建战斗请求
			svr_msg::NewFightReq req;
			req.set_tag(groupId);
			req.set_mapid(1);
			req.set_fighttype(FightType::FIGHT_PVP);
			req.set_isofflinemode(false);

			for (auto i = 0; i < roleCount; ++i)
			{
				auto pRole = req.add_roles();
				auto pRoleInfo = m_pRoleMngService->getRole(arrRole[i]);
				{
					pRole->set_roleid(pRoleInfo->getRoleId());
					pRole->set_occ(pRoleInfo->getOcc());
				}
			}
			SEND_PB_MSG(m_pMasterNodeService, fightNode->sessionID, req);
		}
	}
}