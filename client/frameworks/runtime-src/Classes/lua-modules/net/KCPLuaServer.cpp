#include "KCPLuaServer.h"

KCPLuaServer::KCPLuaServer()
{
	m_server = new net_uv::KCPServer();

	m_server->setStartCallback(CC_CALLBACK_2(KCPLuaServer::onServerStartCall, this));
	m_server->setCloseCallback(CC_CALLBACK_1(KCPLuaServer::onServerCloseCall, this));
	m_server->setNewConnectCallback(CC_CALLBACK_2(KCPLuaServer::onServerNewConnectCall, this));
	m_server->setRecvCallback(std::bind(&KCPLuaServer::onServerRecvCall, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_server->setDisconnectCallback(CC_CALLBACK_2(KCPLuaServer::onServerDisconnectCall, this));

	auto scheduler = cocos2d::Director::getInstance()->getScheduler();
	scheduler->schedule(schedule_selector(KCPLuaServer::update), this, 1 / 60.0f, false);
}

KCPLuaServer::~KCPLuaServer()
{
	auto scheduler = cocos2d::Director::getInstance()->getScheduler();
	scheduler->unscheduleAllForTarget(this);

	CC_SAFE_DELETE(m_server);
}

void KCPLuaServer::startServer(const char* ip, unsigned int port, bool isIPV6)
{
	m_server->startServer(ip, port, isIPV6);
}

bool KCPLuaServer::stopServer()
{
	return m_server->stopServer();
}

void KCPLuaServer::send(net_uv::Session* session, char* data, unsigned int len)
{
	m_server->send(session, data, len);
}

void KCPLuaServer::disconnect(net_uv::Session* session)
{
	m_server->disconnect(session);
}

bool KCPLuaServer::isCloseFinish()
{
	return m_server->isCloseFinish();
}

void KCPLuaServer::update(float)
{
	m_server->updateFrame();
}

void KCPLuaServer::onServerStartCall(net_uv::Server* svr, bool success)
{
	auto handle = getLuaHandle("onServerStartCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(svr, "net_uv::KCPServer");
		handle->pusharg(success);
		handle->pcall();
	}
}

void KCPLuaServer::onServerCloseCall(net_uv::Server* svr)
{
	auto handle = getLuaHandle("onServerCloseCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(svr, "net_uv::KCPServer");
		handle->pcall();
	}
}

void KCPLuaServer::onServerNewConnectCall(net_uv::Server* svr, net_uv::Session* session)
{
	auto handle = getLuaHandle("onServerNewConnectCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(svr, "net_uv::KCPServer");
		handle->pushusertype(session, "net_uv::KCPSession");
		handle->pcall();
	}
}

void KCPLuaServer::onServerRecvCall(net_uv::Server* svr, net_uv::Session* session, char* data, unsigned int len)
{
	auto handle = getLuaHandle("onServerRecvCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(svr, "net_uv::KCPServer");
		handle->pushusertype(session, "net_uv::KCPSession");
		handle->pushlstring(data, len);
		handle->pusharg(len);
		handle->pcall();
	}
}

void KCPLuaServer::onServerDisconnectCall(net_uv::Server* svr, net_uv::Session* session)
{
	auto handle = getLuaHandle("onServerDisconnectCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(svr, "net_uv::KCPServer");
		handle->pushusertype(session, "net_uv::KCPSession");
		handle->pcall();
	}
}
