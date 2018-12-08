#pragma once

#include "TCPSocket.h"

NS_NET_UV_BEGIN


class TCPSession : public Session
{
public:
	TCPSession() = delete;
	TCPSession(const TCPSession&) = delete;
	virtual ~TCPSession();

	virtual uint32_t getPort()override;

	virtual std::string getIp()override;
	
protected:

	static TCPSession* createSession(SessionManager* sessionManager, TCPSocket* socket);

	TCPSession(SessionManager* sessionManager);

protected:

	virtual void executeSend(char* data, uint32_t len) override;

	virtual void executeDisconnect() override;

	virtual bool executeConnect(const char* ip, uint32_t port)override;

	virtual void setIsOnline(bool isOnline)override;

	virtual void update(uint32_t time)override;

protected:

	bool initWithSocket(TCPSocket* socket);
	
	inline TCPSocket* getTCPSocket();

	inline void setResetHeartCount(int32_t resetHeartCount);

	inline void setSendHeartMsg(NET_HEART_TYPE msg);

	inline void setHeartMaxCount(int32_t maxCount);
	
	void onRecvMsgPackage(char* data, uint32_t len, NET_HEART_TYPE type);

protected:

	void on_socket_recv(char* data, ssize_t len);

	void on_socket_close(Socket* socket);

	friend class TCPServer;
	friend class TCPClient;

protected:	

	Buffer* m_recvBuffer;
	TCPSocket* m_socket;

#if TCP_OPEN_UV_THREAD_HEARTBEAT == 1
	int32_t m_curHeartTime;
	int32_t m_curHeartCount;
	int32_t m_resetHeartCount;
	int32_t m_curHeartMaxCount;
	NET_HEART_TYPE m_sendHeartMsg;
#endif
};

TCPSocket* TCPSession::getTCPSocket()
{
	return m_socket;
}


void TCPSession::setResetHeartCount(int32_t resetHeartCount)
{
#if TCP_OPEN_UV_THREAD_HEARTBEAT == 1
	m_resetHeartCount = resetHeartCount;
#endif
}

void TCPSession::setSendHeartMsg(NET_HEART_TYPE msg)
{
#if TCP_OPEN_UV_THREAD_HEARTBEAT == 1
	m_sendHeartMsg = msg;
#endif
}

void TCPSession::setHeartMaxCount(int32_t maxCount)
{
#if TCP_OPEN_UV_THREAD_HEARTBEAT == 1
	m_curHeartMaxCount = maxCount;
#endif
}

NS_NET_UV_END
