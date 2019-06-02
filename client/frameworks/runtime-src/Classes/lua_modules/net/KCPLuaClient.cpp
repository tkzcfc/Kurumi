#include "KCPLuaClient.h"


KCPLuaClient* KCPLuaClient::Instance = NULL;

KCPLuaClient* KCPLuaClient::getInstance()
{
	if (Instance == NULL)
	{
		Instance = new KCPLuaClient();
	}
	return Instance;
}

void KCPLuaClient::destroy()
{
	if (Instance)
	{
		delete Instance;
		Instance = NULL;
	}
}

KCPLuaClient::KCPLuaClient()
{
	m_client = new net_uv::KCPClient();

	m_client->setConnectCallback(CC_CALLBACK_3(KCPLuaClient::onClientConnectCall, this));
	m_client->setDisconnectCallback(CC_CALLBACK_2(KCPLuaClient::onClientDisconnectCall, this));
	m_client->setRecvCallback(std::bind(&KCPLuaClient::onClientRecvCall, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_client->setClientCloseCallback(CC_CALLBACK_1(KCPLuaClient::onClientCloseCall, this));
	m_client->setRemoveSessionCallback(CC_CALLBACK_2(KCPLuaClient::onClientRemoveSessionCall, this));

	auto scheduler = cocos2d::Director::getInstance()->getScheduler();
	scheduler->schedule(schedule_selector(KCPLuaClient::update), this, 1 / 60.0f, false);
}

KCPLuaClient::~KCPLuaClient()
{
	auto scheduler = cocos2d::Director::getInstance()->getScheduler();
	scheduler->unscheduleAllForTarget(this);

	CC_SAFE_DELETE(m_client);
}

void KCPLuaClient::connect(const char* ip, unsigned int port, unsigned int sessionId)
{
	m_client->connect(ip, port, sessionId);
}

void KCPLuaClient::disconnect(unsigned int sessionId)
{
	m_client->disconnect(sessionId);
}

void KCPLuaClient::closeClient()
{
	m_client->closeClient();
}

void KCPLuaClient::send(unsigned int sessionId, char* data, unsigned int len)
{
	m_client->send(sessionId, data, len);
}

void KCPLuaClient::removeSession(unsigned int sessionId)
{
	m_client->removeSession(sessionId);
}

void KCPLuaClient::send(net_uv::Session* session, char* data, unsigned int len)
{
	m_client->send(session->getSessionID(), data, len);
}

void KCPLuaClient::disconnect(net_uv::Session* session)
{
	m_client->disconnect(session->getSessionID());
}

bool KCPLuaClient::isCloseFinish()
{
	return m_client->isCloseFinish();
}

//设置所有socket是否自动重连
void KCPLuaClient::setAutoReconnect(bool isAuto)
{
	m_client->setAutoReconnect(isAuto);
}

//设置所有socket自动重连时间(单位：S)
void KCPLuaClient::setAutoReconnectTime(float time)
{
	m_client->setAutoReconnectTime(time);
}

//是否自动重连
void KCPLuaClient::setAutoReconnectBySessionID(unsigned int sessionID, bool isAuto)
{
	m_client->setAutoReconnectBySessionID(sessionID, isAuto);
}

//自动重连时间(单位：S)
void KCPLuaClient::setAutoReconnectTimeBySessionID(unsigned int sessionID, float time)
{
	m_client->setAutoReconnectTimeBySessionID(sessionID, time);
}

void KCPLuaClient::update(float)
{
	m_client->updateFrame();
}

void KCPLuaClient::onClientConnectCall(net_uv::Client* client, net_uv::Session* session, int status)
{
	auto handle = getLuaHandle("onClientConnectCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype<net_uv::KCPClient>(client, "net_uv::KCPClient");
		handle->pushusertype<net_uv::KCPSession>(session, "net_uv::KCPSession");
		handle->pusharg(status);
		handle->pcall();
	}
}

void KCPLuaClient::onClientDisconnectCall(net_uv::Client* client, net_uv::Session* session)
{
	auto handle = getLuaHandle("onClientDisconnectCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype<net_uv::KCPClient>(client, "net_uv::KCPClient");
		handle->pushusertype<net_uv::KCPSession>(session, "net_uv::KCPSession");
		handle->pcall();
	}
}

void KCPLuaClient::onClientRecvCall(net_uv::Client* client, net_uv::Session* session, char* data, unsigned int len)
{
	auto handle = getLuaHandle("onClientRecvCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype<net_uv::KCPClient>(client, "net_uv::KCPClient");
		handle->pushusertype<net_uv::KCPSession>(session, "net_uv::KCPSession");
		handle->pushlstring(data, len);
		handle->pusharg(len);
		handle->pcall();
	}
}

void KCPLuaClient::onClientCloseCall(net_uv::Client* client)
{
	auto handle = getLuaHandle("onClientCloseCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype<net_uv::KCPSession>(client, "net_uv::KCPSession");
		handle->pcall();
	}
}

void KCPLuaClient::onClientRemoveSessionCall(net_uv::Client* client, net_uv::Session* session)
{
	auto handle = getLuaHandle("onClientRemoveSessionCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype<net_uv::KCPClient>(client, "net_uv::KCPClient");
		handle->pushusertype<net_uv::KCPSession>(session, "net_uv::KCPSession");
		handle->pcall();
	}
}
