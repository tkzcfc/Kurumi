#pragma once

#include "KCPCommon.h"
#include "KCPUtils.h"
#include "KCPSocketManager.h"

NS_NET_UV_BEGIN

#define KCP_MAX_MSG_SIZE (1024*2)

// 新连接过滤回调，用于过滤黑名单 返回false表示不接受该连接
using KCPSocketConnectFilterCall = std::function<bool(const struct sockaddr*)>;
using KCPSocketNewConnectionCall = std::function<void(Socket*)>;
using KCPSocketDisconnectCall = std::function<void(Socket*, unsigned int)>;

class KCPSocket : public Socket
{
public:
	KCPSocket() = delete;

	KCPSocket(const KCPSocket&) = delete;

	KCPSocket(uv_loop_t* loop);

	virtual ~KCPSocket();

	virtual bool bind(const char* ip, unsigned int port)override;

	virtual bool bind6(const char* ip, unsigned int port)override;

	virtual bool listen()override;

	virtual bool connect(const char* ip, unsigned int port)override;

	virtual bool send(char* data, int len)override;

	virtual void disconnect()override;

	inline void setNewConnectionCallback(const KCPSocketNewConnectionCall& call);
	inline void setDisconnectCallback(const KCPSocketDisconnectCall& call);
	inline void setConnectFilterCallback(const KCPSocketConnectFilterCall& call);

protected:
	inline uv_udp_t* getUdp();

	inline void setWeakRefUdp(uv_udp_t* udp);

	inline void setWeakRefSocketManager(KCPSocketManager* manager);

	void socketUpdate(IUINT32 clock);

	void shutdownSocket();

	void setSocketAddr(struct sockaddr* addr);

	inline struct sockaddr* getSocketAddr();

	void udpSend(const char* data, int len);

	void udpSend(const char* data, int len, const struct sockaddr* addr);

	void kcpInput(const char* data, long size);

	void initKcp(IUINT32 conv);

	void onUdpRead(uv_udp_t* handle, ssize_t nread, const uv_buf_t* buf, const struct sockaddr* addr, unsigned flags);

	void doSendConnectMsgPack(IUINT32 clock);

	void doConnectTimeout();

	void doSendTimeout();

	inline void resetLastPacketRecvTime();

	inline void setConv(IUINT32 conv);

	inline IUINT32 getConv();

	inline void startIdle();

	inline void stopIdle();

	void updateKcp(IUINT32 update_clock);

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
	bool m_weakRefUdp;
	struct sockaddr* m_socketAddr;

	bool m_runIdle;

	State m_kcpState;
	char* m_recvBuf;

	ikcpcb* m_kcp;
	IUINT32 m_first_send_connect_msg_time;
	IUINT32 m_last_send_connect_msg_time;
	IUINT32 m_last_packet_recv_time;
	IUINT32 m_last_update_time;
	IUINT32 m_conv;

	IINT32 m_releaseCount;

	KCPSocketManager* m_socketMng;
	bool m_weakRefSocketMng;

	KCPSocketNewConnectionCall m_newConnectionCall;
	KCPSocketDisconnectCall m_disconnectCall;
	KCPSocketConnectFilterCall m_connectFilterCall;

	friend class KCPSocketManager;
	friend class KCPServer;
	friend class KCPSession;
protected:
	static void uv_on_close_socket(uv_handle_t* socket);
	static void uv_on_udp_send(uv_udp_send_t *req, int status);
	static void uv_on_after_read(uv_udp_t* handle, ssize_t nread, const uv_buf_t* buf, const struct sockaddr* addr, unsigned flags);
	static int udp_output(const char *buf, int len, ikcpcb *kcp, void *user);
};

uv_udp_t* KCPSocket::getUdp()
{
	return m_udp;
}

void KCPSocket::setWeakRefUdp(uv_udp_t* udp)
{
	m_udp = udp;
	m_weakRefUdp = true;
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

void KCPSocket::setDisconnectCallback(const KCPSocketDisconnectCall& call)
{
	m_disconnectCall = std::move(call);
}

void KCPSocket::setConnectFilterCallback(const KCPSocketConnectFilterCall& call)
{
	m_connectFilterCall = std::move(call);
}

void KCPSocket::resetLastPacketRecvTime()
{
	m_last_packet_recv_time = m_last_update_time;
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

NS_NET_UV_END

