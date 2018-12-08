#include "KCPClient.h"
#include "KCPCommon.h"
#include "KCPUtils.h"

NS_NET_UV_BEGIN

//断线重连定时器检测间隔
#define KCP_CLIENT_TIMER_DELAY (0.1f)


enum
{
	KCP_CLI_OP_CONNECT,			//	连接
	KCP_CLI_OP_SENDDATA,		// 发送数据
	KCP_CLI_OP_DISCONNECT,		// 断开连接
	KCP_CLI_OP_SET_AUTO_CONNECT,//设置自动连接
	KCP_CLI_OP_SET_RECON_TIME,	//设置重连时间
	KCP_CLI_OP_CLIENT_CLOSE,	//客户端退出
	KCP_CLI_OP_REMOVE_SESSION,	//移除会话命令
	KCP_CLI_OP_DELETE_SESSION,	//删除会话
	KCP_CLI_OP_CREATE_PRE_SOCKET,// 创建预制socket
};

// 连接操作
struct KCPClientConnectOperation
{
	KCPClientConnectOperation() {}
	~KCPClientConnectOperation() {}
	std::string ip;
	uint32_t port;
	uint32_t sessionID;
};

// 设置自动连接操作
struct KCPClientAutoConnectOperation
{
	KCPClientAutoConnectOperation() {}
	~KCPClientAutoConnectOperation() {}
	bool isAuto;
	uint32_t sessionID;
};

// 设置重连时间操作
struct KCPClientReconnectTimeOperation
{
	KCPClientReconnectTimeOperation() {}
	~KCPClientReconnectTimeOperation() {}
	float time;
	uint32_t sessionID;
};


// 创建预制socket返回数据结构
struct KCPClientCreatePreSocketCallData
{
	uint32_t sessionID;
	uint32_t bindPort;
};


//////////////////////////////////////////////////////////////////////////////////
KCPClient::KCPClient()
	: m_reconnect(true)
	, m_totalTime(3.0f)
	, m_isStop(false)
	, m_createPreSocketCall(nullptr)
{
	uv_loop_init(&m_loop);

	m_clientStage = clientStage::START;

	startIdle();
	startSessionUpdate(KCP_HEARTBEAT_TIMER_DELAY);

	uv_timer_init(&m_loop, &m_clientUpdateTimer);
	m_clientUpdateTimer.data = this;
	uv_timer_start(&m_clientUpdateTimer, uv_client_update_timer_run, (uint64_t)(KCP_CLIENT_TIMER_DELAY * 1000), (uint64_t)(KCP_CLIENT_TIMER_DELAY * 1000));

	this->startThread();
}

KCPClient::~KCPClient()
{
	closeClient();
	this->join();
	clearData();
}


void KCPClient::connect(const char* ip, uint32_t port, uint32_t sessionId)
{
	if (m_isStop)
		return;

	assert(ip != NULL);

	KCPClientConnectOperation* opData = (KCPClientConnectOperation*)fc_malloc(sizeof(KCPClientConnectOperation));
	new (opData)KCPClientConnectOperation();

	opData->ip = ip;
	opData->port = port;
	opData->sessionID = sessionId;
	pushOperation(KCP_CLI_OP_CONNECT, opData, 0U, 0U);
}

void KCPClient::closeClient()
{
	if (m_isStop)
		return;
	m_isStop = true;
	pushOperation(KCP_CLI_OP_CLIENT_CLOSE, NULL, 0U, 0U);
}

