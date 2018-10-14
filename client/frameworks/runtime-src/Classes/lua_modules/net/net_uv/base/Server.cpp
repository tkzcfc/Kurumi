#include "Server.h"


NS_NET_UV_BEGIN

Server::Server()
	: m_closeCall(nullptr)
	, m_startCall(nullptr)
	, m_newConnectCall(nullptr)
	, m_recvCall(nullptr)
	, m_disconnectCall(nullptr)
	, m_port(0)
	, m_isIPV6(false)
{
	memset(&m_idle, 0, sizeof(uv_idle_t));
	memset(&m_sessionUpdateTimer, 0, sizeof(uv_timer_t));
	memset(&m_loop, 0, sizeof(uv_loop_t));
}

Server::~Server()
{}

void Server::startServer(const char* ip, unsigned int port, bool isIPV6)
{
	assert(m_startCall != nullptr);
	assert(m_closeCall != nullptr);
	assert(m_newConnectCall != nullptr);
	assert(m_recvCall != nullptr);
	assert(m_disconnectCall != nullptr);

	m_ip = ip;
	m_port = port;
	m_isIPV6 = isIPV6;
}


void Server::pushThreadMsg(NetThreadMsgType type, Session* session, char* data, unsigned int len)
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

void Server::startSessionUpdate(unsigned int time)
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
