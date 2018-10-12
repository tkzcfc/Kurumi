#pragma once

#include "KCPCommon.h"
#include "KCPSocket.h"

NS_NET_UV_BEGIN

class NET_UV_EXTERN KCPSession : public Session
{
public:
	KCPSession() = delete;
	KCPSession(const KCPSession&) = delete;
	virtual ~KCPSession();

	/// Session
	virtual inline unsigned int getPort()override;

	virtual inline const std::string& getIp()override;
	
protected:

	static KCPSession* createSession(SessionManager* sessionManager, KCPSocket* socket);

	KCPSession(SessionManager* sessionManager);

protected:
	
	/// Session
	virtual void executeSend(char* data, unsigned int len)override;

	virtual void executeDisconnect()override;

	virtual bool executeConnect(const char* ip, unsigned int port)override;

	virtual void setIsOnline(bool isOnline)override;

	virtual void update(unsigned int time)override;

	/// KCPSession
	inline void setKCPSocket(KCPSocket* socket);

	inline KCPSocket* getKCPSocket();

	void init(KCPSocket* socket);

	void on_socket_close(Socket* socket);

	void on_socket_recv(char* data, ssize_t len);

	/// 
	inline void setResetHeartCount(int resetHeartCount);

	inline void setSendHeartMsg(NET_HEART_TYPE msg);

	inline void setHeartMaxCount(int maxCount);

	void onRecvMsgPackage(char* data, unsigned int len, NET_HEART_TYPE type);

	void updateKcp(IUINT32 update_clock);

protected:

	friend class KCPClient;
	friend class KCPServer;
protected:
	Buffer* m_recvBuffer;
	KCPSocket* m_socket;

#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
	int m_curHeartTime;
	int m_curHeartCount;
	int m_resetHeartCount;
	int m_curHeartMaxCount;
	NET_HEART_TYPE m_sendHeartMsg;
#endif
};

unsigned int KCPSession::getPort()
{
	return getKCPSocket()->getPort();
}

inline const std::string& KCPSession::getIp()
{
	return getKCPSocket()->getIp();
}

void KCPSession::setKCPSocket(KCPSocket* socket)
{
	m_socket = socket;
}

KCPSocket* KCPSession::getKCPSocket()
{
	return m_socket;
}


void KCPSession::setResetHeartCount(int resetHeartCount)
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

void KCPSession::setHeartMaxCount(int maxCount)
{
#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
	m_curHeartMaxCount = maxCount;
#endif
}

NS_NET_UV_END