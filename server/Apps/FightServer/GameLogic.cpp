#include "GameLogic.h"

// 服务器游戏同步逻辑

static int32_t sg_uuid_seed = 0;

GameLogic::GameLogic()
	: m_isFinish(false)
	, m_pNetService(NULL)
	, m_playerCount(0)
{
	m_uuid = sg_uuid_seed++;
	m_state = RUN_STATE::READY;
	m_waitTime = 0.0f;
}

GameLogic::~GameLogic()
{
	if (m_pNetService)
	{
		m_pNetService->noticeCenter()->delListener(this);
	}
}

err::Code GameLogic::init(const GGameWorldInitArgs &args, const ::google::protobuf::RepeatedPtrField< ::svr_msg::FightPlayerSpawnInfo >& players)
{
	this->setInitArgs(args);

	m_world = std::make_unique<GGameWorld>();

	if (m_world == NULL)
	{
		return err::Code::NO_MEMORY;
	}

	if (!m_world->init(args))
	{
		LOG(ERROR) << "init map failed, mapID: " << args.mapId;
		return err::Code::FIGHT_INIT_FAIL;
	}

	if (players.size() > G_FIGHT_MAX_PLAYER_COUNT)
		return err::Code::FIGHT_PLAYER_TOO_MUCH;

	for (auto i = 0; i < players.size(); ++i)
	{
		m_players[i] = std::make_unique<GamePlayer>();
		if (m_players[i] == NULL)
			return err::Code::NO_MEMORY;

		auto code = m_players[i]->init(players.Get(i));
		if (code != err::Code::SUCCESS)
			return code;

		m_playerIDSet.insert(m_players[i]->getPlayerID());
	}
	if (m_playerIDSet.size() != players.size())
	{
		return err::Code::FIGHT_PLAYERID_REPEAT;
	}

	m_pApplication = GApplication::getInstance();
	m_playerCount = players.size();
	m_lastRunTime = m_pApplication->getRunTime();
	m_pNetService = m_pApplication->getServiceMgr()->getService<GNetService>();

	//! 客户端通信
	ON_PB_MSG_CLASS_CALL(m_pNetService->noticeCenter(), MessageID::MSG_RUN_NEXT_FRAME_REQ, msg::RunNextFrameReq, onMsg_RunNextFrameReq);
	
	return err::Code::SUCCESS;
}


void GameLogic::update(float dt)
{
	// 玩家全部退出游戏,自动结束游戏
	if (m_playerCount <= 0)
	{
		this->setIsFinish(true);
		return;
	}

	switch (m_state)
	{
	case GameLogic::READY:
	{
		this->update_Ready(dt);
	}break;
	case GameLogic::RUN:
	{
		this->update_Run(dt);
	}
		break;
	case GameLogic::WAIT:
	{
		this->update_Wait(dt);
	}
		break;
	default:
		break;
	}
}

void GameLogic::update_Ready(float dt)
{
	bool hasOffline = false;
	// 玩家长时间未准备完毕则将其踢出游戏,避免游戏一直无法进行
	for (auto i = 0; i < m_playerCount; ++i)
	{
		if (m_players[i]->isOffline())
		{
			hasOffline = true;
			if (m_pApplication->getRunTime() - m_players[i]->getOfflineTime() > 30.0f)
			{
				this->exitGame(m_players[i]->getPlayerID());
				// 必须break
				break;
			}
		}
	}

	// 全部准备完毕
	if (!hasOffline)
	{
		m_state = GameLogic::RUN;

		msg::RunNextFrameAck ack;
		ack.set_frame(m_world->getGameLogicFrame() + 1);
		this->sendToAllPlayer(MessageID::MSG_RUN_NEXT_FRAME_ACK, ack);
	}
}

