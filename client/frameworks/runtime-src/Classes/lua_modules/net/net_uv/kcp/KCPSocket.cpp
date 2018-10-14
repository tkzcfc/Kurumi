#include "KCPSocket.h"

NS_NET_UV_BEGIN

// 连接超时时间 5S
#define KCP_SOCKET_CONNECT_TIMEOUT (5000)

KCPSocket::KCPSocket(uv_loop_t* loop)
	: m_socketAddr(NULL)
	, m_udp(NULL)
	, m_socketMng(NULL)
	, m_kcpState(State::DISCONNECT)
	, m_newConnectionCall(nullptr)
	, m_connectFilterCall(nullptr)
	, m_disconnectCall(nullptr)
	, m_releaseCount(5)
	, m_first_send_connect_msg_time(0)
	, m_last_send_connect_msg_time(0)
	, m_last_packet_recv_time(0)
	, m_last_update_time(0)
	, m_conv(0)
	, m_weakRefUdp(false)
	, m_weakRefSocketMng(false)
	, m_kcp(NULL)
	, m_runIdle(false)
{
	m_recvBuf = (char*)fc_malloc(KCP_MAX_MSG_SIZE);
	memset(m_recvBuf, 0, KCP_MAX_MSG_SIZE);
	m_loop = loop;
}

KCPSocket::~KCPSocket()
{
	if (m_socketAddr)
	{
		fc_free(m_socketAddr);
		m_socketAddr = NULL;
	}

	if (m_recvBuf)
	{
		fc_free(m_recvBuf);
		m_recvBuf = NULL;
	}

	if (m_udp)
	{
		if (!m_weakRefUdp)
		{
			net_closeHandle((uv_handle_t*)m_udp, net_closehandle_defaultcallback);
		}
		m_udp = NULL;
	}

	if (m_socketMng != NULL)
	{
		if (m_weakRefSocketMng)
		{
			m_socketMng->remove(getConv());
		}
		else
		{
			fc_free(m_socketMng);
		}
		m_socketMng = NULL;
	}
	stopIdle();
}

bool KCPSocket::bind(const char* ip, unsigned int port)
{
	this->setIp(ip);
	this->setPort(port);
	this->setIsIPV6(false);

	struct sockaddr_in bind_addr;
	int r = uv_ip4_addr(getIp().c_str(), getPort(), &bind_addr);

	if (r != 0)
	{
		return false;
	}

	if (m_udp)
	{
		net_closeHandle((uv_handle_t*)m_udp, net_closehandle_defaultcallback);
		m_udp = NULL;
	}

	m_udp = (uv_udp_t*)fc_malloc(sizeof(uv_udp_t));
	r = uv_udp_init(m_loop, m_udp);
	CHECK_UV_ASSERT(r);
	m_udp->data = this;

	r = uv_udp_bind(m_udp, (const struct sockaddr*) &bind_addr, UV_UDP_REUSEADDR);
	CHECK_UV_ASSERT(r);

	r = uv_udp_recv_start(m_udp, uv_on_alloc_buffer, uv_on_after_read);
	CHECK_UV_ASSERT(r);

	if (r == 0)
	{
		struct sockaddr* p_bind_addr = (struct sockaddr*)&bind_addr;
		struct sockaddr* socker_addr = (struct sockaddr*)fc_malloc(sizeof(struct sockaddr));
		memcpy(socker_addr, p_bind_addr, sizeof(struct sockaddr));
		this->setSocketAddr(socker_addr);
	}

	return (r == 0);
}

bool KCPSocket::bind6(const char* ip, unsigned int port)
{
	this->setIp(ip);
	this->setPort(port);
	this->setIsIPV6(true);

	struct sockaddr_in6 bind_addr;
	int r = uv_ip6_addr(getIp().c_str(), getPort(), &bind_addr);

	if (r != 0)
	{
		return false;
	}

	if (m_udp)
	{
		net_closeHandle((uv_handle_t*)m_udp, net_closehandle_defaultcallback);
		m_udp = NULL;
	}

	m_udp = (uv_udp_t*)fc_malloc(sizeof(uv_udp_t));
	r = uv_udp_init(m_loop, m_udp);
	CHECK_UV_ASSERT(r);
	m_udp->data = this;

	r = uv_udp_bind(m_udp, (const struct sockaddr*) &bind_addr, UV_UDP_REUSEADDR);
	CHECK_UV_ASSERT(r);

	r = uv_udp_recv_start(m_udp, uv_on_alloc_buffer, uv_on_after_read);
	CHECK_UV_ASSERT(r);

	if (r == 0)
	{
		struct sockaddr* p_bind_addr = (struct sockaddr*)&bind_addr;
		struct sockaddr* socker_addr = (struct sockaddr*)fc_malloc(sizeof(struct sockaddr));
		memcpy(socker_addr, p_bind_addr, sizeof(struct sockaddr));
		this->setSocketAddr(socker_addr);
	}

	return (r == 0);
}

