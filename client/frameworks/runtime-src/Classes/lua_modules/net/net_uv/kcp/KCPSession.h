#pragma once

#include "KCPCommon.h"
#include "KCPSocket.h"

NS_NET_UV_BEGIN

class KCPSession : public Session
{
public:
	KCPSession() = delete;
	KCPSession(const KCPSession&) = delete;
	virtual ~KCPSession();

	/// Session
	virtual uint32_t getPort()override;

	virtual std::string getIp()override;
	
protected:

	static KCPSession* createSession(SessionManager* sessionManager, KCPSocket* socket);

	KCPSession(SessionManager* sessionManager);

protected:
	
	/// Session
	virtual void executeSend(char* data, uint32_t len)override;

	virtual void executeDisconnect()override;

	virtual bool executeConnect(const char* ip, uint32_t port)override;

	virtual void setIsOnline(bool isOnline)override;

	virtual void update(uint32_t time)override;

	/// KCPSession
	inline void setKCPSocket(KCPSocket* socket);

	inline KCPSocket* getKCPSocket();

	void init(KCPSocket* socket);

	void on_socket_close(Socket* socket);

	void on_socket_recv(char* data, ssize_t len);

	/// 
	inline void setResetHeartCount(int32_t resetHeartCount);

	inline void setSendHeartMsg(NET_HEART_TYPE msg);

	inline void setHeartMaxCount(int32_t maxCount);

	void onRecvMsgPackage(char* data, uint32_t len, NET_HEART_TYPE type);

	void updateKcp(IUINT32 update_clock);

protected:

	friend class KCPClient;
	friend class KCPServer;
protected:
	Buffer* m_recvBuffer;
	KCPSocket* m_socket;

#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
	int32_t m_curHeartTime;
	int32_t m_curHeartCount;
	int32_t m_resetHeartCount;
	int32_t m_curHeartMaxCount;
	NET_HEART_TYPE m_sendHeartMsg;
#endif
};

void KCPSession::setKCPSocket(KCPSocket* socket)
{
	m_socket = socket;
}

KCPSocket* KCPSession::getKCPSocket()
{
	return m_socket;
}


void KCPSession::setResetHeartCount(int32_t resetHeartCount)
{
#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
	m_resetHeartCount = resetHeartCount;
#endif
}

void KCPSession::setSendHeartMsg(NET_HEART_TYPE msg)
{
#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
	m_sendHeartMsg = msg;
#endif
}

void KCPSession::setHeartMaxCount(int32_t maxCount)
{
#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
	m_curHeartMaxCount = maxCount;
#endif
}

NS_NET_UV_END