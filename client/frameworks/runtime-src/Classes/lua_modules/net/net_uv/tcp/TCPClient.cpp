#include "TCPClient.h"
#include "TCPCommon.h"
#include "TCPUtils.h"

NS_NET_UV_BEGIN

//断线重连定时器检测间隔
#define TCP_CLIENT_TIMER_DELAY (0.1f)


enum 
{
	TCP_CLI_OP_CONNECT,			//	连接
	TCP_CLI_OP_SENDDATA,		// 发送数据
	TCP_CLI_OP_DISCONNECT,		// 断开连接
	TCP_CLI_OP_SET_AUTO_CONNECT,//设置自动连接
	TCP_CLI_OP_SET_RECON_TIME,	//设置重连时间
	TCP_CLI_OP_SET_KEEP_ALIVE,	//设置心跳
	TCP_CLI_OP_SET_NO_DELAY,	//设置NoDelay
	TCP_CLI_OP_CLIENT_CLOSE,	//客户端退出
	TCP_CLI_OP_REMOVE_SESSION,	//移除会话命令
	TCP_CLI_OP_DELETE_SESSION,	//删除会话
};

// 连接操作
struct TCPClientConnectOperation
{
	TCPClientConnectOperation() {}
	~TCPClientConnectOperation() {}
	std::string ip;
	uint32_t port;
	uint32_t sessionID;
};

// 设置自动连接操作
struct TCPClientAutoConnectOperation
{
	TCPClientAutoConnectOperation() {}
	~TCPClientAutoConnectOperation() {}
	bool isAuto;
	uint32_t sessionID;
};

// 设置重连时间操作
struct TCPClientReconnectTimeOperation
{
	TCPClientReconnectTimeOperation() {}
	~TCPClientReconnectTimeOperation() {}
	float time;
	uint32_t sessionID;
};




//////////////////////////////////////////////////////////////////////////////////
TCPClient::TCPClient()
	: m_reconnect(true)
	, m_totalTime(3.0f)
#if TCP_USE_NET_UV_MSG_STRUCT == 0
	, m_enableNoDelay(true)
#else
	, m_enableNoDelay(false)
#endif
	, m_enableKeepAlive(true)
	, m_keepAliveDelay(10)
	, m_isStop(false)
{
	uv_loop_init(&m_loop);
	
	m_clientStage = clientStage::START;
	
	startIdle();
	startSessionUpdate(TCP_HEARTBEAT_TIMER_DELAY);

	uv_timer_init(&m_loop, &m_clientUpdateTimer);
	m_clientUpdateTimer.data = this;
	uv_timer_start(&m_clientUpdateTimer, uv_client_update_timer_run, (uint64_t)(TCP_CLIENT_TIMER_DELAY * 1000), (uint64_t)(TCP_CLIENT_TIMER_DELAY * 1000));

	this->startThread();
}

TCPClient::~TCPClient()
{
	closeClient();
	this->join();
	clearData();
}


void TCPClient::connect(const char* ip, uint32_t port, uint32_t sessionId)
{
	if (m_isStop)
		return;

	assert(ip != NULL);

	TCPClientConnectOperation* opData = (TCPClientConnectOperation*)fc_malloc(sizeof(TCPClientConnectOperation));
	new (opData)TCPClientConnectOperation();

	opData->ip = ip;
	opData->port = port;
	opData->sessionID = sessionId;
	pushOperation(TCP_CLI_OP_CONNECT, opData, 0U, 0U);
}

void TCPClient::closeClient()
{
	if (m_isStop)
		return;
	m_isStop = true;
	pushOperation(TCP_CLI_OP_CLIENT_CLOSE, NULL, 0U, 0U);
}