void KCPClient::updateFrame()
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
			pushOperation(KCP_CLI_OP_DELETE_SESSION, NULL, 0U, Msg.pSession->getSessionID());
		}break;
		case NetThreadMsgType::CREATE_PRE_SOCKET:
		{
			KCPClientCreatePreSocketCallData* pre_data = (KCPClientCreatePreSocketCallData*)Msg.data;
			if (m_createPreSocketCall)
			{
				m_createPreSocketCall(this, pre_data->sessionID, pre_data->bindPort);
			}
			fc_free(pre_data);
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

void KCPClient::removeSession(uint32_t sessionId)
{
	pushOperation(KCP_CLI_OP_REMOVE_SESSION, NULL, 0U, sessionId);
}

/// SessionManager
void KCPClient::send(uint32_t sessionId, char* data, uint32_t len)
{
	if (m_isStop)
		return;

	if (data == 0 || len <= 0)
		return;
	int32_t bufCount = 0;

	uv_buf_t* bufArr = kcp_packageData(data, len, &bufCount);

	if (bufArr == NULL)
		return;

	for (int32_t i = 0; i < bufCount; ++i)
	{
		pushOperation(KCP_CLI_OP_SENDDATA, (bufArr + i)->base, (bufArr + i)->len, sessionId);
	}
	fc_free(bufArr);
}

void KCPClient::disconnect(uint32_t sessionId)
{
	if (m_isStop)
		return;

	pushOperation(KCP_CLI_OP_DISCONNECT, NULL, 0U, sessionId);
}

void KCPClient::setAutoReconnect(bool isAuto)
{
	if (m_isStop)
		return;

	m_reconnect = isAuto;

	KCPClientAutoConnectOperation* opData = (KCPClientAutoConnectOperation*)fc_malloc(sizeof(KCPClientAutoConnectOperation));
	new(opData) KCPClientAutoConnectOperation();

	opData->isAuto = isAuto;
	opData->sessionID = -1;

	pushOperation(KCP_CLI_OP_SET_AUTO_CONNECT, opData, NULL, NULL);
}

void KCPClient::setAutoReconnectTime(float time)
{
	if (m_isStop)
		return;

	m_totalTime = time;

	KCPClientReconnectTimeOperation* opData = (KCPClientReconnectTimeOperation*)fc_malloc(sizeof(KCPClientReconnectTimeOperation));
	new(opData) KCPClientReconnectTimeOperation();

	opData->sessionID = -1;
	opData->time = time;

	pushOperation(KCP_CLI_OP_SET_RECON_TIME, opData, NULL, NULL);
}

void KCPClient::setAutoReconnectBySessionID(uint32_t sessionID, bool isAuto)
{
	if (m_isStop)
		return;

	KCPClientAutoConnectOperation* opData = (KCPClientAutoConnectOperation*)fc_malloc(sizeof(KCPClientAutoConnectOperation));
	new(opData) KCPClientAutoConnectOperation();

	opData->isAuto = isAuto;
	opData->sessionID = sessionID;

	pushOperation(KCP_CLI_OP_SET_AUTO_CONNECT, opData, NULL, NULL);
}

void KCPClient::setAutoReconnectTimeBySessionID(uint32_t sessionID, float time)
{
	if (m_isStop)
		return;

	KCPClientReconnectTimeOperation* opData = (KCPClientReconnectTimeOperation*)fc_malloc(sizeof(KCPClientReconnectTimeOperation));
	new(opData) KCPClientReconnectTimeOperation();

	opData->sessionID = sessionID;
	opData->time = time;

	pushOperation(KCP_CLI_OP_SET_RECON_TIME, opData, NULL, NULL);
}

// 创建预制Socket
void KCPClient::createPrefabricationSocket(uint32_t sessionID)
{
	if (m_isStop)
		return;

	pushOperation(KCP_CLI_OP_CREATE_PRE_SOCKET, NULL, NULL, sessionID);
}

/// Runnable
void KCPClient::run()
{
	uv_run(&m_loop, UV_RUN_DEFAULT);

	uv_loop_close(&m_loop);

	m_clientStage = clientStage::STOP;

	this->pushThreadMsg(NetThreadMsgType::EXIT_LOOP, NULL);
}

/// SessionManager
void KCPClient::executeOperation()
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
		case KCP_CLI_OP_SENDDATA:		// 数据发送
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
		case KCP_CLI_OP_DISCONNECT:	// 断开连接
		{
			auto sessionData = getClientSessionDataBySessionId(curOperation.sessionID);
			if (sessionData->connectState == CONNECT)
			{
				sessionData->connectState = DISCONNECTING;
				sessionData->session->executeDisconnect();
			}
		}break;
		case KCP_CLI_OP_CONNECT:	// 连接
		{
			if (curOperation.operationData)
			{
				createNewConnect(curOperation.operationData);
				((KCPClientConnectOperation*)curOperation.operationData)->~KCPClientConnectOperation();
				fc_free(curOperation.operationData);
			}
		}break;
		case KCP_CLI_OP_SET_AUTO_CONNECT: //设置自动连接
		{
			if (curOperation.operationData)
			{
				KCPClientAutoConnectOperation* opData = (KCPClientAutoConnectOperation*)curOperation.operationData;
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
				opData->~KCPClientAutoConnectOperation();
				fc_free(opData);
			}
		}break;
		case KCP_CLI_OP_SET_RECON_TIME: //设置重连时间
		{
			if (curOperation.operationData)
			{
				KCPClientReconnectTimeOperation* opData = (KCPClientReconnectTimeOperation*)curOperation.operationData;
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
				opData->~KCPClientReconnectTimeOperation();
				fc_free(opData);
			}
		}break;
		case KCP_CLI_OP_CLIENT_CLOSE://客户端关闭
		{
			m_clientStage = clientStage::CLEAR_SESSION;

			// 清空预制socket
			for (auto &it : m_allPrefabricationSocket)
			{
				it.second.socket->~KCPSocket();
				fc_free(it.second.socket);
			}
			m_allPrefabricationSocket.clear();

			stopSessionUpdate();
		}break;
		case KCP_CLI_OP_REMOVE_SESSION:
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
		case KCP_CLI_OP_DELETE_SESSION://删除会话
		{
			auto it = m_allSessionMap.find(curOperation.sessionID);
			if (it != m_allSessionMap.end() && it->second->removeTag)
			{
				it->second->session->~KCPSession();
				fc_free(it->second->session);
				it->second->~clientSessionData();
				fc_free(it->second);
				m_allSessionMap.erase(it);
			}
		}break;
		case KCP_CLI_OP_CREATE_PRE_SOCKET:// 创建预制socket
		{
			auto it = m_allSessionMap.find(curOperation.sessionID);

			if (it == m_allSessionMap.end() || it->second->removeTag)
			{
				auto it_pre = m_allPrefabricationSocket.find(curOperation.sessionID);
				if (it_pre == m_allPrefabricationSocket.end())
				{
					KCPSocket* socket = (KCPSocket*)fc_malloc(sizeof(KCPSocket));
					new (socket)KCPSocket(&m_loop);

					uint32_t bindPort = socket->bind("0.0.0.0", 0);
					if (bindPort == 0)
					{
						socket->~KCPSocket();
						fc_free(socket);
					}
					else
					{
						PrefabricationSocket preData;
						preData.socket = socket;
						preData.bindPort = bindPort;

						m_allPrefabricationSocket.insert(std::make_pair(curOperation.sessionID, preData));
					}
					KCPClientCreatePreSocketCallData* pre_data = (KCPClientCreatePreSocketCallData*)fc_malloc(sizeof(KCPClientCreatePreSocketCallData));
					memset(pre_data, 0, sizeof(KCPClientCreatePreSocketCallData));
					pre_data->bindPort = bindPort;
					pre_data->sessionID = curOperation.sessionID;

					pushThreadMsg(NetThreadMsgType::CREATE_PRE_SOCKET, NULL, (char*)pre_data, 0);
				}
				else
				{
					// 预制socket已存在
					KCPClientCreatePreSocketCallData* pre_data = (KCPClientCreatePreSocketCallData*)fc_malloc(sizeof(KCPClientCreatePreSocketCallData));
					memset(pre_data, 0, sizeof(KCPClientCreatePreSocketCallData));
					pre_data->bindPort = it_pre->second.bindPort;
					pre_data->sessionID = curOperation.sessionID;

					pushThreadMsg(NetThreadMsgType::CREATE_PRE_SOCKET, NULL, (char*)pre_data, 0);
				}
			}
			else
			{
				KCPClientCreatePreSocketCallData* pre_data = (KCPClientCreatePreSocketCallData*)fc_malloc(sizeof(KCPClientCreatePreSocketCallData));
				memset(pre_data, 0, sizeof(KCPClientCreatePreSocketCallData));
				pre_data->bindPort = 0U;
				pre_data->sessionID = curOperation.sessionID;

				// sessionID已存在
				pushThreadMsg(NetThreadMsgType::CREATE_PRE_SOCKET, NULL, (char*)pre_data, 0);
			}
		}break;
		default:
			break;
		}
		m_operationDispatchQue.pop();
	}
}

