#include "GameLogic.h"


//////////////////////////////////////////////////////////////////////////
/// 游戏配置相关

// 服务端逻辑帧最多领先最快客户端多少帧
static const uint32_t MAX_LEAD_FRAME_DIS_MAX_CLIENT = 10U;

// 服务端逻辑帧最多领先最慢客户端多少帧 (超过这个帧数后切换为等待状态)
static const uint32_t MAX_LEAD_FRAME_DIS_MIN_CLIENT = 100U;

// 服务器处于 WAIT_CONNECT 阶段时最多等待客户端多少秒(超过这个时间客户端还没有连上就会将客户端踢出游戏)
static const float MAX_WAIT_CONNECT_TIME = 5.0f;

// 单个玩家游戏时,客户端最大离线时间(超过这个时间客户端还没有断线重连就会将客户端踢出游戏)
static const float MAX_OFF_LINE_TIME_SINGLE_PLAYER = 60.0f;

// 多个玩家游戏时,客户端最大离线时间(应该设置较小,避免其他玩家太长时间处于等待期)
static const float MAX_OFF_LINE_TIME_MULTIPLE_PLAYER = 10.0f;

//////////////////////////////////////////////////////////////////////////


static int32_t sg_uuid_seed = 0;

GameLogic::GameLogic()
	: m_isFinish(false)
	, m_pNetService(NULL)
	, m_playerCount(0)
{
	m_uuid = sg_uuid_seed++;
	m_state = RUN_STATE::WAIT_CONNECT;
	m_waitTime = 0.0f;
	m_lastRunTime = 0.0f;
	m_accumilatedTime = 0.0f;
}

GameLogic::~GameLogic()
{
	if (m_pNetService)
	{
		m_pNetService->noticeCenter()->delListener(this);
	}
}

err::Code GameLogic::init(const GGameWorldInitArgs &args, const ::google::protobuf::RepeatedPtrField< ::svr_msg::FightRoleSpawnInfo >& roles)
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

	if (roles.size() > G_FIGHT_MAX_PLAYER_COUNT)
		return err::Code::FIGHT_PLAYER_TOO_MUCH;

	for (auto i = 0; i < roles.size(); ++i)
	{
		m_players[i] = std::make_unique<GamePlayer>();
		if (m_players[i] == NULL)
			return err::Code::NO_MEMORY;

		auto code = m_players[i]->init(roles.Get(i));
		if (code != err::Code::SUCCESS)
			return code;

		m_playerIDSet.insert(m_players[i]->getPlayerID());
	}
	if (m_playerIDSet.size() != roles.size())
	{
		return err::Code::FIGHT_PLAYERID_REPEAT;
	}

	m_pApplication = GApplication::getInstance();
	m_playerCount = roles.size();
	m_pNetService = m_pApplication->getServiceMgr()->getService<GNetService>();

	//! 客户端通信
	ON_PB_MSG_CLASS_CALL(m_pNetService->noticeCenter(), MessageID::MSG_RUN_NEXT_FRAME_REQ, msg::RunNextFrameReq, onMsg_RunNextFrameReq);
	ON_PB_MSG_CLASS_CALL(m_pNetService->noticeCenter(), MessageID::MSG_LOADING_PERCENT_REQ, msg::PlayerLoadingReq, onMsg_PlayerLoadingReq);

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
	case GameLogic::WAIT_CONNECT:
	{
		this->update_WaitConnect(dt);
	}break;
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

void GameLogic::update_WaitConnect(float dt)
{
	bool hasOffline = false;
	// 玩家长时间未连接成功则将其踢出游戏,避免游戏一直无法进行
	for (auto i = 0; i < m_playerCount; ++i)
	{
		if (m_players[i]->isOffline())
		{
			hasOffline = true;
			if (m_pApplication->getRunTime() - m_players[i]->getOfflineTime() > MAX_WAIT_CONNECT_TIME)
			{
				this->exitGame(m_players[i]->getPlayerID());
				// 必须break
				break;
			}
		}
	}

	// 全部连接成功
	if (!hasOffline)
	{
		m_state = GameLogic::READY;
	}
}