bool KCPSocket::listen()
{
	if (m_socketMng)
		return true;

	m_kcpState = State::LISTEN;

	m_socketMng = (KCPSocketManager*)fc_malloc(sizeof(KCPSocketManager));
	new (m_socketMng) KCPSocketManager(m_loop);
	m_socketMng->setOwner(this);
	return true;
}

bool KCPSocket::connect(const char* ip, unsigned int port)
{
	if (m_kcpState != DISCONNECT)
	{
		return false;
	}

	this->setIp(ip);
	this->setPort(port);

	struct addrinfo hints;
	struct addrinfo* ainfo;
	struct addrinfo* rp;
	struct sockaddr_in* addr4 = NULL;
	struct sockaddr_in6* addr6 = NULL;
	struct sockaddr* addr = NULL;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_ADDRCONFIG;
	hints.ai_socktype = SOCK_STREAM;

	int ret = getaddrinfo(ip, NULL, &hints, &ainfo);

	if (ret == 0)
	{
		for (rp = ainfo; rp; rp = rp->ai_next)
		{
			if (rp->ai_family == AF_INET)
			{
				addr4 = (struct sockaddr_in*)rp->ai_addr;
				addr4->sin_port = htons(port);
				break;

			}
			else if (rp->ai_family == AF_INET6)
			{
				addr6 = (struct sockaddr_in6*)rp->ai_addr;
				addr6->sin6_port = htons(port);
				break;
			}
			else
			{
				continue;
			}
		}
		addr = addr4 ? (struct sockaddr*)addr4 : (struct sockaddr*)addr6;
		struct sockaddr* socker_addr = (struct sockaddr*)fc_malloc(sizeof(struct sockaddr));
		memcpy(socker_addr, addr, sizeof(struct sockaddr));
		this->setSocketAddr(socker_addr);

		if (m_udp)
		{
			net_closeHandle((uv_handle_t*)m_udp, net_closehandle_defaultcallback);
			m_udp = NULL;
		}
		m_udp = (uv_udp_t*)fc_malloc(sizeof(uv_udp_t));
		int r = uv_udp_init(m_loop, m_udp);
		CHECK_UV_ASSERT(r);

		m_udp->data = this;

		//struct sockaddr_in broadcast_addr;
		//r = uv_ip4_addr("0.0.0.0", 0, &broadcast_addr);
		//CHECK_UV_ASSERT(r);
		//r = uv_udp_bind(m_udp, (const struct sockaddr *)&broadcast_addr, 0);
		//CHECK_UV_ASSERT(r);
		//r = uv_udp_set_broadcast(m_udp, 1);
		//CHECK_UV_ASSERT(r);

		r = uv_udp_recv_start(m_udp, uv_on_alloc_buffer, uv_on_after_read);
		CHECK_UV_ASSERT(r);

		m_kcpState = State::WAIT_CONNECT;

		m_first_send_connect_msg_time = iclock();
		doSendConnectMsgPack(m_first_send_connect_msg_time);

		startIdle();

		return true;
	}
	NET_UV_LOG(NET_UV_L_ERROR, "[%s:%d]地址信息获取失败", ip, port);

	return false;
}

bool KCPSocket::send(char* data, int len)
{
	if (m_kcp == NULL)
	{
		return false;
	}
	ikcp_send(m_kcp, data, len);
	return true;
}

void KCPSocket::disconnect()
{
	// 未连接成功的客户端socket或者服务器listen socket
	if (getConv() == 0)
	{
		// 服务器listen socket
		if (m_socketMng != NULL)
		{
			m_kcpState = State::WAIT_DISCONNECT;
			m_releaseCount = 10;
			m_socketMng->stop_listen();
			startIdle();
		}
		else
		{
			shutdownSocket();
		}
	}
	else
	{
		std::string packet = kcp_making_disconnect_packet(getConv());
		udpSend((char*)packet.c_str(), packet.size());

		// 服务器socket
		if (m_weakRefSocketMng)
		{
			shutdownSocket();
		}
		// 客户端socket
		else
		{
			m_kcpState = State::WAIT_DISCONNECT;
			m_releaseCount = 10;
			startIdle();
		}
	}
	if (m_socketMng != NULL)
	{
		if (m_weakRefSocketMng)
		{
			m_socketMng->remove(getConv());
		}
	}
	if (m_kcp)
	{
		ikcp_release(m_kcp);
		m_kcp = NULL;
	}
}