void TCPClient::updateFrame()
{
	if (m_msgMutex.trylock() != 0)
	{
		return;
	}

	if (m_msgQue.empty())
	{
		m_msgMutex.unlock();
		return;
	}

	while (!m_msgQue.empty())
	{
		m_msgDispatchQue.push(m_msgQue.front());
		m_msgQue.pop();
	}
	m_msgMutex.unlock();

	bool closeClientTag = false;
	while (!m_msgDispatchQue.empty())
	{
		const NetThreadMsg& Msg = m_msgDispatchQue.front();
		switch (Msg.msgType)
		{
		case NetThreadMsgType::RECV_DATA:
		{
			m_recvCall(this, Msg.pSession, Msg.data, Msg.dataLen);
			fc_free(Msg.data);
		}break;
		case NetThreadMsgType::CONNECT_FAIL:
		{
			if (m_connectCall != nullptr)
			{
				m_connectCall(this, Msg.pSession, 0);
			}
		}break;
		case NetThreadMsgType::CONNECT:
		{
			if (m_connectCall != nullptr)
			{
				m_connectCall(this, Msg.pSession, 1);
			}
		}break;
		case NetThreadMsgType::CONNECT_TIMOUT:
		{
			if (m_connectCall != nullptr)
			{
				m_connectCall(this, Msg.pSession, 2);
			}
		}break;
		case NetThreadMsgType::DIS_CONNECT:
		{
			if (m_disconnectCall != nullptr)
			{
				m_disconnectCall(this, Msg.pSession);
			}
		}break;
		case NetThreadMsgType::EXIT_LOOP:
		{
			closeClientTag = true;
		}break;
		case NetThreadMsgType::REMOVE_SESSION:
		{
			if (m_removeSessionCall != nullptr)
			{
				m_removeSessionCall(this, Msg.pSession);
			}
			pushOperation(TCP_CLI_OP_DELETE_SESSION, NULL, 0U, Msg.pSession->getSessionID());
		}break;
		default:
			break;
		}
		m_msgDispatchQue.pop();
	}
	if (closeClientTag && m_clientCloseCall != nullptr)
	{
		m_clientCloseCall(this);
	}
}

void TCPClient::removeSession(uint32_t sessionId)
{
	pushOperation(TCP_CLI_OP_REMOVE_SESSION, NULL, 0U, sessionId);
}

/// SessionManager

void TCPClient::disconnect(uint32_t sessionId)
{
	if (m_isStop)
		return;

	pushOperation(TCP_CLI_OP_DISCONNECT, NULL, 0U, sessionId);
}

void TCPClient::send(uint32_t sessionId, char* data, uint32_t len)
{
	if (m_isStop)
		return;

	if (data == 0 || len <= 0)
		return;
	int32_t bufCount = 0;

	uv_buf_t* bufArr = tcp_packageData(data, len, &bufCount);

	if (bufArr == NULL)
		return;

	for (int32_t i = 0; i < bufCount; ++i)
	{
		pushOperation(TCP_CLI_OP_SENDDATA, (bufArr + i)->base, (bufArr + i)->len, sessionId);
	}
	fc_free(bufArr);
}

/// TCPClient
bool TCPClient::isCloseFinish()
{
	return (m_clientStage == clientStage::STOP);
}

bool TCPClient::setSocketNoDelay(bool enable)
{
	if (m_isStop)
		return false;

#if TCP_USE_NET_UV_MSG_STRUCT == 0
	return true;
#else
	m_enableNoDelay = enable;
	pushOperation(TCP_CLI_OP_SET_NO_DELAY, NULL, 0U, 0U);
	return true;
#endif	
}

bool TCPClient::setSocketKeepAlive(int32_t enable, uint32_t delay)
{
	if (m_isStop)
		return false;

	m_enableKeepAlive = enable;
	m_keepAliveDelay = delay;
	
	pushOperation(TCP_CLI_OP_SET_KEEP_ALIVE, NULL, 0U, 0U);
	return true;
}

void TCPClient::setAutoReconnect(bool isAuto)
{
	if (m_isStop)
		return;

	m_reconnect = isAuto;

	TCPClientAutoConnectOperation* opData = (TCPClientAutoConnectOperation*)fc_malloc(sizeof(TCPClientAutoConnectOperation));
	new(opData) TCPClientAutoConnectOperation();

	opData->isAuto = isAuto;
	opData->sessionID = -1;

	pushOperation(TCP_CLI_OP_SET_AUTO_CONNECT, opData, NULL, NULL);
}