void GameLogic::update_Ready(float dt)
{
	// 准备阶段不允许玩家掉线,将离线玩家踢出游戏
	bool exitGameTag = false;
	do 
	{
		exitGameTag = false;
		for (auto i = 0; i < m_playerCount; ++i)
		{
			if (m_players[i]->isOffline())
			{
				exitGameTag = true;
				this->exitGame(m_players[i]->getPlayerID());
				// 必须break
				break;
			}
		}
	} while (exitGameTag);

	if (m_playerCount <= 0)
		return;

	bool finishAllTag = true;
	for (auto i = 0; i < m_playerCount; ++i)
	{
		if (!m_players[i]->getLoadFinish())
		{
			finishAllTag = false;
			break;
		}
	}

	// 全部准备完毕
	if (finishAllTag)
	{
		m_state = GameLogic::RUN;

		G_ASSERT(m_world->getGameLogicFrame() == 0);

		msg::RunNextFrameAck ack;
		ack.set_nextframe(0);
		this->sendToAllPlayer(MessageID::MSG_RUN_NEXT_FRAME_ACK, ack);
	}
}

void GameLogic::update_Run(float dt)
{
	m_accumilatedTime += dt;

	uint32_t maxFrame = 0U;
	uint32_t minFrame = UINT_MAX;
	for (auto i = 0; i < m_playerCount; ++i)
	{
		maxFrame = MAX(maxFrame, m_players[i]->getLastRecvFrame());
		minFrame = MIN(minFrame, m_players[i]->getLastRecvFrame());
	}

	// 目标帧率
	uint32_t targetFrame = maxFrame + MAX_LEAD_FRAME_DIS_MAX_CLIENT;
	// 服务器逻辑以网速最好的客户端逻辑帧步进
	if (targetFrame >= m_world->getGameLogicFrame())
	{
		m_runNextFrameAckCache.clear_frames();
		m_runNextFrameAckCache.set_nextframe(m_world->getGameLogicFrame());
		
		if (m_curFrameInputs.size() > 0)
		{
			for (auto& it : m_curFrameInputs)
			{
				G_ASSERT(m_world->getGameLogicFrame() == it->frame());
				//it->set_frame(m_world->getGameLogicFrame());
				m_runNextFrameAckCache.add_frames()->CopyFrom(*it);
				m_pastRecords.add_frames()->CopyFrom(*it);

				freePlayerFrameInput(it);
			}
			m_curFrameInputs.clear();
		}

		sendToAllPlayer(MessageID::MSG_RUN_NEXT_FRAME_ACK, m_runNextFrameAckCache);

		m_world->updateFrame();

		//printf("do frame... %d\n", m_world->getGameLogicFrame());
		m_lastRunTime = m_accumilatedTime;
	}

	// 多个玩家
	if (m_playerCount > 1)
	{
		// 服务逻辑超过了最慢客户端太多,则等待最慢的客户端一段时间
		if (minFrame < m_world->getGameLogicFrame() && m_world->getGameLogicFrame() - minFrame > MAX_LEAD_FRAME_DIS_MIN_CLIENT)
		{
			m_state = RUN_STATE::WAIT;
			m_waitTime = 0.0f;
		}
	}
	else
	{
		// 只有一个玩家,判断他的离线时间
		auto player = getSlowestPlayer();
		if (player && player->isOffline())
		{
			// 离线太久,踢出游戏
			if (m_pApplication->getRunTime() - player->getOfflineTime() > MAX_OFF_LINE_TIME_SINGLE_PLAYER)
			{
				this->exitGame(player->getPlayerID());
			}
		}
	}

	// 太长时间没有跑过逻辑帧,应该是客户端推帧服务器没有收到,结束游戏
	// 这个时间应该大于离线等待时间
	if (m_accumilatedTime - m_lastRunTime > 120.0f)
	{
		m_lastRunTime = m_accumilatedTime;
		// 全部踢出游戏
		for (auto i = m_playerCount - 1; i >= 0; --i)
		{
			this->exitGame(m_players[i]->getPlayerID());
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
	if (m_waitTime >= MAX_OFF_LINE_TIME_MULTIPLE_PLAYER)
	{
		auto player = getSlowestPlayer();
		if (player)
		{
			this->exitGame(player->getPlayerID());
		}
	}
}

//////////////////////////////////////////////////////////////////////////

uint32_t GameLogic::getGameLogicFrame() const
{
	if (m_world)
		return m_world->getGameLogicFrame();
	return 0;
}

int32_t GameLogic::getGameStatus() const
{
	return (int32_t)m_state;
}

////////////////////////////////////////////////////////////////////////////////////////////

err::Code GameLogic::joinCode(uint32_t sessionID, const msg::JoinFightReq& req)
{
	// 玩家已经被踢出游戏
	if (m_playerIDSet.count(req.playerid()) == 0)
	{
		return err::Code::FIGHT_LEAVE_GAME;
	}

	err::Code code = err::Code::UNKNOWN;
	for (auto i = 0; i < m_playerCount; ++i)
	{
		if (m_players[i] && m_players[i]->getPlayerID() == req.playerid())
		{
			if (m_players[i]->getSessionID() != GamePlayer::INVALID_SESSION_ID)
			{
				code = err::Code::FIGHT_PLAYING;
				break;
			}
			code = err::Code::SUCCESS;
		}
	}

	if (code == err::Code::SUCCESS)
	{
		if (m_state == GameLogic::READY || m_state == GameLogic::WAIT_CONNECT)
		{
			// 不为0有问题
			if (req.frame() != 0)
			{
				code = err::Code::FIGHT_FRAME_ERR;
			}
		}
		else
		{
			if (m_pastRecords.frames_size() <= 0)
			{
				if (req.frame() > 0)
				{
					code = err::Code::FIGHT_FRAME_ERR;
				}
			}
			else
			{
				if (m_pastRecords.frames().Get(0).frame() > req.frame())
				{
					// 服务器缓存记录不足以支持客户端断线重连
					code = err::Code::FIGHT_PAST_RECORDS_INC;
				}
			}
		}
	}

	if (code != err::Code::UNKNOWN)
		return code;

	return err::Code::FIGHT_NOE_FOUND_PLAYER;
}

void GameLogic::doJoin(uint32_t sessionID, const msg::JoinFightReq& req)
{
	// 设置sessionID
	for (auto i = 0; i < m_playerCount; ++i)
	{
		if (m_players[i] && m_players[i]->getPlayerID() == req.playerid())
		{
			m_players[i]->setSessionID(sessionID);
		}
	}

	//msg::PlayerReadyNotify ntf;
	//ntf.set_pid(req.playerid());
	//this->sendToAllPlayer(MessageID::MSG_PLAYER_READY_NTF, ntf);

	if (m_state == GameLogic::READY || m_state == GameLogic::WAIT_CONNECT)
	{
		sendLoadingPercentToAllPlayer();
	}
	else
	{
		pushFrameInfo(req.frame(), sessionID);
	}
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
		if (m_players[i] && m_players[i]->getPlayerID() != playerID)
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

void GameLogic::sendLoadingPercentToAllPlayer()
{
	msg::PlayerLoadingAck ack;

	bool finish = true;
	for (auto i = 0; i < m_playerCount; ++i)
	{
		ack.add_percent(m_players[i]->getLoadPercent());
		ack.add_pid(m_players[i]->getPlayerID());
		finish = finish & m_players[i]->getLoadFinish();
	}
	ack.set_finish(finish);
	sendToAllPlayer(MessageID::MSG_LOADING_PERCENT_ACK, ack);
}

// 向玩家推帧
void GameLogic::pushFrameInfo(uint32_t startFrame, uint32_t sessionID)
{
	// MSG_PUSH_FRAME_BEGIN
	msg::Null null;
	SEND_PB_MSG(m_pNetService, sessionID, MessageID::MSG_PUSH_FRAME_BEGIN, null);


	msg::PushFrameInput ack;

	int32_t curCount = 0;
	bool sendTag = false;
	uint32_t frame = 0;

	for (auto i = 0; i < m_pastRecords.frames_size(); ++i)
	{
		auto& data = m_pastRecords.frames().Get(i);
		if (data.frame() >= startFrame)
		{
			sendTag = true;
			curCount++;

			if (frame != data.frame())
			{
				frame = data.frame();
				curCount++;
				// 大于一定帧数后进行分片推帧
				if (curCount > 50)
				{
					SEND_PB_MSG(m_pNetService, sessionID, MessageID::MSG_PUSH_FRAME_INPUT, ack);
					ack.clear_frames();
					sendTag = false;
				}
			}
			ack.set_lastframe(data.frame());
			ack.add_frames()->CopyFrom(data);
		}
	}

	if (sendTag)
	{
		SEND_PB_MSG(m_pNetService, sessionID, MessageID::MSG_PUSH_FRAME_INPUT, ack);
	}

	// MSG_PUSH_FRAME_END
	SEND_PB_MSG(m_pNetService, sessionID, MessageID::MSG_PUSH_FRAME_END, null);
}

msg::PlayerFrameInput* GameLogic::getFrameInputByPlayerId(int64_t pid)
{
	for (auto& it : m_curFrameInputs)
	{
		if (it->pid() == pid)
		{
			return it;
		}
	}

	auto pInput = dequeuePlayerFrameInput();
	pInput->set_pid(pid);
	m_curFrameInputs.push_back(pInput);
	return pInput;
}

msg::PlayerFrameInput* GameLogic::dequeuePlayerFrameInput()
{
	if (m_playerFrameInputCache.empty())
	{
		m_playerFrameInputCache.reserve(10);
		for (auto i = 0; i < 10; ++i)
		{
			PlayerFrameInputCache cache;
			cache.free = true;
			m_playerFrameInputCache.push_back(cache);
		}
	}

	for (auto& it : m_playerFrameInputCache)
	{
		if (it.free)
		{
			return &it.input;
		}
	}
	G_ASSERT(0);

	PlayerFrameInputCache cache;
	cache.free = true;
	m_playerFrameInputCache.push_back(cache);
	return &m_playerFrameInputCache.back().input;
}

void GameLogic::freePlayerFrameInput(msg::PlayerFrameInput* pInput)
{
	for (auto& it : m_playerFrameInputCache)
	{
		if (&it.input == pInput)
		{
			it.free = true;
			return;
		}
	}
	G_ASSERT(0);
}

void GameLogic::onMsg_RunNextFrameReq(uint32_t sessionID, const msg::RunNextFrameReq& req)
{
	if (m_state != GameLogic::RUN)
		return;

	auto player = getPlayerBySessionID(sessionID);
	if (player == NULL) return;
	
	auto curFrame = m_world->getGameLogicFrame();

	if (req.frame() > curFrame + 1)
	{
		// 客户端逻辑帧超过服务端逻辑帧,客户端作弊了吧
		// 当前消息视为无效消息
		LOG(ERROR) << "recv invalid input [1], playerid: " << player->getPlayerID();
		this->exitGame(player->getPlayerID());
		return;
	}
	else
	{
		player->setLastRecvFrame(req.frame());
		// 客户端发送的操作数据距离当前逻辑帧太久,直接抛弃操作
		if (curFrame - req.frame() > 30)
			return;
	}
	
	auto pInput = getFrameInputByPlayerId(player->getPlayerID());
	pInput->set_frame(curFrame);
	pInput->mutable_input()->CopyFrom(req.input());
}

void GameLogic::onMsg_PlayerLoadingReq(uint32_t sessionID, const msg::PlayerLoadingReq& req)
{
	auto player = getPlayerBySessionID(sessionID);
	if (player == NULL) return;

	if (player->getLoadFinish())
		return;

	player->setLoadPercent(MIN(req.percent(), 1.0f));
	player->setLoadFinish(req.finish());

	if (player->getLoadFinish())
		player->setLoadPercent(1.0f);

	this->sendLoadingPercentToAllPlayer();
}

