#include "KCPServer.h"
#include "KCPUtils.h"

NS_NET_UV_BEGIN

enum
{
	KCP_SVR_OP_STOP_SERVER,	// 停止服务器
	KCP_SVR_OP_SEND_DATA,	// 发送消息给某个会话
	KCP_SVR_OP_DIS_SESSION,	// 断开某个会话
	KCP_SVR_OP_SEND_DIS_SESSION_MSG_TO_MAIN_THREAD,//向主线程发送会话已断开
	KCP_SVR_OP_SVR_SOCKET_SEND,//服务器socket发送数据
};

// 连接操作
struct KCPServerSVRSendOperation
{
	KCPServerSVRSendOperation() {}
	~KCPServerSVRSendOperation() {}
	char addrData[sizeof(sockaddr_in6) * 2];
	char* sendData;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

KCPServer::KCPServer()
	: m_start(false)
	, m_server(NULL)
{
}

KCPServer::~KCPServer()
{
	stopServer();
	this->join();
	clearData();

	NET_UV_LOG(NET_UV_L_INFO, "KCPServer destroy...");
}

bool KCPServer::startServer(const char* ip, uint32_t port, bool isIPV6)
{
	if (m_serverStage != ServerStage::STOP || m_start)
	{
		return false;
	}

	Server::startServer(ip, port, isIPV6);

	int32_t r = uv_loop_init(&m_loop);
	CHECK_UV_ASSERT(r);

	m_server = (KCPSocket*)fc_malloc(sizeof(KCPSocket));
	if (m_server == NULL)
	{
		return false;
	}

	new (m_server) KCPSocket(&m_loop);
	m_server->setCloseCallback(std::bind(&KCPServer::onServerSocketClose, this, std::placeholders::_1));
	m_server->setNewConnectionCallback(std::bind(&KCPServer::onNewConnect, this, std::placeholders::_1));
	m_server->setConnectFilterCallback(std::bind(&KCPServer::onServerSocketConnectFilter, this, std::placeholders::_1));

	uint32_t bindPort = 0;
	if (m_isIPV6)
	{
		bindPort = m_server->bind6(m_ip.c_str(), m_port);
	}
	else
	{
		bindPort = m_server->bind(m_ip.c_str(), m_port);
	}

	if (bindPort == 0)
	{
		startFailureLogic();
		return false;
	}

	bool suc = m_server->listen();
	if (!suc)
	{
		startFailureLogic();
		return false;
	}
	NET_UV_LOG(NET_UV_L_INFO, "KCPServer %s:%u start-up...", ip, bindPort);

	m_start = true;
	m_serverStage = ServerStage::RUN;

	setListenPort(bindPort);
	startThread();

	return true;
}

bool KCPServer::stopServer()
{
	if (!m_start)
	{
		return false;
	}

	m_start = false;
	pushOperation(KCP_SVR_OP_STOP_SERVER, NULL, NULL, 0U);
	return true;
}

void KCPServer::updateFrame()
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

	bool closeServerTag = false;
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
		case NetThreadMsgType::NEW_CONNECT:
		{
			m_newConnectCall(this, Msg.pSession);
		}break;
		case NetThreadMsgType::DIS_CONNECT:
		{
			m_disconnectCall(this, Msg.pSession);
			pushOperation(KCP_SVR_OP_SEND_DIS_SESSION_MSG_TO_MAIN_THREAD, NULL, 0, Msg.pSession->getSessionID());
		}break;
		case NetThreadMsgType::EXIT_LOOP:
		{
			closeServerTag = true;
		}break;
		default:
			break;
		}
		m_msgDispatchQue.pop();
	}
	if (closeServerTag && m_closeCall != nullptr)
	{
		m_closeCall(this);
	}
}

void KCPServer::send(uint32_t sessionID, char* data, uint32_t len)
{
	int32_t bufCount = 0;

	uv_buf_t* bufArr = kcp_packageData(data, len, &bufCount);

	if (bufArr == NULL)
		return;

	for (int32_t i = 0; i < bufCount; ++i)
	{
		pushOperation(KCP_SVR_OP_SEND_DATA, (bufArr + i)->base, (bufArr + i)->len, sessionID);
	}
	fc_free(bufArr);
}