void KCPSocket::socketUpdate(IUINT32 clock)
{
	m_last_update_time = clock;

	if (m_kcpState == State::DISCONNECT)
		return;

	if (m_kcpState == State::WAIT_CONNECT)
	{
		// 连接超时
		if (m_last_send_connect_msg_time - m_first_send_connect_msg_time > KCP_SOCKET_CONNECT_TIMEOUT)
		{
			doConnectTimeout();
			return;
		}
		m_last_send_connect_msg_time = m_last_update_time;
		//doSendConnectMsgPack(clock);
	}
	else if (m_kcpState == State::WAIT_DISCONNECT)
	{
		m_releaseCount--;
		if (m_releaseCount <= 0)
		{
			shutdownSocket();
		}
	}
	else
	{
		// 发送超时
		// 三分钟没有任何消息返回
		if (m_last_packet_recv_time > 0 && clock - m_last_packet_recv_time > 300000)
		{
			doSendTimeout();
			return;
		}

		if (m_kcp)
		{
			ikcp_update(m_kcp, clock);
		}
	}
}

void KCPSocket::shutdownSocket()
{
	m_kcpState = State::DISCONNECT;

	if (m_weakRefUdp && m_udp)
	{
		m_udp = NULL;
		if (m_closeCall != nullptr)
		{
			m_closeCall(this);
		}
		return;
	}

	if (m_udp == NULL)
	{
		return;
	}
	uv_udp_recv_stop(m_udp);
	net_closeHandle((uv_handle_t*)m_udp, uv_on_close_socket);
	m_udp = NULL;

	stopIdle();
}

void KCPSocket::setSocketAddr(struct sockaddr* addr)
{
	if (m_socketAddr == addr)
		return;
	if (m_socketAddr)
	{
		fc_free(m_socketAddr);
	}
	m_socketAddr = addr;
}

void KCPSocket::udpSend(const char* data, int len)
{
	if (getSocketAddr() == NULL || m_udp == NULL)
	{
		return;
	}
	uv_buf_t* buf = (uv_buf_t*)fc_malloc(sizeof(uv_buf_t));
	buf->base = (char*)fc_malloc(len);
	buf->len = len;

	memcpy(buf->base, data, len);

	uv_udp_send_t* udp_send = (uv_udp_send_t*)fc_malloc(sizeof(uv_udp_send_t));
	udp_send->data = buf;
	int r = uv_udp_send(udp_send, m_udp, buf, 1, getSocketAddr(), uv_on_udp_send);

	if (r != 0)
	{
		NET_UV_LOG(NET_UV_L_ERROR, "udp send error %s", uv_strerror(r));
	}
}

void KCPSocket::udpSend(const char* data, int len, const struct sockaddr* addr)
{
	if (m_udp == NULL)
	{
		return;
	}
	uv_buf_t* buf = (uv_buf_t*)fc_malloc(sizeof(uv_buf_t));
	buf->base = (char*)fc_malloc(len);
	buf->len = len;

	memcpy(buf->base, data, len);

	uv_udp_send_t* udp_send = (uv_udp_send_t*)fc_malloc(sizeof(uv_udp_send_t));
	udp_send->data = buf;
	int r = uv_udp_send(udp_send, m_udp, buf, 1, addr, uv_on_udp_send);

	if (r != 0)
	{
		NET_UV_LOG(NET_UV_L_ERROR, "udp send error %s", uv_strerror(r));
	}
}

void KCPSocket::kcpInput(const char* data, long size)
{
	m_last_packet_recv_time = m_last_update_time;
	ikcp_input(m_kcp, data, size);

	int kcp_recvd_bytes = 0;
	do
	{
		kcp_recvd_bytes = ikcp_recv(m_kcp, m_recvBuf, KCP_MAX_MSG_SIZE);

		if (kcp_recvd_bytes < 0)
		{
			kcp_recvd_bytes = 0;
		}
		m_recvCall(m_recvBuf, kcp_recvd_bytes);
	} while (kcp_recvd_bytes > 0);
}

void KCPSocket::initKcp(IUINT32 conv)
{
	if (m_kcp)
	{
		ikcp_release(m_kcp);
		m_kcp = NULL;
	}
	m_kcp = ikcp_create(conv, this);
	m_kcp->output = &KCPSocket::udp_output;

	ikcp_wndsize(m_kcp, 128, 128);

	// 启动快速模式
	// 第二个参数 nodelay-启用以后若干常规加速将启动
	// 第三个参数 interval为内部处理时钟，默认设置为 10ms
	// 第四个参数 resend为快速重传指标，设置为2
	// 第五个参数 为是否禁用常规流控，这里禁止
	ikcp_nodelay(m_kcp, 1, 10, 2, 1);
	//ikcp_nodelay(m_kcp, 1, 5, 1, 1); // 设置成1次ACK跨越直接重传, 这样反应速度会更快. 内部时钟5毫秒.
}

