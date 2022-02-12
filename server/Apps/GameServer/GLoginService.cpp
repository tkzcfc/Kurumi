#include "GLoginService.h"
#include "GPlayerMngService.h"

// 登录服务

static std::string loginTimeoutKey(uint32_t sessionID)
{
	return StringUtils::format("login_timeout_%d", sessionID);
}


uint32_t GLoginService::onInit()
{
	G_CHECK_SERVICE(GSlaveNodeService);
	G_CHECK_SERVICE(GNetService);
	G_CHECK_SERVICE(GPlayerMngService);
	G_CHECK_SERVICE(GRoleMngService);
	

	// server
	m_pSlaveNodeService = m_serviceMgr->getService<GSlaveNodeService>();
	ON_PB_MSG_CLASS_CALL(m_pSlaveNodeService->noticeCenter(), MessageID::MSG_CKECK_TOKEN_ACK, svr_msg::CheckTokenAck, onMsg_CheckTokenAck);
	ON_PB_MSG_CLASS_CALL(m_pSlaveNodeService->noticeCenter(), MessageID::MES_CHANGE_TOKEN_NTF, svr_msg::TokenChangeNtf, onMsg_TokenChangeNtf);

	// client
	m_pNetService = m_serviceMgr->getService<GNetService>();
	ON_PB_MSG_CLASS_CALL(m_pNetService->noticeCenter(), MessageID::MSG_LOGIN_REQ, msg::LoginReq, onMsg_LoginReq);
	ON_PB_MSG_CLASS_CALL(m_pNetService->noticeCenter(), MessageID::MSG_CREATE_ROLE_REQ, msg::CreateRoleReq, onMsg_CreateRoleReq);
	ON_PB_MSG_CLASS_CALL(m_pNetService->noticeCenter(), MessageID::MSG_ENTER_GAME_REQ, msg::EnterGameReq, onMsg_EnterGameReq);

	

	// 玩家管理服务
	m_pPlayerMngService = m_serviceMgr->getService<GPlayerMngService>();
	// 角色管理服务
	m_pRoleMngService = m_serviceMgr->getService<GRoleMngService>();

	m_pNetService->noticeCenter()->addListener(this, GNetService::MSG_KEY_DISCONNECT, [=](uint32_t sessionID) 
	{
		this->playerOffline(m_pPlayerMngService->getPlayerBySessionID(sessionID), err::Code::EXIT_GAME_CLIENT_DIS);
	});

	return SCODE_START_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// server

void GLoginService::onMsg_CheckTokenAck(uint32_t sessionID, const svr_msg::CheckTokenAck& msg)
{
	GApplication::getInstance()->getScheduler()->unSchedule(this, loginTimeoutKey(msg.session()));

	msg::LoginAck ack;

	if (msg.code() == err::Code::SUCCESS)
	{
		std::vector<GPlayer*> players;
		if (m_pPlayerMngService->queryPlayerInfo(msg.account(), players) == false)
		{
			// 没有查找到,创建新玩家
			auto player = m_pPlayerMngService->createPlayer(msg.account());
			if (player == NULL)
			{
				ack.set_code(err::Code::UNKNOWN);
			}
			else
			{
				ack.set_code(err::Code::SUCCESS);
				auto info = ack.add_infos();
				info->set_name(player->getName());
				info->set_playerid(player->getPlayerId());

				player->setToken(msg.token());
			}
		}
		else
		{
			for (auto it : players)
			{
				it->setToken(msg.token());
			}
			// 自动选择玩家数据
			if (msg.pid() == 0)
			{
				for (auto it : players)
				{
					auto info = ack.add_infos();
					info->set_name(it->getName());
					info->set_playerid(it->getPlayerId());

					auto& roles = it->getRoles();
					for (auto role : roles)
					{
						info->add_arrroleids(role->getRoleId());
					}
				}

				if (ack.infos_size() == 0)
					ack.set_code(err::Code::GAME_LOGIN_NO_FOUND_PLAYER);
				else if (ack.infos_size() == 1)
					ack.set_code(err::Code::SUCCESS);
				else
					ack.set_code(err::Code::GAME_LOGIN_MUT_PID);
			}
			else
			{
				for (auto it : players)
				{
					if (it->getPlayerId() == msg.pid())
					{
						auto info = ack.add_infos();
						info->set_name(it->getName());
						info->set_playerid(it->getPlayerId());
						auto& roles = it->getRoles();
						for (auto role : roles)
						{
							info->add_arrroleids(role->getRoleId());
						}
					}
				}
				if (ack.infos_size() == 1)
					ack.set_code(err::Code::SUCCESS);
				else /// 该账号没有对应玩家id
					ack.set_code(err::Code::GAME_LOGIN_NO_FOUND_PLAYER);
			}
		}
	}
	else
	{
		ack.set_code(msg.code());
	}
	
	SEND_PB_MSG(m_pNetService, msg.session(), MessageID::MSG_LOGIN_ACK, ack);

	if (ack.code() == err::Code::SUCCESS && ack.infos_size() == 1)
	{
		const auto& info = ack.infos().Get(0);
		onPlayerLogin(info.playerid(), msg.session());
	}
}

void GLoginService::onMsg_TokenChangeNtf(uint32_t sessionID, const svr_msg::TokenChangeNtf& msg)
{
	std::vector<GPlayer*> players;
	if (m_pPlayerMngService->queryPlayerInfo(msg.account(), players))
	{
		for (auto& it : players)
		{
			it->setToken(msg.token());
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// client

void GLoginService::onMsg_LoginReq(uint32_t sessionID, const msg::LoginReq& msg)
{
	if (m_pSlaveNodeService->isOnline() == false)
	{
		msg::LoginAck ack;
		ack.set_code(err::SVR_ERROR);
		SEND_PB_MSG(m_pNetService, sessionID, MessageID::MSG_LOGIN_ACK, ack);
		return;
	}

	// 发送至登录服校验账号/token合法性
	svr_msg::CheckTokenReq req;
	req.set_account(msg.account());
	req.set_token(msg.token());
	req.set_pid(msg.playerid());
	req.set_session(sessionID);
	SEND_PB_MSG_NO_SESSION(m_pSlaveNodeService, MessageID::MSG_CKECK_TOKEN_REQ, req);

	GApplication::getInstance()->getScheduler()->scheduleOnce([=](float dt) 
	{
		msg::LoginAck ack;
		ack.set_code(err::LOGIN_TIMEOUT);
		SEND_PB_MSG(m_pNetService, sessionID, MessageID::MSG_LOGIN_ACK, ack);
	}, this, 2.0f, loginTimeoutKey(sessionID));
}

void GLoginService::onMsg_CreateRoleReq(uint32_t sessionID, const msg::CreateRoleReq& msg)
{
	auto player = m_pPlayerMngService->getPlayerBySessionID(sessionID);
	if (player == NULL)
		return;

	msg::CreateRoleAck ack;
	ack.set_code(err::SUCCESS);
	ack.set_roleid(0);
	do
	{
		if (msg.name().size() <= 0)
		{
			ack.set_code(err::NAME_STR_TO_SHORT);
			break;
		}

		if (m_pRoleMngService->containName(msg.name()))
		{
			ack.set_code(err::NAME_TARGET_REPEAT);
			break;
		}

		auto pRole = m_pRoleMngService->createRole(msg.name(), msg.occupation());
		if (pRole == NULL)
		{
			ack.set_code(err::SVR_ERROR);
			break;
		}
		ack.set_roleid(pRole->getRoleId());

		player->addRole(pRole);

		auto local = m_serviceMgr->getService<GLocalStorageService>();
		player->save(local->getsqliter());
	} while (false);
	SEND_PB_MSG(m_pNetService, sessionID, MessageID::MSG_CREATE_ROLE_ACK, ack);
}

void GLoginService::onMsg_EnterGameReq(uint32_t sessionID, const msg::EnterGameReq& msg)
{
	msg::EnterGameAck ack;
	ack.set_code(err::SUCCESS);

	do
	{
		auto player = m_pPlayerMngService->getPlayerBySessionID(sessionID);
		if (player == NULL)
		{
			ack.set_code(err::ACCOUNT_NOT_EXIST);
			break;
		}
		if (msg.token() != player->getToken())
		{
			ack.set_code(err::TOKEN_ERR);
			break;
		}
		if (msg.playerid() != player->getPlayerId())
		{
			ack.set_code(err::SVR_ERROR);
			break;
		}

		auto pRole = player->getRole(msg.roleid());
		if (pRole == NULL)
		{
			ack.set_code(err::ROLE_NOT_EXIST);
			break;
		}
		if (player->setLoginRole(msg.roleid()) == false)
		{
			ack.set_code(err::ROLE_NOT_EXIST);
			break;
		}

		auto pInfo = ack.mutable_roleinfo();
		pInfo->set_roleid(pRole->getRoleId());
		pInfo->set_name(pRole->getName());
		pInfo->set_lv(pRole->getLv());
		pInfo->set_occupation(pRole->getOcc());
	} while (false);

	SEND_PB_MSG(m_pNetService, sessionID, MessageID::MSG_ENTER_GAME_ACK, ack);
}

void GLoginService::onPlayerLogin(int64_t playerId, uint32_t sessionID)
{
	auto player = m_pPlayerMngService->getPlayer(playerId);
	G_CHECK_NULL_RETURN(player);

	if (player->getIsOnline())
	{
		// 将之前的客户端踢下线
		playerOffline(player, err::Code::EXIT_GAME_LOGIN_REPEAT);
	}

	// 玩家登录成功逻辑
	player->setIsOnline(true);
	player->setSessionID(sessionID);
}

void GLoginService::playerOffline(GPlayer* player, err::Code code)
{
	if (player == NULL)
		return;

	if (player->getIsOnline() == false)
	{
		return;
	}

	if (code == err::Code::EXIT_GAME_LOGIN_REPEAT)
	{
		msg::ExitGameNtf ntf;
		ntf.set_code(code);
		SEND_PB_MSG(m_pNetService, player->getSessionID(), MessageID::MSG_EXIT_GAME_NTF, ntf);
	}

	/// 玩家退出游戏清理逻辑
	player->setIsOnline(false);
}

