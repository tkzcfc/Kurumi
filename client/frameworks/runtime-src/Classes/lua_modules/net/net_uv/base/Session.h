#pragma once

#include "Common.h"

NS_NET_UV_BEGIN

class Session;
using SessionCloseCall = std::function<void(Session*)>;
using SessionRecvCall = std::function<void(Session*, char*, unsigned int)>;

class SessionManager;
class Session
{
public:
	Session(SessionManager* manager);
	virtual ~Session();

	virtual void send(char* data, unsigned int len);

	virtual void disconnect();

	inline unsigned int getSessionID();

	virtual inline unsigned int getPort() = 0;

	virtual inline const std::string& getIp() = 0;

protected:

	virtual void executeSend(char* data, unsigned int len) = 0;

	virtual void executeDisconnect() = 0;

	virtual bool executeConnect(const char* ip, unsigned int port) = 0;

	virtual void update(unsigned int time) = 0;

protected:
		
	inline SessionManager* getSessionManager();

	inline void setSessionClose(const SessionCloseCall& call);

	inline void setSessionRecvCallback(const SessionRecvCall& call);

	inline bool isOnline();

	virtual void setIsOnline(bool isOnline);

	inline void setSessionID(unsigned int sessionId);

protected:
	friend class SessionManager;

	SessionManager* m_sessionManager;

	SessionCloseCall m_sessionCloseCallback;
	SessionRecvCall m_sessionRecvCallback;

	bool m_isOnline;
	unsigned int m_sessionID;
};


void Session::setSessionClose(const SessionCloseCall& call)
{
	m_sessionCloseCallback = std::move(call);
}

void Session::setSessionRecvCallback(const SessionRecvCall& call)
{
	m_sessionRecvCallback = std::move(call);
}

SessionManager* Session::getSessionManager()
{
	return m_sessionManager;
}

bool Session::isOnline()
{
	return m_isOnline;
}

unsigned int Session::getSessionID()
{
#if OPEN_NET_UV_DEBUG == 1
	assert(m_sessionID != -1);
#endif
	return m_sessionID;
}

void Session::setSessionID(unsigned int sessionId)
{
	m_sessionID = sessionId;
}

NS_NET_UV_END