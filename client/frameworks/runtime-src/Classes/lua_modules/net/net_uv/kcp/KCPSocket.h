#pragma once

#include "KCPCommon.h"
#include "KCPUtils.h"
#include "KCPSocketManager.h"

NS_NET_UV_BEGIN

#define KCP_MAX_MSG_SIZE (1024*2)

// 新连接过滤回调，用于过滤黑名单 返回false表示不接受该连接
using KCPSocketConnectFilterCall = std::function<bool(const struct sockaddr*)>;
using KCPSocketNewConnectionCall = std::function<void(Socket*)>;

class KCPSocket : public Socket
{
public:
	KCPSocket() = delete;

	KCPSocket(const KCPSocket&) = delete;

	KCPSocket(uv_loop_t* loop);

	virtual ~KCPSocket();

	virtual uint32_t bind(const char* ip, uint32_t port)override;

	virtual uint32_t bind6(const char* ip, uint32_t port)override;

	virtual bool listen()override;

	virtual bool connect(const char* ip, uint32_t port)override;

	virtual bool send(char* data, int32_t len)override;

	virtual void disconnect()override;

	bool accept(const struct sockaddr* addr, IUINT32 conv);

	inline void setNewConnectionCallback(const KCPSocketNewConnectionCall& call);
	inline void setConnectFilterCallback(const KCPSocketConnectFilterCall& call);

	void svrIdleRun();

protected:
	inline uv_udp_t* getUdp();
	
	inline void setWeakRefSocketManager(KCPSocketManager* manager);

	void svr_connect(struct sockaddr* addr, IUINT32 conv);

	void socketUpdate(IUINT32 clock);

	void shutdownSocket(bool isCallClose = true);

	void setSocketAddr(struct sockaddr* addr);

	inline struct sockaddr* getSocketAddr();

	void udpSend(const char* data, int32_t len);

	void udpSend(const char* data, int32_t len, const struct sockaddr* addr);

	void kcpInput(const char* data, long size);

	void initKcp(IUINT32 conv);

	void onUdpRead(uv_udp_t* handle, ssize_t nread, const uv_buf_t* buf, const struct sockaddr* addr, uint32_t flags);

	void connectResult(int32_t status);

	void doSendSvrConnectMsgPack(IUINT32 clock);

	void doSendConnectMsgPack(IUINT32 clock);

	void doConnectTimeout();

	void doSendTimeout();
	
	inline void setConv(IUINT32 conv);

	inline IUINT32 getConv();

	inline void startIdle();

	inline void stopIdle();

	inline void setConnectTimeoutTime(uint32_t timout);

protected:

	enum State
	{
		WAIT_CONNECT,
		CONNECT,
		WAIT_DISCONNECT,
		LISTEN,
		DISCONNECT,
		NONE,
	};

	uv_udp_t* m_udp;
	struct sockaddr* m_socketAddr;

	bool m_runIdle;

	State m_kcpState;
	char* m_recvBuf;

	ikcpcb* m_kcp;
	IUINT32 m_first_send_connect_msg_time;
	IUINT32 m_last_send_connect_msg_time;
	IUINT32 m_last_kcp_packet_recv_time;
	IUINT32 m_last_kcp_packet_send_time;
	IUINT32 m_last_update_time;
	IUINT32 m_conv;
	IINT32 m_releaseCount;

	uint32_t m_connectTimeoutTime;
	uint32_t m_burrowCount;
	
	KCPSocketManager* m_socketMng;
	bool m_weakRefSocketMng;

	KCPSocketNewConnectionCall m_newConnectionCall;
	KCPSocketConnectFilterCall m_connectFilterCall;

	friend class KCPSocketManager;
	friend class KCPServer;
	friend class KCPSession;
protected:
	static void uv_on_close_socket(uv_handle_t* socket);
	static void uv_on_udp_send(uv_udp_send_t *req, int32_t status);
	static void uv_on_after_read(uv_udp_t* handle, ssize_t nread, const uv_buf_t* buf, const struct sockaddr* addr, unsigned flags);
	static int32_t udp_output(const char *buf, int32_t len, ikcpcb *kcp, void *user);
};

uv_udp_t* KCPSocket::getUdp()
{
	return m_udp;
}

void KCPSocket::setWeakRefSocketManager(KCPSocketManager* manager)
{
	m_weakRefSocketMng = true;
	m_socketMng = manager;
}

struct sockaddr* KCPSocket::getSocketAddr()
{
	return m_socketAddr;
}

void KCPSocket::setNewConnectionCallback(const KCPSocketNewConnectionCall& call)
{
	m_newConnectionCall = std::move(call);
}

void KCPSocket::setConnectFilterCallback(const KCPSocketConnectFilterCall& call)
{
	m_connectFilterCall = std::move(call);
}

void KCPSocket::setConv(IUINT32 conv)
{
	m_conv = conv;
}

IUINT32 KCPSocket::getConv()
{
	return m_conv;
}

void KCPSocket::startIdle()
{
	m_runIdle = true;
}

void KCPSocket::stopIdle()
{
	m_runIdle = false;
}

void KCPSocket::setConnectTimeoutTime(uint32_t timout)
{
	m_connectTimeoutTime = timout;
}

NS_NET_UV_END