void TCPClient::setAutoReconnectTime(float time)
{
	if (m_isStop)
		return;

	m_totalTime = time;

	TCPClientReconnectTimeOperation* opData = (TCPClientReconnectTimeOperation*)fc_malloc(sizeof(TCPClientReconnectTimeOperation));
	new(opData) TCPClientReconnectTimeOperation();

	opData->sessionID = -1;
	opData->time = time;

	pushOperation(TCP_CLI_OP_SET_RECON_TIME, opData, NULL, NULL);
}

void TCPClient::setAutoReconnectBySessionID(uint32_t sessionID, bool isAuto)
{
	if (m_isStop)
		return;

	TCPClientAutoConnectOperation* opData = (TCPClientAutoConnectOperation*)fc_malloc(sizeof(TCPClientAutoConnectOperation));
	new(opData) TCPClientAutoConnectOperation();

	opData->isAuto = isAuto;
	opData->sessionID = sessionID;

	pushOperation(TCP_CLI_OP_SET_AUTO_CONNECT, opData, NULL, NULL);
}

void TCPClient::setAutoReconnectTimeBySessionID(uint32_t sessionID, float time)
{
	if (m_isStop)
		return;

	TCPClientReconnectTimeOperation* opData = (TCPClientReconnectTimeOperation*)fc_malloc(sizeof(TCPClientReconnectTimeOperation));
	new(opData) TCPClientReconnectTimeOperation();

	opData->sessionID = sessionID;
	opData->time = time;

	pushOperation(TCP_CLI_OP_SET_RECON_TIME, opData, NULL, NULL);
}

/// Runnable
void TCPClient::run()
{
	uv_run(&m_loop, UV_RUN_DEFAULT);

	uv_loop_close(&m_loop);

	m_clientStage = clientStage::STOP;

	this->pushThreadMsg(NetThreadMsgType::EXIT_LOOP, NULL);
}