void KCPClient::onIdleRun()
{
	executeOperation();

	IUINT32 update_clock = iclock();
	for (auto& it : m_allSessionMap)
	{
		it.second->session->updateKcp(update_clock);
	}

	ThreadSleep(1);
}

void KCPClient::onSessionUpdateRun()
{
	for (auto& it : m_allSessionMap)
	{
		it.second->session->update(KCP_HEARTBEAT_TIMER_DELAY);
	}
}

/// KCPClient
void KCPClient::onSocketConnect(Socket* socket, int32_t status)
{
	Session* pSession = NULL;
	bool isSuc = (status == 1);

	for (auto& it : m_allSessionMap)
	{
		if (it.second->session->getKCPSocket() == socket)
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

void KCPClient::onSessionClose(Session* session)
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

void KCPClient::createNewConnect(void* data)
{
	if (data == NULL)
		return;
	KCPClientConnectOperation* opData = (KCPClientConnectOperation*)data;

	auto it = m_allSessionMap.find(opData->sessionID);
	if (it != m_allSessionMap.end())
	{
		if (it->second->removeTag)
			return;

		if (it->second->connectState == CONNECTSTATE::DISCONNECT)
		{
			it->second->ip = opData->ip;
			it->second->port = opData->port;

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
		auto it_pre = m_allPrefabricationSocket.find(opData->sessionID);

		KCPSocket* socket = NULL;
		// 存在预制，则使用预制的socket
		if (it_pre != m_allPrefabricationSocket.end())
		{
			socket = it_pre->second.socket;
			m_allPrefabricationSocket.erase(it_pre);
		}
		else
		{
			socket = (KCPSocket*)fc_malloc(sizeof(KCPSocket));
			new (socket) KCPSocket(&m_loop);
		}
		socket->setConnectCallback(std::bind(&KCPClient::onSocketConnect, this, std::placeholders::_1, std::placeholders::_2));

		KCPSession* session = KCPSession::createSession(this, socket);

		if (session == NULL)
		{
			NET_UV_LOG(NET_UV_L_FATAL, "创建会话失败，可能是内存不足!!!");
			return;
		}
		session->setSessionRecvCallback(std::bind(&KCPClient::onSessionRecvData, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		session->setSessionClose(std::bind(&KCPClient::onSessionClose, this, std::placeholders::_1));
		session->setSessionID(opData->sessionID);
		session->setSendHeartMsg(NET_HEARTBEAT_MSG_C2S);
		session->setHeartMaxCount(KCP_HEARTBEAT_MAX_COUNT_CLIENT);
		session->setResetHeartCount(KCP_HEARTBEAT_COUNT_RESET_VALUE_CLIENT);
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

void KCPClient::onSessionRecvData(Session* session, char* data, uint32_t len)
{
	pushThreadMsg(NetThreadMsgType::RECV_DATA, session, data, len);
}

KCPClient::clientSessionData* KCPClient::getClientSessionDataBySessionId(uint32_t sessionId)
{
	auto it = m_allSessionMap.find(sessionId);
	if (it != m_allSessionMap.end())
		return it->second;
	return NULL;
}

KCPClient::clientSessionData* KCPClient::getClientSessionDataBySession(Session* session)
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

void KCPClient::clearData()
{
	for (auto & it : m_allSessionMap)
	{
		it.second->session->~KCPSession();
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
		case KCP_CLI_OP_SENDDATA:			// 数据发送
		{
			if (curOperation.operationData)
			{
				fc_free(curOperation.operationData);
			}
		}break;
		case KCP_CLI_OP_CONNECT:			// 连接
		{
			if (curOperation.operationData)
			{
				((KCPClientConnectOperation*)curOperation.operationData)->~KCPClientConnectOperation();
				fc_free(curOperation.operationData);
			}
		}break;
		case KCP_CLI_OP_SET_AUTO_CONNECT:	//设置自动连接
		{
			if (curOperation.operationData)
			{
				((KCPClientAutoConnectOperation*)curOperation.operationData)->~KCPClientAutoConnectOperation();
				fc_free(curOperation.operationData);
			}
		}break;
		case KCP_CLI_OP_SET_RECON_TIME:		//设置重连时间
		{
			if (curOperation.operationData)
			{
				((KCPClientReconnectTimeOperation*)curOperation.operationData)->~KCPClientReconnectTimeOperation();
				fc_free(curOperation.operationData);
			}
		}break;
		}
		m_operationQue.pop();
	}

	for (auto &it : m_allPrefabricationSocket)
	{
		it.second.socket->~KCPSocket();
		fc_free(it.second.socket);
	}
	m_allPrefabricationSocket.clear();
}

void KCPClient::onClientUpdate()
{
	if (m_clientStage == clientStage::START)
	{
		clientSessionData* data = NULL;
		for (auto& it : m_allSessionMap)
		{
			data = it.second;
			if (data->connectState == CONNECTSTATE::DISCONNECT && data->reconnect && data->removeTag == false)
			{
				data->curtime = data->curtime + KCP_CLIENT_TIMER_DELAY;

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
void KCPClient::uv_client_update_timer_run(uv_timer_t* handle)
{
	KCPClient* c = (KCPClient*)handle->data;
	c->onClientUpdate();
}

NS_NET_UV_END
