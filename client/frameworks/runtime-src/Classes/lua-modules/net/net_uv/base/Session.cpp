#include "Session.h"
#include "SessionManager.h"

NS_NET_UV_BEGIN

Session::Session(SessionManager* manager)
	: m_sessionManager(manager)
	, m_isOnline(false)
	, m_sessionID(-1)
	, m_sessionRecvCallback(nullptr)
	, m_sessionCloseCallback(nullptr)
{}

Session::~Session()
{}

void Session::send(char* data, unsigned int len)
{
	getSessionManager()->send(this, data, len);
}

void Session::disconnect()
{
	getSessionManager()->disconnect(this);
}

void Session::setIsOnline(bool bIsOnline)
{
	m_isOnline = bIsOnline;
}
NS_NET_UV_END