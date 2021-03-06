#include "ServiceFight.h"

// 最大同时战斗数量
#define MAX_FIGHT_COUNT 10

#define ERR_GEN_WORD_NO_MEM -1
#define ERR_GEN_WORD_INIT_FAIL -2

uint32_t ServiceFight::onInit()
{
	// 依赖网络服务,用于与玩家通信
	auto m_pNetService = m_serviceMgr->getService<GNetService>();
	// 依赖从节点同步服务,与主节点通信
	auto m_pSlaveNode = m_serviceMgr->getService<GSlaveNodeService>();

	if (m_pNetService == NULL)
	{
		LOG(ERROR) << "Missing service: 'GNetService'";
		return SCODE_START_FAIL_EXIT_APP;
	}
	if(m_pSlaveNode == NULL)
	{
		LOG(ERROR) << "Missing service: 'GSlaveNodeService'";
		return SCODE_START_FAIL_EXIT_APP;
	}
	
	//! 服务器通信
	ON_PB_MSG_CLASS_CALL(m_pSlaveNode->noticeCenter(), MessageID::MSG_NEW_FIGHT_REQ, svr_msg::NewFightReq, onMsg_NewFightReq);

	//! 客户端通信
	ON_PB_MSG_CLASS_CALL(m_pNetService->noticeCenter(), MessageID::MSG_JOIN_FIGHT_REQ, msg::JoinFightReq, onMsg_JoinFightReq);
	ON_PB_MSG_CLASS_CALL(m_pNetService->noticeCenter(), MessageID::MSG_EXIT_FIGHT_REQ, msg::ExitFightReq, onMsg_ExitFightReq);


	m_arrFightInfo.reserve(20);
	return SCODE_START_SUCCESS;
}

void ServiceFight::onStartService()
{
	// 定时清理已完成的战斗
	GApplication::getInstance()->getScheduler()->schedule([=](float) {
		this->clearInvalid();
	}, this, 5.0f, false, "check");
}

void ServiceFight::onStopService()
{
	m_pSlaveNode->noticeCenter()->delListener(this);
	m_pNetService->noticeCenter()->delListener(this);
}

void ServiceFight::onUpdate(float dt)
{
	for (auto& it : m_arrFightInfo)
	{
		if (it->finish() == false)
		{
			it->update(dt);
		}
	}
}

void ServiceFight::onDestroy()
{
	for (auto it : m_arrFightInfo)
	{
		delete it;
	}
	m_arrFightInfo.clear();
}

// 销毁世界
void ServiceFight::destroyFight(int32_t uuid)
{
	for (auto it = m_arrFightInfo.begin(); it != m_arrFightInfo.end(); ++it)
	{
		if ((*it)->uuid() == uuid)
		{
			delete *it;
			m_arrFightInfo.erase(it);
			break;
		}
	}
}

// 统计当前正在战斗的数量
int32_t ServiceFight::curFightCount()
{
	int32_t count = 0;
	for (auto& it : m_arrFightInfo)
	{
		if (it->finish() == false)
			count++;
	}
	return count;
}

// 清除无效战斗
void ServiceFight::clearInvalid()
{
	for (auto it = m_arrFightInfo.begin(); it != m_arrFightInfo.end(); )
	{
		if ((*it)->finish())
		{
			it = m_arrFightInfo.erase(it);
		}
		else
		{
			++it;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
/// MSG
/////////////////////////////////////////////////////////////////////////////////////////////
void ServiceFight::onMsg_NewFightReq(uint32_t sessionID, const svr_msg::NewFightReq& msg)
{
	svr_msg::NewFightAck ack;
	ack.set_code(err::Code::UNKNOWN);
	ack.set_uuid(0);

	// 参数错误
	if (msg.players_size() <= 0)
	{
		ack.set_code(err::Code::PARAM_ERROR);
		SEND_PB_MSG_NO_SESSION(m_pSlaveNode, MessageID::MSG_NEW_FIGHT_ACK, ack);
		return;
	}

	// 服务器过载
	if (this->curFightCount() >= MAX_FIGHT_COUNT)
	{
		ack.set_code(err::Code::OVERLOAD);
		SEND_PB_MSG_NO_SESSION(m_pSlaveNode, MessageID::MSG_NEW_FIGHT_ACK, ack);
		return;
	}

	auto logic = new(std::nothrow) GameLogic();
	// 内存不足
	if (logic == NULL)
	{
		ack.set_code(err::Code::NO_MEMORY);
		SEND_PB_MSG_NO_SESSION(m_pSlaveNode, MessageID::MSG_NEW_FIGHT_ACK, ack);
		return;
	}

	// 初始化失败
	auto code = logic->init(msg.mapid(), msg.players());
	if (code != err::Code::SUCCESS)
	{
		delete logic;
		ack.set_code(code);
		SEND_PB_MSG_NO_SESSION(m_pSlaveNode, MessageID::MSG_NEW_FIGHT_ACK, ack);
		return;
	}
	m_arrFightInfo.push_back(logic);

	ack.set_code(err::Code::SUCCESS);
	ack.set_uuid(logic->uuid());
	SEND_PB_MSG_NO_SESSION(m_pSlaveNode, MessageID::MSG_NEW_FIGHT_ACK, ack);
}


void ServiceFight::onMsg_JoinFightReq(uint32_t sessionID, const msg::JoinFightReq& msg)
{
	msg::JoinFightAck ack;
	ack.set_code(err::Code::UNKNOWN);

	for (auto& it : m_arrFightInfo)
	{
		if (it->uuid() == msg.fightuuid() && it->finish() == false)
		{
			ack.set_code(it->join(sessionID, msg));
			SEND_PB_MSG(m_pNetService, sessionID, MessageID::MSG_JOIN_FIGHT_ACK, ack);
			return;
		}
	}

	// 找不到对应ID
	ack.set_code(err::Code::NOT_FOUND_FIGHT);
	SEND_PB_MSG(m_pNetService, sessionID, MessageID::MSG_JOIN_FIGHT_ACK, ack);
}

void ServiceFight::onMsg_ExitFightReq(uint32_t sessionID, const msg::ExitFightReq& msg)
{
	msg::ExitFightAck ack;
	ack.set_code(err::Code::NOT_FOUND_FIGHT);

	for (auto& it : m_arrFightInfo)
	{
		if (it->uuid() == msg.fightuuid())
		{
			ack.set_code(it->exitGameWithSessionID(sessionID));
			break;
		}
	}

	SEND_PB_MSG(m_pNetService, sessionID, MessageID::MSG_EXIT_FIGHT_ACK, ack);
}