void KCPServer::disconnect(uint32_t sessionID)
{
	pushOperation(KCP_SVR_OP_DIS_SESSION, NULL, 0, sessionID);
}

/// KCPServer
bool KCPServer::svrUdpSend(const char* ip, uint32_t port, bool isIPV6, char* data, uint32_t len)
{
	uint32_t addrlen;
	struct sockaddr* addr = net_getsocketAddr_no(ip, port, isIPV6, &addrlen);

	if (addr == NULL)
		return false;

	bool ret = svrUdpSend(addr, addrlen, data, len);

	fc_free(addr);

	return ret;
}

bool KCPServer::svrUdpSend(struct sockaddr* addr, uint32_t addrlen, char* data, uint32_t len)
{
	if (addr == NULL || data == NULL || len <= 0)
		return false;

	KCPServerSVRSendOperation* opData = (KCPServerSVRSendOperation*)fc_malloc(sizeof(KCPServerSVRSendOperation));
	new (opData)KCPServerSVRSendOperation();

	memset(opData->addrData, 0, sizeof(sockaddr_in6) * 2);
	memcpy(opData, addr, addrlen);

	opData->sendData = (char*)fc_malloc(len);
	memcpy(opData->sendData, data, len);

	pushOperation(KCP_SVR_OP_SVR_SOCKET_SEND, opData, len, 0U);

	return true;
}

void KCPServer::run()
{
	startIdle();
	startSessionUpdate(KCP_HEARTBEAT_TIMER_DELAY);

	uv_run(&m_loop, UV_RUN_DEFAULT);

	if (m_server)
	{
		m_server->~KCPSocket();
		fc_free(m_server);
		m_server = NULL;
	}

	uv_loop_close(&m_loop);

	m_serverStage = ServerStage::STOP;
	pushThreadMsg(NetThreadMsgType::EXIT_LOOP, NULL);
}

