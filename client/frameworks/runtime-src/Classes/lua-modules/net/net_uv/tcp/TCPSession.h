#pragma once

#include "TCPSocket.h"

NS_NET_UV_BEGIN


class TCPSession : public Session
{
public:
	TCPSession() = delete;
	TCPSession(const TCPSession&) = delete;
	virtual ~TCPSession();

	virtual inline unsigned int getPort()override;

	virtual inline const std::string& getIp()override;
	
protected:

	static TCPSession* createSession(SessionManager* sessionManager, TCPSocket* socket);

	TCPSession(SessionManager* sessionManager);

protected:

	virtual void executeSend(char* data, unsigned int len) override;

	virtual void executeDisconnect() override;

	virtual bool executeConnect(const char* ip, unsigned int port)override;

	virtual void setIsOnline(bool isOnline)override;

	virtual void update(unsigned int time)override;

protected:

	bool initWithSocket(TCPSocket* socket);
	
	inline TCPSocket* getTCPSocket();

	inline void setResetHeartCount(int resetHeartCount);

	inline void setSendHeartMsg(NET_HEART_TYPE msg);

	inline void setHeartMaxCount(int maxCount);
	
	void onRecvMsgPackage(char* data, unsigned int len, NET_HEART_TYPE type);

protected:

	void on_socket_recv(char* data, ssize_t len);

	void on_socket_close(Socket* socket);

	friend class TCPServer;
	friend class TCPClient;

protected:	

	Buffer* m_recvBuffer;
	TCPSocket* m_socket;

#if TCP_OPEN_UV_THREAD_HEARTBEAT == 1
	int m_curHeartTime;
	int m_curHeartCount;
	int m_resetHeartCount;
	int m_curHeartMaxCount;
	NET_HEART_TYPE m_sendHeartMsg;
#endif
};

TCPSocket* TCPSession::getTCPSocket()
{
	return m_socket;
}

unsigned int TCPSession::getPort()
{
	return getTCPSocket()->getPort();
}

const std::string& TCPSession::getIp()
{
	return getTCPSocket()->getIp();
}


void TCPSession::setResetHeartCount(int resetHeartCount)
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

void TCPSession::setHeartMaxCount(int maxCount)
{
#if TCP_OPEN_UV_THREAD_HEARTBEAT == 1
	m_curHeartMaxCount = maxCount;
#endif
}

NS_NET_UV_END
