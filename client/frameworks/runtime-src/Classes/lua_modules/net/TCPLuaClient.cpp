#include "TCPLuaClient.h"


TCPLuaClient* TCPLuaClient::Instance = NULL;

void tcp_com_log_func(int level, const char* log)
{
	CCLOG("[NET_UV]: %s", log);
}

TCPLuaClient* TCPLuaClient::getInstance()
{
	if (Instance == NULL)
	{
		net_uv::setNetUVLogPrintFunc(tcp_com_log_func);
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
	m_client = new net_uv::TCPClient();

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

	CC_SAFE_DELETE(m_client);
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

void TCPLuaClient::send(net_uv::Session* session, char* data, unsigned int len)
{
	m_client->send(session->getSessionID(), data, len);
}

void TCPLuaClient::disconnect(net_uv::Session* session)
{
	m_client->disconnect(session->getSessionID());
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
}

void TCPLuaClient::onClientConnectCall(net_uv::Client* client, net_uv::Session* session, int status)
{
	auto handle = getLuaHandle("onClientConnectCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype<net_uv::TCPClient>(client, "net_uv::TCPClient");
		handle->pushusertype<net_uv::TCPSession>(session, "net_uv::TCPSession");
		handle->pusharg(status);
		handle->pcall();
	}
}

void TCPLuaClient::onClientDisconnectCall(net_uv::Client* client, net_uv::Session* session)
{
	auto handle = getLuaHandle("onClientDisconnectCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype<net_uv::TCPClient>(client, "net_uv::TCPClient");
		handle->pushusertype<net_uv::TCPSession>(session, "net_uv::TCPSession");
		handle->pcall();
	}
}

void TCPLuaClient::onClientRecvCall(net_uv::Client* client, net_uv::Session* session, char* data, unsigned int len)
{
	auto handle = getLuaHandle("onClientRecvCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype<net_uv::TCPClient>(client, "net_uv::TCPClient");
		handle->pushusertype<net_uv::TCPSession>(session, "net_uv::TCPSession");
		handle->pushlstring(data, len);
		handle->pusharg(len);
		handle->pcall();
	}
}

void TCPLuaClient::onClientCloseCall(net_uv::Client* client)
{
	auto handle = getLuaHandle("onClientCloseCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype<net_uv::TCPClient>(client, "net_uv::TCPClient");
		handle->pcall();
	}
}

void TCPLuaClient::onClientRemoveSessionCall(net_uv::Client* client, net_uv::Session* session)
{
	auto handle = getLuaHandle("onClientRemoveSessionCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype<net_uv::TCPClient>(client, "net_uv::TCPClient");
		handle->pushusertype<net_uv::TCPSession>(session, "net_uv::TCPSession");
		handle->pcall();
	}
}