/// SessionManager
void TCPClient::executeOperation()
{
	if (m_operationMutex.trylock() != 0)
	{
		return;
	}

	if (m_operationQue.empty())
	{
		m_operationMutex.unlock();
		return;
	}

	while (!m_operationQue.empty())
	{
		m_operationDispatchQue.push(m_operationQue.front());
		m_operationQue.pop();
	}
	m_operationMutex.unlock();

	while (!m_operationDispatchQue.empty())
	{
		auto & curOperation = m_operationDispatchQue.front();
		switch (curOperation.operationType)
		{
		case TCP_CLI_OP_SENDDATA:		// 数据发送
		{
			auto sessionData = getClientSessionDataBySessionId(curOperation.sessionID);
			if (sessionData && !sessionData->removeTag)
			{
				sessionData->session->executeSend((char*)curOperation.operationData, curOperation.operationDataLen);
			}
			else
			{
				fc_free(curOperation.operationData);
			}
		}break;
		case TCP_CLI_OP_DISCONNECT:	// 断开连接
		{
			auto sessionData = getClientSessionDataBySessionId(curOperation.sessionID);
			if (sessionData->connectState == CONNECT)
			{
				sessionData->connectState = DISCONNECTING;
				sessionData->session->executeDisconnect();
			}
		}break;
		case TCP_CLI_OP_CONNECT:	// 连接
		{
			if (curOperation.operationData)
			{
				createNewConnect(curOperation.operationData);
				((TCPClientConnectOperation*)curOperation.operationData)->~TCPClientConnectOperation();
				fc_free(curOperation.operationData);
			}
		}break;
		case TCP_CLI_OP_SET_AUTO_CONNECT: //设置自动连接
		{
			if (curOperation.operationData)
			{
				TCPClientAutoConnectOperation* opData = (TCPClientAutoConnectOperation*)curOperation.operationData;
				if (opData->sessionID == -1)
				{
					for (auto& it : m_allSessionMap)
					{
						it.second->reconnect = opData->isAuto;
					}
				}
				else
				{
					auto sessionData = getClientSessionDataBySessionId(opData->sessionID);
					if (sessionData)
					{
						sessionData->reconnect = opData->isAuto;
					}
				}
				opData->~TCPClientAutoConnectOperation();
				fc_free(opData);
			}
		}break;
		case TCP_CLI_OP_SET_RECON_TIME: //设置重连时间
		{
			if (curOperation.operationData)
			{
				TCPClientReconnectTimeOperation* opData = (TCPClientReconnectTimeOperation*)curOperation.operationData;
				if (opData->sessionID == -1)
				{
					for (auto& it : m_allSessionMap)
					{
						it.second->totaltime = opData->time;
					}
				}
				else
				{
					auto sessionData = getClientSessionDataBySessionId(opData->sessionID);
					if (sessionData)
					{
						sessionData->totaltime = opData->time;
					}
				}
				opData->~TCPClientReconnectTimeOperation();
				fc_free(opData);
			}
		}break;
		case TCP_CLI_OP_SET_KEEP_ALIVE: //心跳设置
		{
			for (auto& it : m_allSessionMap)
			{
				auto socket = it.second->session->getTCPSocket();
				if (socket && !it.second->removeTag)
				{
					socket->setKeepAlive(m_enableKeepAlive, m_keepAliveDelay);
				}
			}
		}break;
		case TCP_CLI_OP_SET_NO_DELAY:// 设置nodelay
		{
			for (auto& it : m_allSessionMap)
			{
				auto socket = it.second->session->getTCPSocket();
				if (socket && !it.second->removeTag)
				{
					socket->setNoDelay(m_enableNoDelay);
				}
			}
		}break;
		case TCP_CLI_OP_CLIENT_CLOSE://客户端关闭
		{
			m_clientStage = clientStage::CLEAR_SESSION;
			stopSessionUpdate();
		}break;
		case TCP_CLI_OP_REMOVE_SESSION:
		{
			auto sessionData = getClientSessionDataBySessionId(curOperation.sessionID);
			if (sessionData)
			{
				if (sessionData->connectState != DISCONNECT)
				{
					sessionData->removeTag = true;
					sessionData->session->executeDisconnect();
				}
				else
				{
					if (!sessionData->removeTag)
					{
						sessionData->removeTag = true;
						pushThreadMsg(NetThreadMsgType::REMOVE_SESSION, sessionData->session);
					}
				}
			}
		}break;
		case TCP_CLI_OP_DELETE_SESSION://删除会话
		{
			auto it = m_allSessionMap.find(curOperation.sessionID);
			if (it != m_allSessionMap.end() && it->second->removeTag)
			{
				it->second->session->~TCPSession();
				fc_free(it->second->session);
				it->second->~clientSessionData();
				fc_free(it->second);
				m_allSessionMap.erase(it);
			}
		}break;
		default:
			break;
		}
		m_operationDispatchQue.pop();
	}
}

void TCPClient::onIdleRun()
{
	executeOperation();
	ThreadSleep(1);
}

void TCPClient::onSessionUpdateRun()
{
	for (auto& it : m_allSessionMap)
	{
		it.second->session->update(TCP_HEARTBEAT_TIMER_DELAY);
	}
}

/// TCPClient
void TCPClient::onSocketConnect(Socket* socket, int32_t status)
{
	Session* pSession = NULL;
	bool isSuc = (status == 1);

	for (auto& it : m_allSessionMap)
	{
		if (it.second->session->getTCPSocket() == socket)
		{
			pSession = it.second->session;
			it.second->session->setIsOnline(isSuc);
			it.second->connectState = isSuc ? CONNECTSTATE::CONNECT : CONNECTSTATE::DISCONNECT;

			if (isSuc)
			{
				if (m_clientStage != clientStage::START)
				{
					it.second->session->executeDisconnect();
					pSession = NULL;
				}
				else
				{
					if (it.second->removeTag)
					{
						it.second->session->executeDisconnect();
						pSession = NULL;
					}
					else
					{
						it.second->session->getTCPSocket()->setNoDelay(m_enableNoDelay);
						it.second->session->getTCPSocket()->setKeepAlive(m_enableKeepAlive, m_keepAliveDelay);
					}
				}
			}
			break;
		}
	}

	if (pSession)
	{
		if (status == 0)
		{
			pushThreadMsg(NetThreadMsgType::CONNECT_FAIL, pSession);
		}
		else if (status == 1)
		{
			pushThreadMsg(NetThreadMsgType::CONNECT, pSession);
		}
		else if (status == 2)
		{
			pushThreadMsg(NetThreadMsgType::CONNECT_TIMOUT, pSession);
		}
	}
}