void GameLogic::update_Run(float dt)
{
	uint32_t maxFrame = 0U;
	uint32_t minFrame = UINT_MAX;
	for (auto i = 0; i < m_playerCount; ++i)
	{
		maxFrame = MAX(maxFrame, m_players[i]->getLastRecvFrame());
		minFrame = MIN(minFrame, m_players[i]->getLastRecvFrame());
	}

	// 服务器逻辑以网速最好的客户端逻辑帧步进
	if (maxFrame > m_world->getGameLogicFrame())
	{
		m_world->update(dt);
	}

	if (minFrame < m_world->getGameLogicFrame() && m_world->getGameLogicFrame() - minFrame > 100U)
	{
		// 服务逻辑超过了最慢客户端太多,则等待最慢的客户端一段时间
		if (m_playerCount > 1)
		{
			m_state = RUN_STATE::WAIT;
			m_waitTime = 0.0f;
		}
		else
		{
			// 只有一个玩家,判断他的离线时间
			auto player = getSlowestPlayer();
			if (player && player->isOffline())
			{
				// 离线太久,踢出游戏
				if (m_pApplication->getRunTime() - player->getOfflineTime() > 60.0f)
				{
					this->exitGame(player->getPlayerID());
				}
			}
		}
	}

	//// 清除比较久的操作记录
	//if (m_pastRecords.empty() == false)
	//{
	//	// 最多保留帧数
	//	const int32_t maxCount = 350;
	//	// 超过最多保留帧数多少之后开始清理
	//	const int32_t stepCount = 50;

	//	if (m_world->getGameLogicFrame() - m_pastRecords.front().frame > maxCount + stepCount)
	//	{
	//		while (!m_pastRecords.empty())
	//		{
	//			if (m_world->getGameLogicFrame() - m_pastRecords.front().frame <= maxCount)
	//				break;

	//			m_pastRecords.pop_front();
	//		}
	//	}
	//}
}

