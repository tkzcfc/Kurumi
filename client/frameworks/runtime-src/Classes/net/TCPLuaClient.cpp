#include "TCPLuaClient.h"


TCPLuaClient* TCPLuaClient::Instance = NULL;

void tcp_com_log_func(int level, const char* log)
{
	CCLOG("%s", log);
}

TCPLuaClient* TCPLuaClient::getInstance()
{
	if (Instance == NULL)
	{
		//setUVLogPrintFunc(tcp_com_log_func);
		Instance = new TCPLuaClient();
	}
	return Instance;
}

void TCPLuaClient::destroy()
{
	if (Instance)
	{
		delete Instance;
		Instance = NULL;
	}
}

TCPLuaClient::TCPLuaClient()
{
	m_client = new TCPClient();

	m_client->setConnectCallback(CC_CALLBACK_3(TCPLuaClient::onClientConnectCall, this));
	m_client->setDisconnectCallback(CC_CALLBACK_2(TCPLuaClient::onClientDisconnectCall, this));
	m_client->setRecvCallback(std::bind(&TCPLuaClient::onClientRecvCall, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_client->setClientCloseCallback(CC_CALLBACK_1(TCPLuaClient::onClientCloseCall, this));
	m_client->setRemoveSessionCallback(CC_CALLBACK_2(TCPLuaClient::onClientRemoveSessionCall, this));
	
	auto scheduler = cocos2d::Director::getInstance()->getScheduler();
	scheduler->schedule(schedule_selector(TCPLuaClient::update), this, 1 / 60.0f, false);
}

TCPLuaClient::~TCPLuaClient()
{
	auto scheduler = cocos2d::Director::getInstance()->getScheduler();
	scheduler->unscheduleAllForTarget(this);

	delete m_client;
}

void TCPLuaClient::connect(const char* ip, unsigned int port, unsigned int sessionId)
{
	m_client->connect(ip, port, sessionId);
}

void TCPLuaClient::disconnect(unsigned int sessionId)
{
	m_client->disconnect(sessionId);
}

void TCPLuaClient::closeClient()
{
	m_client->closeClient();
}

void TCPLuaClient::send(unsigned int sessionId, char* data, unsigned int len)
{
	m_client->send(sessionId, data, len);
}

void TCPLuaClient::removeSession(unsigned int sessionId)
{
	m_client->removeSession(sessionId);
}

void TCPLuaClient::send(Session* session, char* data, unsigned int len)
{
	m_client->send(session, data, len);
}

void TCPLuaClient::disconnect(Session* session)
{
	m_client->disconnect(session);
}

bool TCPLuaClient::isCloseFinish()
{
	return m_client->isCloseFinish();
}

//是否启用TCP_NODELAY
bool TCPLuaClient::setSocketNoDelay(bool enable)
{
	return m_client->setSocketNoDelay(enable);
}

//设置心跳
bool TCPLuaClient::setSocketKeepAlive(int enable, unsigned int delay)
{
	return m_client->setSocketKeepAlive(enable, delay);
}

//设置所有socket是否自动重连
void TCPLuaClient::setAutoReconnect(bool isAuto)
{
	m_client->setAutoReconnect(isAuto);
}

//设置所有socket自动重连时间(单位：S)
void TCPLuaClient::setAutoReconnectTime(float time)
{
	m_client->setAutoReconnectTime(time);
}

//是否自动重连
void TCPLuaClient::setAutoReconnectBySessionID(unsigned int sessionID, bool isAuto)
{
	m_client->setAutoReconnectBySessionID(sessionID, isAuto);
}

//自动重连时间(单位：S)
void TCPLuaClient::setAutoReconnectTimeBySessionID(unsigned int sessionID, float time)
{
	m_client->setAutoReconnectTimeBySessionID(sessionID, time);
}

void TCPLuaClient::update(float)
{
	m_client->updateFrame();

	//m_client->getAllThreadMsg(&m_threadMsg);
	//if (!m_threadMsg.empty())
	//{
	//	if (m_func)
	//	{
	//		for (auto& it : m_threadMsg)
	//		{
	//			m_func(it);
	//		}
	//	}

	//	if (m_luaHandleInvalid)
	//	{
	//		for (auto& msg : m_threadMsg)
	//		{
	//			switch (msg.msgType)
	//			{
	//			case CONNECT_FAIL:	//连接失败
	//			{
	//				UV_LOG(UV_L_INFO, "CONNECT_FAIL");
	//				m_luaHandle("fail", msg.key);
	//			}break;
	//			case CONNECT_ING:	//正在连接
	//			{
	//				UV_LOG(UV_L_INFO, "CONNECT_ING");
	//				m_luaHandle("connecting", msg.key);
	//			}break;
	//			case CONNECT:		//连接成功
	//			{
	//				UV_LOG(UV_L_INFO, "CONNECT");
	//				m_luaHandle("connect", msg.key);
	//			}break;
	//			case DIS_CONNECT:	//断开连接
	//			{
	//				UV_LOG(UV_L_INFO, "DIS_CONNECT");
	//				m_luaHandle("disconnect", msg.key);
	//			}break;
	//			case EXIT_LOOP:		//退出loop
	//			{
	//				UV_LOG(UV_L_INFO, "EXIT_LOOP");
	//				m_luaHandle("loop exit");
	//			}break;
	//			case RECV_DATA:		//收到消息
	//			{
	//				//UV_LOG("uv RECV_DATA");
	//				if (msg.tag == TCPMsgTag::MT_DEFAULT)
	//				{
	//					m_luaHandle.ppush();
	//					m_luaHandle.pusharg("recv");
	//					m_luaHandle.pushlstring((const char*)msg.data, (unsigned int)msg.dataLen);
	//					m_luaHandle.pcall();
	//				}
	//			}break;
	//			default:
	//				break;
	//			}
	//		}
	//	}

	//	for (auto& it : m_threadMsg)
	//	{
	//		fc_free(it.data);
	//	}
	//}
}

void TCPLuaClient::onClientConnectCall(Client* client, Session* session, int status)
{
	auto handle = getLuaHandle("onClientConnectCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(client, "Client");
		handle->pushusertype(session, "Session");
		handle->pusharg(status);
		handle->pcall();
	}
}

void TCPLuaClient::onClientDisconnectCall(Client* client, Session* session)
{
	auto handle = getLuaHandle("onClientDisconnectCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(client, "Client");
		handle->pushusertype(session, "Session");
		handle->pcall();
	}
}

void TCPLuaClient::onClientRecvCall(Client* client, Session* session, char* data, unsigned int len)
{
	auto handle = getLuaHandle("onClientRecvCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(client, "Client");
		handle->pushusertype(session, "Session");
		handle->pushlstring(data, len);
		handle->pusharg(len);
		handle->pcall();
	}
}

void TCPLuaClient::onClientCloseCall(Client* client)
{
	auto handle = getLuaHandle("onClientCloseCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(client, "Client");
		handle->pcall();
	}
}

void TCPLuaClient::onClientRemoveSessionCall(Client* client, Session* session)
{
	auto handle = getLuaHandle("onClientRemoveSessionCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(client, "Client");
		handle->pushusertype(session, "Session");
		handle->pcall();
	}
}