void KCPServer::onNewConnect(Socket* socket)
{
	if (socket != NULL)
	{
		KCPSession* session = KCPSession::createSession(this, (KCPSocket*)socket);
		if (session == NULL)
		{
			NET_UV_LOG(NET_UV_L_ERROR, "服务器创建新会话失败,可能是内存不足");
		}
		else
		{
			session->setSessionRecvCallback(std::bind(&KCPServer::onSessionRecvData, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
			session->setSessionClose(std::bind(&KCPServer::onSessionClose, this, std::placeholders::_1));
			session->setSendHeartMsg(NET_HEARTBEAT_MSG_S2C);
			session->setHeartMaxCount(KCP_HEARTBEAT_MAX_COUNT_SERVER);
			session->setResetHeartCount(KCP_HEARTBEAT_COUNT_RESET_VALUE_SERVER);
			session->setSessionID(((KCPSocket*)socket)->getConv());
			session->setIsOnline(true);
			addNewSession(session);
		}
	}
	else
	{
		NET_UV_LOG(NET_UV_L_ERROR, "接受新连接失败");
	}
}

void KCPServer::onServerSocketClose(Socket* svr)
{
	m_serverStage = ServerStage::CLEAR;
}

bool KCPServer::onServerSocketConnectFilter(const struct sockaddr* addr)
{
	return true;
}

void KCPServer::startFailureLogic()
{
	m_server->~KCPSocket();
	fc_free(m_server);
	m_server = NULL;

	uv_run(&m_loop, UV_RUN_DEFAULT);

	uv_loop_close(&m_loop);

	m_serverStage = ServerStage::STOP;
}

void KCPServer::addNewSession(KCPSession* session)
{
	if (session == NULL)
	{
		return;
	}
	serverSessionData data;
	data.isInvalid = false;
	data.session = session;

	m_allSession.insert(std::make_pair(session->getSessionID(), data));

	pushThreadMsg(NetThreadMsgType::NEW_CONNECT, session);
}

void KCPServer::onSessionClose(Session* session)
{
	if (session == NULL)
	{
		return;
	}
	auto it = m_allSession.find(session->getSessionID());
	if (it != m_allSession.end())
	{
		it->second.isInvalid = true;
		pushThreadMsg(NetThreadMsgType::DIS_CONNECT, session);
	}
}

void KCPServer::onSessionRecvData(Session* session, char* data, uint32_t len)
{
	pushThreadMsg(NetThreadMsgType::RECV_DATA, session, data, len);
}

void KCPServer::executeOperation()
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
		case KCP_SVR_OP_SEND_DATA:		// 数据发送
		{
			auto it = m_allSession.find(curOperation.sessionID);
			if (it != m_allSession.end())
			{
				it->second.session->executeSend((char*)curOperation.operationData, curOperation.operationDataLen);
			}
			else//该会话已失效
			{
				fc_free(curOperation.operationData);
			}
		}break;
		case KCP_SVR_OP_DIS_SESSION:	// 断开连接
		{
			auto it = m_allSession.find(curOperation.sessionID);
			if (it != m_allSession.end())
			{
				it->second.session->executeDisconnect();
			}
		}break;
		case KCP_SVR_OP_SEND_DIS_SESSION_MSG_TO_MAIN_THREAD:
		{
			auto it = m_allSession.find(curOperation.sessionID);
			if (it != m_allSession.end())
			{
				it->second.session->~KCPSession();
				fc_free(it->second.session);
				it = m_allSession.erase(it);
			}
		}break;
		case KCP_SVR_OP_STOP_SERVER:
		{
			for (auto & it : m_allSession)
			{
				if (!it.second.isInvalid)
				{
					it.second.session->executeDisconnect();
				}
			}
			m_server->disconnect();
			m_serverStage = ServerStage::WAIT_CLOSE_SERVER_SOCKET;

			stopSessionUpdate();
		}break;
		case KCP_SVR_OP_SVR_SOCKET_SEND:
		{
			KCPServerSVRSendOperation* opData = (KCPServerSVRSendOperation*)curOperation.operationData;
			m_server->udpSend((const char*)opData->sendData, curOperation.operationDataLen, (const struct sockaddr*)opData->addrData);
			
			fc_free(opData->sendData); 
			opData->~KCPServerSVRSendOperation();
			fc_free(opData);
		}break;
		default:
			break;
		}
		m_operationDispatchQue.pop();
	}
}

void KCPServer::clearData()
{
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
		const auto& curOpration = m_operationQue.front();
		if (curOpration.operationType == KCP_SVR_OP_SEND_DATA)
		{
			fc_free(curOpration.operationData);
		}
		else if (curOpration.operationType == KCP_SVR_OP_SVR_SOCKET_SEND)
		{
			KCPServerSVRSendOperation* opData = (KCPServerSVRSendOperation*)curOpration.operationData;
			fc_free(opData->sendData);
			opData->~KCPServerSVRSendOperation();
			fc_free(opData);
		}
		m_operationQue.pop();
	}
}

void KCPServer::onIdleRun()
{
	m_server->svrIdleRun();

	executeOperation();

	switch (m_serverStage)
	{
	case ServerStage::CLEAR:
	{
		for (auto& it : m_allSession)
		{
			if (!it.second.isInvalid)
			{
				it.second.session->executeDisconnect();
			}
		}
		m_serverStage = ServerStage::WAIT_SESSION_CLOSE;
	}
	break;
	case ServerStage::WAIT_SESSION_CLOSE:
	{
		if (m_allSession.empty())
		{
			m_server->~KCPSocket();
			fc_free(m_server);
			m_server = NULL;

			stopIdle();
			uv_stop(&m_loop);
		}
	}
	break;
	default:
		break;
	}

	ThreadSleep(1);
}

void KCPServer::onSessionUpdateRun()
{
	for (auto& it : m_allSession)
	{
		it.second.session->update(KCP_HEARTBEAT_TIMER_DELAY);
	}
}

NS_NET_UV_END