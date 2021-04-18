#include "GFightService.h"

// 战斗服务

const char* FIGHT_SVR_IP_KEY = "ip";
const char* FIGHT_SVR_PORT_KEY = "port";


uint32_t GFightService::onInit()
{
	m_applyGroupSeed = 0;

	G_CHECK_SERVICE(GNetService);
	G_CHECK_SERVICE(GMasterNodeService);
	G_CHECK_SERVICE(GPlayerMngService);

	m_pNetService = m_serviceMgr->getService<GNetService>();
	m_pMasterNodeService = m_serviceMgr->getService<GMasterNodeService>();
	m_pPlayerMngService = m_serviceMgr->getService<GPlayerMngService>();

	ON_PB_MSG_CLASS_CALL(m_pMasterNodeService->noticeCenter(), MessageID::MSG_NEW_FIGHT_ACK, svr_msg::NewFightAck, onMsg_NewFightAck);

	ON_PB_MSG_CLASS_CALL(m_pNetService->noticeCenter(), MessageID::MSG_START_PVE_REQ, msg::StartPVEFightReq, onMsg_StartPVEFightReq);
	ON_PB_MSG_CLASS_CALL(m_pNetService->noticeCenter(), MessageID::MSG_START_PVP_REQ, msg::StartPVPFightReq, onMsg_StartPVPFightReq);
	ON_PB_MSG_CLASS_CALL(m_pNetService->noticeCenter(), MessageID::MSG_STOP_PVP_REQ, msg::Null, onMsg_StopPVPFightReq);

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

int32_t GFightService::newFightGroup(PLAYER_ID* arrPlayer, int32_t playerCount, int32_t fightType)
{
	m_applyGroupSeed++;

	FightApplyGroup group;
	memset(&group, 0, sizeof(group));
	group.time = ::time(NULL);
	group.count = playerCount;
	group.fightType = fightType;

	for (auto i = 0; i < playerCount; ++i)
	{
		group.playerid[i] = arrPlayer[i];
	}

	m_applyGroupMap[m_applyGroupSeed] = group;

	return m_applyGroupSeed;
}

GFightService::FightApplyGroup* GFightService::getPlayerApplyGroup(PLAYER_ID playerId)
{
	for (auto& it : m_applyGroupMap)
	{
		for (auto i = 0; i < it.second.count; ++i)
		{
			if (it.second.playerid[i] == playerId)
				return &it.second;
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
			ntf.set_fightuuid(msg.uuid());
			ntf.set_fightip(slaveInfo->infoJson.FindMember(FIGHT_SVR_IP_KEY)->value.GetString());
			ntf.set_fightport(slaveInfo->infoJson.FindMember(FIGHT_SVR_PORT_KEY)->value.GetInt());
		}
	}

	for (auto i = 0; i < it->second.count; ++i)
	{
		auto player = m_pPlayerMngService->getPlayer(it->second.playerid[i]);
		if (player)
		{
			SEND_PB_MSG(m_pNetService, player->getSessionID(), MessageID::MSG_START_FIGHT_NTF, ntf);
		}
	}
}

void GFightService::onMsg_StartPVEFightReq(uint32_t sessionID, const msg::StartPVEFightReq& msg)
{
	auto player = m_pPlayerMngService->getPlayerBySessionID(sessionID);
	G_CHECK_NULL_RETURN(player);

	// 分配战斗服
	auto fightNode = getFightSvr();

	msg::StartPVEFightAck ack;
	if (fightNode == NULL)
	{
		ack.set_code(err::Code::FIGHT_SVR_NONE);
	}
	else
	{
		ack.set_code(err::Code::SUCCESS);
	}
	SEND_PB_MSG(m_pNetService, sessionID, MessageID::MSG_START_PVE_ACK, ack);

	auto playerId = player->getPlayerId();
	auto groupId = newFightGroup(&playerId, 1, FightType::FIGHT_PVE);
	
	// 提交新建战斗请求
	svr_msg::NewFightReq req;
	req.set_tag(groupId);
	req.set_mapid(msg.carbonid());
	req.set_fighttype(FightType::FIGHT_PVE);

	auto reqPlayer = req.add_players();
	reqPlayer->set_playerid(playerId);

	SEND_PB_MSG(m_pMasterNodeService, fightNode->sessionID, MessageID::MSG_NEW_FIGHT_REQ, req);
}

void GFightService::onMsg_StartPVPFightReq(uint32_t sessionID, const msg::StartPVPFightReq& msg)
{
	auto player = m_pPlayerMngService->getPlayerBySessionID(sessionID);
	G_CHECK_NULL_RETURN(player);

	if (getPlayerApplyGroup(player->getPlayerId()) != NULL)
	{
		// 通知客户端匹配成功
		msg::StartPVPFightAck ack;
		ack.set_code(err::Code::PVP_MATCH_SUC);
		SEND_PB_MSG(m_pNetService, sessionID, MessageID::MSG_START_PVP_ACK, ack);
		return;
	}

	m_pvpSet.insert(player->getPlayerId());

	// 通知客户端匹配中
	msg::StartPVPFightAck ack;
	ack.set_code(err::Code::PVP_MATCHING);
	SEND_PB_MSG(m_pNetService, sessionID, MessageID::MSG_START_PVP_ACK, ack);
}

void GFightService::onMsg_StopPVPFightReq(uint32_t sessionID, const msg::Null& msg)
{
	auto player = m_pPlayerMngService->getPlayerBySessionID(sessionID);
	G_CHECK_NULL_RETURN(player);

	if (m_pvpSet.count(player->getPlayerId()) == 0)
	{
		// 已经匹配了
		bool find = false;
		for (auto it = m_applyGroupMap.begin(); it != m_applyGroupMap.end(); ++it)
		{
			for (auto i = 0; i < it->second.count; ++i)
			{
				if (it->second.playerid[i] == player->getPlayerId())
				{
					find = true;
					break;
				}
			}

			if (find)
			{
				for (auto i = 0; i < it->second.count; ++i)
				{
					if (it->second.playerid[i] != player->getPlayerId())
					{
						auto sid = m_pPlayerMngService->getSessionID(it->second.playerid[i]);
						// 通知其他玩家对手取消匹配
						msg::StartPVPFightAck ack;
						ack.set_code(err::Code::PVP_RIVAL_EXIT);
						SEND_PB_MSG(m_pNetService, sid, MessageID::MSG_START_PVP_ACK, ack);
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
		m_pvpSet.erase(player->getPlayerId());
	}

	// 通知客户端取消成功
	msg::CodeAck ack;
	ack.set_code(err::Code::SUCCESS);
	SEND_PB_MSG(m_pNetService, sessionID, MessageID::MSG_STOP_PVP_ACK, ack);
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
			auto player = m_pPlayerMngService->getPlayer(*it);
			if (player == NULL || player->getIsOnline() == false)
			{
				m_pvpSet.erase(player->getPlayerId());
				tag = false;
				break;
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

		const auto playerCount = 2;
		PLAYER_ID arrPlayer[playerCount] = { p1, p2 };

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
		for (auto i = 0; i < playerCount; ++i)
		{
			SEND_PB_MSG(m_pNetService, m_pPlayerMngService->getSessionID(arrPlayer[i]), MessageID::MSG_START_PVP_ACK, ack);
		}

		if (fightNode)
		{
			// 玩家分组
			auto groupId = newFightGroup(arrPlayer, playerCount, FightType::FIGHT_PVP);

			// 提交新建战斗请求
			svr_msg::NewFightReq req;
			req.set_tag(groupId);
			req.set_mapid(0);
			req.set_fighttype(FightType::FIGHT_PVP);

			for (auto i = 0; i < playerCount; ++i)
			{
				auto player = req.add_players();
				player->set_playerid(arrPlayer[i]);
			}
			SEND_PB_MSG(m_pMasterNodeService, fightNode->sessionID, MessageID::MSG_NEW_FIGHT_REQ, req);
		}
	}
}