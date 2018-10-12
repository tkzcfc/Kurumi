#pragma once

#include "Common.h"
#include "Session.h"
#include "SessionManager.h"
#include "Runnable.h"
#include "../common/NetUVThreadMsg.h"

NS_NET_UV_BEGIN

class Server;
using ServerStartCall = std::function<void(Server*, bool)>;
using ServerCloseCall = std::function<void(Server*)>;
using ServerNewConnectCall = std::function<void(Server*, Session*)>;
using ServerRecvCall = std::function<void(Server*, Session*, char* data, unsigned int len)>;
using ServerDisconnectCall = std::function<void(Server*, Session*)>;

class Server : public Runnable, public SessionManager
{
public:
	Server();
	virtual ~Server();

	virtual void startServer(const char* ip, unsigned int port, bool isIPV6);

	virtual bool stopServer() = 0;

	// 主线程轮询
	virtual void updateFrame() = 0;

	inline void setCloseCallback(const ServerCloseCall& call);

	inline void setStartCallback(const ServerStartCall& call);

	inline void setNewConnectCallback(const ServerNewConnectCall& call);

	inline void setRecvCallback(const ServerRecvCall& call);

	inline void setDisconnectCallback(const ServerDisconnectCall& call);

protected:

	virtual void onIdleRun() = 0;

	virtual void onSessionUpdateRun() = 0;

protected:

	void startIdle();

	void stopIdle();

	void startSessionUpdate(unsigned int time);

	void stopSessionUpdate();

	virtual void pushThreadMsg(NetThreadMsgType type, Session* session, char* data = NULL, unsigned int len = 0);

protected:
	static void uv_on_idle_run(uv_idle_t* handle);

	static void uv_on_session_update_timer_run(uv_timer_t* handle);
protected:
	ServerStartCall m_startCall;
	ServerCloseCall m_closeCall;
	ServerNewConnectCall m_newConnectCall;
	ServerRecvCall m_recvCall;
	ServerDisconnectCall m_disconnectCall;

	// 线程消息
	Mutex m_msgMutex;
	std::queue<NetThreadMsg> m_msgQue;
	std::queue<NetThreadMsg> m_msgDispatchQue;

	uv_idle_t m_idle;
	uv_timer_t m_sessionUpdateTimer;
	uv_loop_t m_loop;

	std::string m_ip;
	unsigned int m_port;
	bool m_isIPV6;
};

void Server::setCloseCallback(const ServerCloseCall& call)
{
	m_closeCall = std::move(call);
}

void Server::setStartCallback(const ServerStartCall& call)
{
	m_startCall = std::move(call);
}

void Server::setNewConnectCallback(const ServerNewConnectCall& call)
{
	m_newConnectCall = std::move(call);
}

void Server::setRecvCallback(const ServerRecvCall& call)
{
	m_recvCall = std::move(call);
}

void Server::setDisconnectCallback(const ServerDisconnectCall& call)
{
	m_disconnectCall = std::move(call);
}


NS_NET_UV_END
