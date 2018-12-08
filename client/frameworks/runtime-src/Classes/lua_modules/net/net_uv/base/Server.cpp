#include "Server.h"


NS_NET_UV_BEGIN

Server::Server()
	: m_closeCall(nullptr)
	, m_newConnectCall(nullptr)
	, m_recvCall(nullptr)
	, m_disconnectCall(nullptr)
	, m_port(0)
	, m_listenPort(0)
	, m_isIPV6(false)
	, m_serverStage(ServerStage::STOP)
{
	memset(&m_idle, 0, sizeof(uv_idle_t));
	memset(&m_sessionUpdateTimer, 0, sizeof(uv_timer_t));
	memset(&m_loop, 0, sizeof(uv_loop_t));
}

Server::~Server()
{}

bool Server::startServer(const char* ip, uint32_t port, bool isIPV6)
{
	assert(m_closeCall != nullptr);
	assert(m_newConnectCall != nullptr);
	assert(m_recvCall != nullptr);
	assert(m_disconnectCall != nullptr);

	m_ip = ip;
	m_port = port;
	m_isIPV6 = isIPV6;
	m_listenPort = port;
	
	return true;
}


void Server::pushThreadMsg(NetThreadMsgType type, Session* session, char* data, uint32_t len)
{
	NetThreadMsg msg;
	msg.msgType = type;
	msg.data = data;
	msg.dataLen = len;
	msg.pSession = session;

	m_msgMutex.lock();
	m_msgQue.push(msg);
	m_msgMutex.unlock();
}

std::string Server::getIP()
{
	return m_ip;
}

uint32_t Server::getPort()
{
	return m_port;
}

uint32_t Server::getListenPort()
{
	return m_listenPort;
}

bool Server::isIPV6()
{
	return m_isIPV6;
}

bool Server::isCloseFinish()
{
	return (m_serverStage == ServerStage::STOP);
}

void Server::startIdle()
{
	stopIdle();

	uv_idle_init(&m_loop, &m_idle);
	m_idle.data = this;

	uv_idle_start(&m_idle, uv_on_idle_run);
}

void Server::stopIdle()
{
	if (m_idle.data)
	{
		uv_idle_stop(&m_idle);
		m_idle.data = NULL;
	}
}

void Server::startSessionUpdate(uint32_t time)
{
	stopSessionUpdate();

	uv_timer_init(&m_loop, &m_sessionUpdateTimer);
	m_sessionUpdateTimer.data = this;

	uv_timer_start(&m_sessionUpdateTimer, uv_on_session_update_timer_run, time, time);
}

void Server::stopSessionUpdate()
{
	if (m_sessionUpdateTimer.data)
	{
		uv_timer_stop(&m_sessionUpdateTimer);
		m_sessionUpdateTimer.data = NULL;
	}
}

void Server::uv_on_idle_run(uv_idle_t* handle)
{
	Server* svr = (Server*)handle->data;
	svr->onIdleRun();
}

void Server::uv_on_session_update_timer_run(uv_timer_t* handle)
{
	Server* svr = (Server*)handle->data;
	svr->onSessionUpdateRun();
}


NS_NET_UV_END
