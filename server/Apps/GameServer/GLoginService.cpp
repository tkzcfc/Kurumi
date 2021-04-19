#include "GLoginService.h"
#include "GPlayerMngService.h"

// 登录服务

uint32_t GLoginService::onInit()
{
	G_CHECK_SERVICE(GSlaveNodeService);
	G_CHECK_SERVICE(GNetService);
	G_CHECK_SERVICE(GPlayerMngService);

	m_pSlaveNodeService = m_serviceMgr->getService<GSlaveNodeService>();
	ON_PB_MSG_CLASS_CALL(m_pSlaveNodeService->noticeCenter(), MessageID::MSG_CKECK_TOKEN_ACK, svr_msg::CheckTokenAck, onMsg_CheckTokenAck);


	m_pNetService = m_serviceMgr->getService<GNetService>();
	ON_PB_MSG_CLASS_CALL(m_pNetService->noticeCenter(), MessageID::MSG_LOGIN_REQ, msg::LoginReq, onMsg_LoginReq);

	m_pPlayerMngService = m_serviceMgr->getService<GPlayerMngService>();

	m_pNetService->noticeCenter()->addListener(this, GNetService::MSG_KEY_DISCONNECT, [=](uint32_t sessionID) 
	{
		this->playerOffline(m_pPlayerMngService->getPlayerBySessionID(sessionID), err::Code::EXIT_GAME_CLIENT_DIS);
	});

	return SCODE_START_SUCCESS;
}

void GLoginService::onMsg_CheckTokenAck(uint32_t sessionID, const svr_msg::CheckTokenAck& msg)
{
	msg::LoginAck ack;

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
		}
	}
	else
	{
		// 自动选择玩家数据
		if (msg.pid() == 0)
		{
			for (auto it : players)
			{
				auto info = ack.add_infos();
				info->set_name(it->getName());
				info->set_playerid(it->getPlayerId());
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
				}
			}
			if (ack.infos_size() == 1)
				ack.set_code(err::Code::SUCCESS);
			else /// 该账号没有对应玩家id
				ack.set_code(err::Code::GAME_LOGIN_NO_FOUND_PLAYER);
		}
	}
	
	SEND_PB_MSG(m_pNetService, msg.session(), MessageID::MSG_LOGIN_ACK, ack);

	if (ack.code() == err::Code::SUCCESS && ack.infos_size() == 1)
	{
		const auto& info = ack.infos().Get(0);
		onPlayerLogin(info.playerid(), sessionID);
	}
}

void GLoginService::onMsg_LoginReq(uint32_t sessionID, const msg::LoginReq& msg)
{
	// 发送至登录服校验账号/token合法性
	svr_msg::CheckTokenReq req;
	req.set_account(msg.account());
	req.set_token(msg.token());
	req.set_pid(msg.playerid());
	req.set_session(sessionID);
	SEND_PB_MSG_NO_SESSION(m_pSlaveNodeService, MessageID::MSG_CKECK_TOKEN_REQ, req);
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

