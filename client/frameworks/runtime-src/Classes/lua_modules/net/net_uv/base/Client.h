#pragma once

#include "Common.h"
#include "Runnable.h"
#include "SessionManager.h"
#include "../common/NetUVThreadMsg.h"

NS_NET_UV_BEGIN

class Client;
class Session;

using ClientConnectCall = std::function<void(Client*, Session*, int)>; // 0失败 1成功 2超时 3会话ID已存在，且与现在的IP、端口不一致
using ClientDisconnectCall = std::function<void(Client*, Session*)>;
using ClientRecvCall = std::function<void(Client*, Session*, char*, unsigned int)>;
using ClientCloseCall = std::function<void(Client*)>;
using ClientRemoveSessionCall = std::function<void(Client*, Session*)>;

class Client : public Runnable, public SessionManager
{
public:
	Client();

	virtual ~Client();

	virtual void connect(const char* ip, unsigned int port, unsigned int sessionId) = 0;

	virtual void disconnect(unsigned int sessionId) = 0;

	virtual void closeClient() = 0;

	virtual void updateFrame() = 0;

	virtual void send(unsigned int sessionId, char* data, unsigned int len) = 0;

	virtual void removeSession(unsigned int sessionId) = 0;

	inline void setConnectCallback(const ClientConnectCall& call);

	inline void setDisconnectCallback(const ClientDisconnectCall& call);

	inline void setRecvCallback(const ClientRecvCall& call);

	inline void setClientCloseCallback(const ClientCloseCall& call);
	
	inline void setRemoveSessionCallback(const ClientRemoveSessionCall& call);

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
	ClientConnectCall m_connectCall;
	ClientDisconnectCall m_disconnectCall;
	ClientRecvCall m_recvCall;
	ClientCloseCall m_clientCloseCall;
	ClientRemoveSessionCall m_removeSessionCall;


	// 线程消息
	Mutex m_msgMutex;
	std::queue<NetThreadMsg> m_msgQue;
	std::queue<NetThreadMsg> m_msgDispatchQue;

	uv_idle_t m_idle;
	uv_timer_t m_sessionUpdateTimer;
	uv_loop_t m_loop;
};

void Client::setConnectCallback(const ClientConnectCall& call)
{
	m_connectCall = std::move(call);
}

void Client::setDisconnectCallback(const ClientDisconnectCall& call)
{
	m_disconnectCall = std::move(call);
}

void Client::setRecvCallback(const ClientRecvCall& call)
{
	m_recvCall = std::move(call);
}

void Client::setClientCloseCallback(const ClientCloseCall& call)
{
	m_clientCloseCall = std::move(call);
}

void Client::setRemoveSessionCallback(const ClientRemoveSessionCall& call)
{
	m_removeSessionCall = std::move(call);
}

NS_NET_UV_END