void TCPClient::onSessionClose(Session* session)
{
	auto sessionData = getClientSessionDataBySession(session);
	if (sessionData)
	{
		sessionData->connectState = CONNECTSTATE::DISCONNECT;
		pushThreadMsg(NetThreadMsgType::DIS_CONNECT, sessionData->session);

		if (sessionData->removeTag)
		{
			pushThreadMsg(NetThreadMsgType::REMOVE_SESSION, sessionData->session);
		}
	}
}

void TCPClient::createNewConnect(void* data)
{
	if (data == NULL)
		return;
	TCPClientConnectOperation* opData = (TCPClientConnectOperation*)data;

	auto it = m_allSessionMap.find(opData->sessionID);
	if (it != m_allSessionMap.end())
	{
		if (it->second->removeTag)
			return;

		if (it->second->connectState == CONNECTSTATE::DISCONNECT)
		{
			if (it->second->session->executeConnect(opData->ip.c_str(), opData->port))
			{
				it->second->connectState = CONNECTSTATE::CONNECTING;
			}
			else
			{
				it->second->connectState = CONNECTSTATE::DISCONNECT;
				it->second->session->executeDisconnect();
				pushThreadMsg(NetThreadMsgType::CONNECT_FAIL, it->second->session);
			}
		}
	}
	else
	{
		TCPSocket* socket = (TCPSocket*)fc_malloc(sizeof(TCPSocket));
		new (socket) TCPSocket(&m_loop); 
		socket->setConnectCallback(std::bind(&TCPClient::onSocketConnect, this, std::placeholders::_1, std::placeholders::_2));

		TCPSession* session = TCPSession::createSession(this, socket);

		if (session == NULL)
		{
			NET_UV_LOG(NET_UV_L_FATAL, "创建会话失败，可能是内存不足!!!");
			return;
		}
		session->setSessionRecvCallback(std::bind(&TCPClient::onSessionRecvData, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		session->setSessionClose(std::bind(&TCPClient::onSessionClose, this, std::placeholders::_1));
		session->setSessionID(opData->sessionID);
		session->setSendHeartMsg(NET_HEARTBEAT_MSG_C2S);
		session->setHeartMaxCount(TCP_HEARTBEAT_MAX_COUNT_CLIENT);
		session->setResetHeartCount(TCP_HEARTBEAT_COUNT_RESET_VALUE_CLIENT);
		session->setIsOnline(false);
		
		clientSessionData* cs = (clientSessionData*)fc_malloc(sizeof(clientSessionData));
		new (cs) clientSessionData();
		cs->removeTag = false;
		cs->ip = opData->ip;
		cs->port = opData->port;
		cs->session = session;
		cs->curtime = 0;
		cs->reconnect = m_reconnect;
		cs->totaltime = m_totalTime;
		cs->connectState = CONNECTSTATE::CONNECTING;

		m_allSessionMap.insert(std::make_pair(opData->sessionID, cs));
		
		if (socket->connect(opData->ip.c_str(), opData->port))
		{
			cs->connectState = CONNECTSTATE::CONNECTING;
		}
		else
		{
			cs->connectState = CONNECTSTATE::DISCONNECT;
			pushThreadMsg(NetThreadMsgType::CONNECT_FAIL, session);
		}
	}
}

void TCPClient::onSessionRecvData(Session* session, char* data, uint32_t len)
{
	pushThreadMsg(NetThreadMsgType::RECV_DATA, session, data, len);
}

TCPClient::clientSessionData* TCPClient::getClientSessionDataBySessionId(uint32_t sessionId)
{
	auto it = m_allSessionMap.find(sessionId);
	if (it != m_allSessionMap.end())
		return it->second;
	return NULL;
}

TCPClient::clientSessionData* TCPClient::getClientSessionDataBySession(Session* session)
{
	for (auto &it : m_allSessionMap)
	{
		if (it.second->session == session)
		{
			return it.second;
		}
	}
	return NULL;
}

void TCPClient::clearData()
{
	for (auto & it : m_allSessionMap)
	{
		it.second->session->~TCPSession();
		fc_free(it.second->session);
		it.second->~clientSessionData();
		fc_free(it.second);
	}
	m_allSessionMap.clear();

	m_msgMutex.lock();
	while (!m_msgQue.empty())
	{
		if (m_msgQue.front().data)
		{
			fc_free(m_msgQue.front().data);
		}
		m_msgQue.pop();
	}
	m_msgMutex.unlock();

	while (!m_operationQue.empty())
	{
		auto & curOperation = m_operationQue.front();
		switch (curOperation.operationType)
		{
		case TCP_CLI_OP_SENDDATA:			// 数据发送
		{
			if (curOperation.operationData)
			{
				fc_free(curOperation.operationData);
			}
		}break;
		case TCP_CLI_OP_CONNECT:			// 连接
		{
			if (curOperation.operationData)
			{
				((TCPClientConnectOperation*)curOperation.operationData)->~TCPClientConnectOperation();
				fc_free(curOperation.operationData);
			}
		}break;
		case TCP_CLI_OP_SET_AUTO_CONNECT:	//设置自动连接
		{
			if (curOperation.operationData)
			{
				((TCPClientAutoConnectOperation*)curOperation.operationData)->~TCPClientAutoConnectOperation();
				fc_free(curOperation.operationData);
			}
		}break;
		case TCP_CLI_OP_SET_RECON_TIME:		//设置重连时间
		{
			if (curOperation.operationData)
			{
				((TCPClientReconnectTimeOperation*)curOperation.operationData)->~TCPClientReconnectTimeOperation();
				fc_free(curOperation.operationData);
			}
		}break;
		}
		m_operationQue.pop();
	}
}

void TCPClient::onClientUpdate()
{
	if (m_clientStage == clientStage::START)
	{
		clientSessionData* data = NULL;
		for (auto& it : m_allSessionMap)
		{
			data = it.second;
			if (data->connectState == CONNECTSTATE::DISCONNECT && data->reconnect && data->removeTag == false)
			{
				data->curtime = data->curtime + TCP_CLIENT_TIMER_DELAY;

				if (data->curtime >= data->totaltime)
				{
					data->curtime = 0.0f;
					if (data->session->executeConnect(data->ip.c_str(), data->port))
					{
						data->connectState = CONNECTSTATE::CONNECTING;
					}
					else
					{
						data->connectState = CONNECTSTATE::DISCONNECT;
					}
				}
			}
		}
	}
	else if (m_clientStage == clientStage::CLEAR_SESSION)
	{
		clientSessionData* data = NULL;
		for (auto& it : m_allSessionMap)
		{
			data = it.second;

			if (data->connectState == CONNECT)
			{
				data->removeTag = true;
				data->session->executeDisconnect();
			}
			else if (data->connectState == DISCONNECT)
			{
				if (!data->removeTag)
				{
					data->removeTag = true;
					pushThreadMsg(NetThreadMsgType::REMOVE_SESSION, data->session);
				}
			}
		}
		if (m_allSessionMap.empty())
		{
			m_clientStage = clientStage::WAIT_EXIT;
		}
	}
	else if (m_clientStage == clientStage::WAIT_EXIT)
	{
		stopIdle();
		uv_timer_stop(&m_clientUpdateTimer);
		uv_stop(&m_loop);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TCPClient::uv_client_update_timer_run(uv_timer_t* handle)
{
	TCPClient* c = (TCPClient*)handle->data;
	c->onClientUpdate();
}

NS_NET_UV_END