void GameLogic::update_Wait(float dt)
{
	uint32_t maxFrame = 0U;
	uint32_t minFrame = UINT_MAX;
	for (auto i = 0; i < m_playerCount; ++i)
	{
		maxFrame = MAX(maxFrame, m_players[i]->getLastRecvFrame());
		minFrame = MIN(minFrame, m_players[i]->getLastRecvFrame());
	}

	m_waitTime += dt;
	if (minFrame >= m_world->getGameLogicFrame())
	{
		m_state = RUN_STATE::RUN;
		m_waitTime = 0.0f;
	}
	// 等待时间太久,将该玩家踢出游戏
	if (m_waitTime >= 10.0f)
	{
		auto player = getSlowestPlayer();
		if (player)
		{
			this->exitGame(player->getPlayerID());
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////

err::Code GameLogic::join(uint32_t sessionID, const msg::JoinFightReq& req)
{
	err::Code code = err::Code::UNKNOWN;
	bool playerExit = false;

	for (auto i = 0; i < m_playerCount; ++i)
	{
		if (m_players[i] && m_players[i]->getPlayerID() == req.playerid())
		{
			if (m_players[i]->getSessionID() != GamePlayer::INVALID_SESSION_ID)
			{
				code = err::Code::FIGHT_PLAYING;
				break;
			}
			m_players[i]->setSessionID(sessionID);

			code = err::Code::SUCCESS;
		}
	}

	if (code == err::Code::SUCCESS)
	{
		msg::PlayerReadyNotify ntf;
		ntf.set_pid(req.playerid());
		this->sendToAllPlayer(MessageID::MSG_PLAYER_READY_NTF, ntf);

		if (m_state == GameLogic::READY)
		{
			// 不为0有问题
			if (req.frame() != 0)
			{
				code = err::Code::FIGHT_FRAME_ERR;
				playerExit = true;
			}
		}
		else
		{
			// 客户端是断线重连进入的
			if (req.frame() > 0 && m_pastRecords.empty() == false)
			{
				if (m_pastRecords.front().frame <= req.frame())
				{
					msg::RunNextFrameAck ack;
					bool tag = false;
					
					auto frame = m_pastRecords.front().frame;
					for (auto it = m_pastRecords.begin(); it != m_pastRecords.end(); ++it)
					{
						if (it->frame < frame)
							continue;

						if (it->frame > frame)
						{
							ack.set_frame(frame);
							SEND_PB_MSG(m_pNetService, sessionID, MessageID::MSG_RUN_NEXT_FRAME_ACK, ack);

							ack.clear_inputs();
							frame = it->frame;
						}
						auto pInput = ack.add_inputs();
						pInput->assign(it->input.c_str(), it->input.size());
						tag = true;
					}

					if (tag)
					{
						ack.set_frame(frame);
						SEND_PB_MSG(m_pNetService, sessionID, MessageID::MSG_RUN_NEXT_FRAME_ACK, ack);
					}
				}
				else
				{
					// 服务器缓存记录不足以支持客户端断线重连
					code = err::Code::FIGHT_PAST_RECORDS_INC;
					playerExit = true;
				}
			}
		}
	}

	if (playerExit)
	{
		m_pApplication->getScheduler()->scheduleOnce([=](float)
		{
			this->exitGame(req.playerid());
		}, this, 0.0f, StringUtils::format("%d_exit", req.playerid()));
	}

	if (code != err::Code::UNKNOWN)
		return code;

	// 玩家已经被踢出游戏
	if (m_playerIDSet.count(req.playerid()) > 0)
	{
		return err::Code::FIGHT_LEAVE_GAME;
	}

	return err::Code::FIGHT_NOE_FOUND_PLAYER;
}

void GameLogic::exitGame(int64_t playerID)
{
	if (!containPlayer(playerID))
		return;

	msg::PlayerExitFightNotify ntf;
	ntf.set_pid(playerID);
	this->sendToAllPlayer(MessageID::MSG_PLAYER_EXIT_FIGHT_NTF, ntf);
	
	std::unique_ptr<GamePlayer> tmp[G_FIGHT_MAX_PLAYER_COUNT];
	int32_t index = 0;

	for (auto i = 0; i < G_FIGHT_MAX_PLAYER_COUNT; ++i)
	{
		if (m_players[i] && m_players[i]->getPlayerID() == playerID)
		{
			tmp[index].reset(m_players[i].release());
			index++;
		}
		m_players[i] = NULL;
	}
	
	for (auto i = 0; i < index; ++i)
	{
		m_players[i].reset(tmp[i].release());
	}

	m_playerCount--;

	G_ASSERT(index == m_playerCount);
}

err::Code GameLogic::exitGameWithSessionID(uint32_t sessionID)
{
	for (auto i = 0; i < m_playerCount; ++i)
	{
		if (m_players[i]->getSessionID() == sessionID)
		{
			this->exitGame(m_players[i]->getPlayerID());
			return err::Code::SUCCESS;
		}
	}
	return err::Code::FIGHT_LEAVE_GAME;
}

bool GameLogic::containPlayer(int64_t playerID)
{
	for (auto i = 0; i < m_playerCount; ++i)
	{
		if (m_players[i]->getPlayerID() == playerID)
			return true;
	}
	return false;
}


void GameLogic::sendToAllPlayer(MessageID msgID, const ::google::protobuf::MessageLite& msg)
{
	for (auto i = 0; i < m_playerCount; ++i)
	{
		SEND_PB_MSG(m_pNetService, m_players[i]->getSessionID(), msgID, msg);
	}
}

GamePlayer* GameLogic::getPlayerBySessionID(uint32_t sessionID)
{
	for (auto i = 0; i < m_playerCount; ++i)
	{
		if (m_players[i]->getSessionID() == sessionID)
			return m_players[i].get();
	}
	return NULL;
}

// 获取逻辑帧最慢的一个玩家
GamePlayer* GameLogic::getSlowestPlayer()
{
	GamePlayer* player = NULL;
	uint32_t minFrame = UINT_MAX;
	for (auto i = 0; i < m_playerCount; ++i)
	{
		if (m_players[i]->getLastRecvFrame() < minFrame)
		{
			minFrame = m_players[i]->getLastRecvFrame();
			player = m_players[i].get();
		}
	}
	return player;
}

void GameLogic::onMsg_RunNextFrameReq(uint32_t sessionID, const msg::RunNextFrameReq& req)
{
	auto player = getPlayerBySessionID(sessionID);
	if (player == NULL) return;
	
	auto curFrame = m_world->getGameLogicFrame();

	if (req.frame() > curFrame)
	{
		// 客户端逻辑帧超过服务端逻辑帧太多,客户端作弊了吧
		if (req.frame() - curFrame > 10)
		{
			// 当前消息视为无效消息
			return;
		}
		player->setLastRecvFrame(req.frame());
	}
	else
	{
		player->setLastRecvFrame(req.frame());
		// 客户端发送的操作数据距离当前逻辑帧太久,直接抛弃操作
		if (m_world->getGameLogicFrame() - req.frame() > 100)
			return;
	}
	
	// 记录用户输入
	for (auto i = 0; i < req.input_size(); ++i)
	{
		auto& input = req.input().Get(i);

		GOPMsg_Base* msgBase = (GOPMsg_Base*)input.c_str();

		if (input.size() < sizeof(GOPMsg_Base) || msgBase->msgSize != input.size())
		{
			G_ASSERT(0);
			return;
		}
		// 更改帧数
		msgBase->logicFrame = curFrame + 1;

		m_pastRecords.push_back(Record());

		auto& record = m_pastRecords.back();
		record.frame = curFrame + 1;
		record.input = input;
	}
}

