#include "Client.h"

NS_NET_UV_BEGIN

Client::Client()
	: m_connectCall(nullptr)
	, m_disconnectCall(nullptr)
	, m_recvCall(nullptr)
{
	memset(&m_idle, 0, sizeof(uv_idle_t));
	memset(&m_sessionUpdateTimer, 0, sizeof(uv_timer_t));
	memset(&m_loop, 0, sizeof(uv_loop_t));
}

Client::~Client()
{}

void Client::pushThreadMsg(NetThreadMsgType type, Session* session, char* data, unsigned int len)
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

void Client::startIdle()
{
	stopIdle();

	uv_idle_init(&m_loop, &m_idle);
	m_idle.data = this;

	uv_idle_start(&m_idle, uv_on_idle_run);
}

void Client::stopIdle()
{
	if (m_idle.data)
	{
		uv_idle_stop(&m_idle);
		m_idle.data = NULL;
	}
}

void Client::startSessionUpdate(unsigned int time)
{
	stopSessionUpdate();

	uv_timer_init(&m_loop, &m_sessionUpdateTimer);
	m_sessionUpdateTimer.data = this;

	uv_timer_start(&m_sessionUpdateTimer, uv_on_session_update_timer_run, time, time);
}

void Client::stopSessionUpdate()
{
	if (m_sessionUpdateTimer.data)
	{
		uv_timer_stop(&m_sessionUpdateTimer);
		m_sessionUpdateTimer.data = NULL;
	}
}

void Client::uv_on_idle_run(uv_idle_t* handle)
{
	Client* svr = (Client*)handle->data;
	svr->onIdleRun();
}

void Client::uv_on_session_update_timer_run(uv_timer_t* handle)
{
	Client* svr = (Client*)handle->data;
	svr->onSessionUpdateRun();
}


NS_NET_UV_END