void KCPSocket::onUdpRead(uv_udp_t* handle, ssize_t nread, const uv_buf_t* buf, const struct sockaddr* addr, unsigned flags)
{
	switch (m_kcpState)
	{
	case KCPSocket::WAIT_CONNECT:
	{
		if (kcp_is_send_back_conv_packet(buf->base, nread))
		{
			unsigned int conv = kcp_grab_conv_from_send_back_conv_packet(buf->base, nread);
			if (conv == 0)
			{
				m_kcpState = State::DISCONNECT;
				m_connectCall(this, 0);
				return;
			}
			initKcp(conv);
			setConv(conv);
			m_kcpState = State::CONNECT;

			m_connectCall(this, 1);
		}
	}
	break;
	case KCPSocket::LISTEN:
	{
		if (kcp_is_connect_packet(buf->base, nread))
		{
			KCPSocket* socket = NULL;
			if (m_connectFilterCall != nullptr)
			{
				if (m_connectFilterCall(addr))
				{
					socket = m_socketMng->accept(handle, addr);
				}
			}
			else
			{
				socket = m_socketMng->accept(handle, addr);
			}
			if (socket != NULL)
			{
				m_newConnectionCall(socket);

				std::string packet = kcp_making_send_back_conv_packet(socket->getConv());
				udpSend((char*)packet.c_str(), (int)packet.size(), addr);
			}
		}
		else if (kcp_is_disconnect_packet(buf->base, nread))
		{
			unsigned int conv = kcp_grab_conv_from_disconnect_packet(buf->base, nread);
			m_socketMng->disconnect(conv);
		}
		else
		{
			m_socketMng->input(ikcp_getconv(buf->base), buf->base, nread);
		}
	}break;
	case KCPSocket::CONNECT:
	{
		resetLastPacketRecvTime();

		if (kcp_is_disconnect_packet(buf->base, nread))
		{
			unsigned int conv = kcp_grab_conv_from_disconnect_packet(buf->base, nread);
			if (conv == getConv())
			{
				if (m_kcp)
				{
					ikcp_release(m_kcp);
					m_kcp = NULL;
				}
				m_kcpState = State::WAIT_DISCONNECT;
				m_releaseCount = 0;
			}
		}
		else
		{
			kcpInput(buf->base, nread);
		}
	}
	break;
	default:
		break;
	}
}

void KCPSocket::doSendConnectMsgPack(IUINT32 clock)
{
	m_last_send_connect_msg_time = clock;
	std::string packet = kcp_making_connect_packet();
	udpSend((char*)packet.c_str(), packet.size());
}

void KCPSocket::doConnectTimeout()
{
	stopIdle();
	if (m_connectCall != nullptr)
	{
		m_connectCall(this, 2);
	}
	m_kcpState = State::DISCONNECT;
}

void KCPSocket::doSendTimeout()
{
	if (m_kcp)
	{
		ikcp_release(m_kcp);
		m_kcp = NULL;
	}
	shutdownSocket();
}

void KCPSocket::updateKcp(IUINT32 update_clock)
{
	if (!m_runIdle)
		return;
	socketUpdate(update_clock);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void KCPSocket::uv_on_close_socket(uv_handle_t* socket)
{
	KCPSocket* s = (KCPSocket*)(socket->data);
	if (s->m_closeCall != nullptr)
	{
		s->m_closeCall(s);
	}
	fc_free(socket);
}

void KCPSocket::uv_on_udp_send(uv_udp_send_t *req, int status)
{
	if (status != 0)
	{
		NET_UV_LOG(NET_UV_L_ERROR, "udp send error %s", uv_strerror(status));
	}
	uv_buf_t* buf = (uv_buf_t*)req->data;
	fc_free(buf->base);
	fc_free(buf);
	fc_free(req);
}

void KCPSocket::uv_on_after_read(uv_udp_t* handle, ssize_t nread, const uv_buf_t* buf, const struct sockaddr* addr, unsigned flags)
{
	if (nread < 0)
	{
		NET_UV_LOG(NET_UV_L_ERROR, "udp read error %s\n", uv_err_name(nread));
		return;
	}
	if (addr == NULL)
	{
		//NET_UV_LOG(NET_UV_L_ERROR, "addr is null");
		return;
	}

	if (nread > 0)
	{
		KCPSocket* s = (KCPSocket*)handle->data;
		s->onUdpRead(handle, nread, buf, addr, flags);
	}
}

int KCPSocket::udp_output(const char *buf, int len, ikcpcb *kcp, void *user)
{
	((KCPSocket*)user)->udpSend(buf, len);
	return 0;
}

NS_NET_UV_END