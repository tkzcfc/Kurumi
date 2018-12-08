#include "TCPServer.h"
#include "TCPUtils.h"

NS_NET_UV_BEGIN

enum 
{
	TCP_SVR_OP_STOP_SERVER,	// 停止服务器
	TCP_SVR_OP_SEND_DATA,	// 发送消息给某个会话
	TCP_SVR_OP_DIS_SESSION,	// 断开某个会话
	TCP_SVR_OP_SEND_DIS_SESSION_MSG_TO_MAIN_THREAD,//向主线程发送会话已断开
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////

TCPServer::TCPServer()
	: m_start(false)
	, m_server(NULL)
	, m_sessionID(0)
{
}

TCPServer::~TCPServer()
{
	stopServer();
	this->join();
	clearData();

	NET_UV_LOG(NET_UV_L_INFO, "TCPServer destroy...");
}

bool TCPServer::startServer(const char* ip, uint32_t port, bool isIPV6)
{
	if (m_serverStage != ServerStage::STOP || m_start)
	{
		return false;
	}

	Server::startServer(ip, port, isIPV6);

	int32_t r = uv_loop_init(&m_loop);
	CHECK_UV_ASSERT(r);

	m_server = (TCPSocket*)fc_malloc(sizeof(TCPSocket));
	if (m_server == NULL)
	{
		return false;
	}
	new (m_server) TCPSocket(&m_loop);
	m_server->setCloseCallback(std::bind(&TCPServer::onServerSocketClose, this, std::placeholders::_1));
	m_server->setNewConnectionCallback(std::bind(&TCPServer::onNewConnect, this, std::placeholders::_1, std::placeholders::_2));

	uint32_t outPort = 0U;
	if (m_isIPV6)
	{
		outPort = m_server->bind6(m_ip.c_str(), m_port);
	}
	else
	{
		outPort = m_server->bind(m_ip.c_str(), m_port);
	}

	if (outPort == 0)
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
	NET_UV_LOG(NET_UV_L_INFO, "TCPServer %s:%u start-up...", m_ip.c_str(), getListenPort());

	m_start = true;
	m_serverStage = ServerStage::RUN;

	setListenPort(outPort);
	startThread();

	return true;
}

bool TCPServer::stopServer()
{
	if (!m_start)
		return false;
	m_start = false;
	pushOperation(TCP_SVR_OP_STOP_SERVER, NULL, NULL, 0U);
	return true;
}

void TCPServer::updateFrame()
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
			pushOperation(TCP_SVR_OP_SEND_DIS_SESSION_MSG_TO_MAIN_THREAD, NULL, 0, Msg.pSession->getSessionID());
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

void TCPServer::send(uint32_t sessionID, char* data, uint32_t len)
{
	int32_t bufCount = 0;

	uv_buf_t* bufArr = tcp_packageData(data, len, &bufCount);

	if (bufArr == NULL)
		return;

	for (int32_t i = 0; i < bufCount; ++i)
	{
		pushOperation(TCP_SVR_OP_SEND_DATA, (bufArr + i)->base, (bufArr + i)->len, sessionID);
	}
	fc_free(bufArr);
}

void TCPServer::disconnect(uint32_t sessionID)
{
	pushOperation(TCP_SVR_OP_DIS_SESSION, NULL, 0, sessionID);
}

void TCPServer::run()
{
	startIdle();
	startSessionUpdate(TCP_HEARTBEAT_TIMER_DELAY);

	uv_run(&m_loop, UV_RUN_DEFAULT);

	m_server->~TCPSocket();
	fc_free(m_server);
	m_server = NULL;
	
	uv_loop_close(&m_loop);
	
	m_serverStage = ServerStage::STOP;
	pushThreadMsg(NetThreadMsgType::EXIT_LOOP, NULL);
}


void TCPServer::onNewConnect(uv_stream_t* server, int32_t status)
{
	TCPSocket* client = m_server->accept(server, status);
	if (client != NULL)
	{
		TCPSession* session = TCPSession::createSession(this, client);
		if (session == NULL)
		{
			NET_UV_LOG(NET_UV_L_ERROR, "服务器创建新会话失败,可能是内存不足");
		}
		else
		{
			session->setSessionRecvCallback(std::bind(&TCPServer::onSessionRecvData, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
			session->setSessionClose(std::bind(&TCPServer::onSessionClose, this, std::placeholders::_1));
			session->setSendHeartMsg(NET_HEARTBEAT_MSG_S2C);
			session->setHeartMaxCount(TCP_HEARTBEAT_MAX_COUNT_SERVER);
			session->setResetHeartCount(TCP_HEARTBEAT_COUNT_RESET_VALUE_SERVER);
			session->setSessionID(m_sessionID);
			session->setIsOnline(true);

			m_sessionID++;

			addNewSession(session);
		}
	}
	else
	{
		NET_UV_LOG(NET_UV_L_ERROR, "接受新连接失败");
	}
}

void TCPServer::onServerSocketClose(Socket* svr)
{
	m_serverStage = ServerStage::CLEAR;
}

void TCPServer::startFailureLogic()
{
	m_server->~TCPSocket();
	fc_free(m_server);
	m_server = NULL;

	uv_run(&m_loop, UV_RUN_DEFAULT);

	uv_loop_close(&m_loop);

	m_serverStage = ServerStage::STOP;
}

void TCPServer::addNewSession(TCPSession* session)
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

void TCPServer::onSessionClose(Session* session)
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

void TCPServer::onSessionRecvData(Session* session, char* data, uint32_t len)
{
	pushThreadMsg(NetThreadMsgType::RECV_DATA, session, data, len);
}

void TCPServer::executeOperation()
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
		case TCP_SVR_OP_SEND_DATA :		// 数据发送
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
		case TCP_SVR_OP_DIS_SESSION:	// 断开连接
		{
			auto it = m_allSession.find(curOperation.sessionID);
			if (it != m_allSession.end())
			{
				it->second.session->executeDisconnect();
			}
		}break;
		case TCP_SVR_OP_SEND_DIS_SESSION_MSG_TO_MAIN_THREAD:
		{
			auto it = m_allSession.find(curOperation.sessionID);
			if (it != m_allSession.end())
			{
				it->second.session->~TCPSession();
				fc_free(it->second.session);
				it = m_allSession.erase(it);
			}
		}break;
		case TCP_SVR_OP_STOP_SERVER:
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
		default:
			break;
		}
		m_operationDispatchQue.pop();
	}
}

void TCPServer::clearData()
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
		if (m_operationQue.front().operationType == TCP_SVR_OP_SEND_DATA)
		{
			fc_free(m_operationQue.front().operationData);
		}
		m_operationQue.pop();
	}
}

void TCPServer::onIdleRun()
{
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

void TCPServer::onSessionUpdateRun()
{
	for (auto& it : m_allSession)
	{
		it.second.session->update(TCP_HEARTBEAT_TIMER_DELAY);
	}
}

NS_NET_UV_END