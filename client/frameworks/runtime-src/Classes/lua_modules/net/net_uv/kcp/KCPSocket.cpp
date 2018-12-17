#include "KCPSocket.h"

NS_NET_UV_BEGIN

// 连接超时时间
/// 连接到服务器超时时间
#define KCP_SOCKET_CONNECT_FIRST_TIMEOUT (5000)
/// 重定向到服务器超时时间
#define KCP_SOCKET_CONNECT_SECOND_TIMEOUT (30000)

KCPSocket::KCPSocket(uv_loop_t* loop)
	: m_socketAddr(NULL)
	, m_udp(NULL)
	, m_socketMng(NULL)
	, m_kcpState(State::DISCONNECT)
	, m_newConnectionCall(nullptr)
	, m_connectFilterCall(nullptr)
	, m_releaseCount(5)
	, m_first_send_connect_msg_time(0)
	, m_last_send_connect_msg_time(0)
	, m_last_kcp_packet_recv_time(0)
	, m_last_update_time(0)
	, m_last_kcp_packet_send_time(0)
	, m_conv(0)
	, m_weakRefSocketMng(false)
	, m_kcp(NULL)
	, m_runIdle(false)
	, m_connectTimeoutTime(KCP_SOCKET_CONNECT_FIRST_TIMEOUT)
	, m_burrowCount(0)
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
		net_closeHandle((uv_handle_t*)m_udp, net_closehandle_defaultcallback);
		m_udp = NULL;
	}

	if (m_socketMng != NULL)
	{
		if (m_weakRefSocketMng)
		{
			m_socketMng->remove(this);
		}
		else
		{
			m_socketMng->~KCPSocketManager();
			fc_free(m_socketMng);
		}
		m_socketMng = NULL;
	}
	stopIdle();
}

uint32_t KCPSocket::bind(const char* ip, uint32_t port)
{
	if (m_udp != NULL)
	{
		return 0;
	}

	this->setIp(ip);
	this->setPort(port);
	this->setIsIPV6(false);

	struct sockaddr_in bind_addr;
	int32_t r = uv_ip4_addr(ip, port, &bind_addr);

	if (r != 0)
	{
		return 0;
	}

	m_udp = (uv_udp_t*)fc_malloc(sizeof(uv_udp_t));
	r = uv_udp_init(m_loop, m_udp);
	CHECK_UV_ASSERT(r);
	m_udp->data = this;

	r = uv_udp_bind(m_udp, (const struct sockaddr*) &bind_addr, UV_UDP_REUSEADDR);

	if (r != 0)
	{
		return 0;
	}
	net_adjustBuffSize((uv_handle_t*)m_udp, KCP_UV_SOCKET_RECV_BUF_LEN, KCP_UV_SOCKET_SEND_BUF_LEN);

	if (port == 0)
	{
		return net_udp_getPort(m_udp);
	}
	return port;
}

uint32_t KCPSocket::bind6(const char* ip, uint32_t port)
{
	if (m_udp != NULL)
	{
		return 0;
	}

	this->setIp(ip);
	this->setPort(port);
	this->setIsIPV6(true);

	struct sockaddr_in6 bind_addr;
	int32_t r = uv_ip6_addr(ip, port, &bind_addr);

	if (r != 0)
	{
		return 0;
	}

	m_udp = (uv_udp_t*)fc_malloc(sizeof(uv_udp_t));
	r = uv_udp_init(m_loop, m_udp);
	CHECK_UV_ASSERT(r);
	m_udp->data = this;

	r = uv_udp_bind(m_udp, (const struct sockaddr*) &bind_addr, UV_UDP_REUSEADDR);

	if (r != 0)
	{
		return 0;
	}
	net_adjustBuffSize((uv_handle_t*)m_udp, KCP_UV_SOCKET_RECV_BUF_LEN, KCP_UV_SOCKET_SEND_BUF_LEN);

	if (port == 0)
	{
		return net_udp_getPort(m_udp);
	}
	return port;
}

bool KCPSocket::listen()
{
	if (m_socketMng)
		return true;

	if (m_udp == NULL)
		return false;

	int32_t r = uv_udp_recv_start(m_udp, uv_on_alloc_buffer, uv_on_after_read);
	if (r != 0)
	{
		NET_UV_LOG(NET_UV_L_ERROR, "uv_udp_recv_start error: %s", net_getUVError(r).c_str());
		return false;
	}

	m_kcpState = State::LISTEN;

	m_socketMng = (KCPSocketManager*)fc_malloc(sizeof(KCPSocketManager));
	new (m_socketMng) KCPSocketManager(m_loop);
	m_socketMng->setOwner(this);
	return true;
}

bool KCPSocket::connect(const char* ip, uint32_t port)
{
	if (m_kcpState != DISCONNECT)
	{
		return false;
	}

	struct sockaddr* addr = net_getsocketAddr(ip, port, NULL);

	if (addr == NULL)
	{
		NET_UV_LOG(NET_UV_L_ERROR, "[%s:%d]地址信息获取失败", ip, port);
		return false;
	}

	this->setIp(ip);
	this->setPort(port);
	this->setSocketAddr(addr);

	if (m_udp == NULL)
	{
		m_udp = (uv_udp_t*)fc_malloc(sizeof(uv_udp_t));
		int32_t r = uv_udp_init(m_loop, m_udp);
		CHECK_UV_ASSERT(r);
		m_udp->data = this;

		struct sockaddr_in bind_addr;
		r = uv_ip4_addr("0.0.0.0", 0, &bind_addr);
		CHECK_UV_ASSERT(r);
		r = uv_udp_bind(m_udp, (const struct sockaddr *)&bind_addr, 0);
		CHECK_UV_ASSERT(r);
		//r = uv_udp_set_broadcast(m_udp, 1);
		//CHECK_UV_ASSERT(r);

		net_adjustBuffSize((uv_handle_t*)m_udp, KCP_UV_SOCKET_RECV_BUF_LEN, KCP_UV_SOCKET_SEND_BUF_LEN);
	}

	int32_t r = uv_udp_recv_start(m_udp, uv_on_alloc_buffer, uv_on_after_read);
	if (r != 0)
	{
		NET_UV_LOG(NET_UV_L_ERROR, "uv_udp_recv_start error: %s", net_getUVError(r).c_str());
		return false;
	}

	m_kcpState = State::WAIT_CONNECT;

	m_first_send_connect_msg_time = iclock();
	doSendConnectMsgPack(m_first_send_connect_msg_time);
	this->setConnectTimeoutTime(KCP_SOCKET_CONNECT_FIRST_TIMEOUT);

	startIdle();

	return true;
}

bool KCPSocket::send(char* data, int32_t len)
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
	if (m_kcp)
	{
		ikcp_release(m_kcp);
		m_kcp = NULL;
	}
	setConv(0);

	switch (m_kcpState)
	{
	case KCPSocket::State::WAIT_CONNECT:
	{
		shutdownSocket();
	}
	break;
	case KCPSocket::State::CONNECT:
	{
		std::string packet = kcp_making_disconnect_packet(getConv());
		udpSend((char*)packet.c_str(), packet.size());

		m_kcpState = State::WAIT_DISCONNECT;
		m_releaseCount = 10;
		startIdle();
	}
	break;
	case KCPSocket::State::LISTEN:
	{
		m_kcpState = State::WAIT_DISCONNECT;
		m_releaseCount = 10;
		m_socketMng->stop_listen();
		startIdle();
	}
		break;
	}
}

bool KCPSocket::accept(const struct sockaddr* addr, IUINT32 conv)
{
	if (m_socketMng == NULL)
		return false;

	std::string strip;
	uint32_t port;
	uint32_t addrlen = net_getsockAddrIPAndPort(addr, strip, port);
	if (addrlen == 0)
	{
		NET_UV_LOG(NET_UV_L_ERROR, "kcp服务器创建KCPSocket失败,地址解析失败");
		return false;
	}

	struct sockaddr* socker_addr = (struct sockaddr*)fc_malloc(addrlen);
	memcpy(socker_addr, addr, addrlen);

	KCPSocket* socket = (KCPSocket*)fc_malloc(sizeof(KCPSocket));
	new (socket) KCPSocket(m_loop);
	socket->setIp(strip);
	socket->setPort(port);
	socket->setIsIPV6(socker_addr->sa_family == AF_INET6);
	socket->setWeakRefSocketManager(m_socketMng); 
	socket->svr_connect(socker_addr, conv);
	
	m_socketMng->push(socket);

	uint32_t listenPort = net_udp_getPort(socket->getUdp());
	std::string packet = kcp_making_send_back_conv_packet(conv, listenPort);
	udpSend((char*)packet.c_str(), (int32_t)packet.size(), addr);

	return true;
}

void KCPSocket::svr_connect(struct sockaddr* addr, IUINT32 conv)
{
	this->setSocketAddr(addr);
	this->setConv(conv);

	if (m_udp == NULL)
	{
		m_udp = (uv_udp_t*)fc_malloc(sizeof(uv_udp_t));
		int32_t r = uv_udp_init(m_loop, m_udp);
		CHECK_UV_ASSERT(r);
		m_udp->data = this;

		struct sockaddr_in bind_addr;
		r = uv_ip4_addr("0.0.0.0", 0, &bind_addr);
		CHECK_UV_ASSERT(r);
		r = uv_udp_bind(m_udp, (const struct sockaddr *)&bind_addr, 0);
		CHECK_UV_ASSERT(r);
		//r = uv_udp_set_broadcast(m_udp, 1);
		//CHECK_UV_ASSERT(r);

		net_adjustBuffSize((uv_handle_t*)m_udp, KCP_UV_SOCKET_RECV_BUF_LEN, KCP_UV_SOCKET_SEND_BUF_LEN);

		r = uv_udp_recv_start(m_udp, uv_on_alloc_buffer, uv_on_after_read);
		CHECK_UV_ASSERT(r);
	}

	m_kcpState = State::WAIT_CONNECT;

	m_first_send_connect_msg_time = iclock();
	doSendSvrConnectMsgPack(m_first_send_connect_msg_time);
	this->setConnectTimeoutTime(KCP_SOCKET_CONNECT_SECOND_TIMEOUT);

	startIdle();
}

void KCPSocket::svrIdleRun()
{
	if (m_socketMng)
	{
		m_socketMng->idleRun();
	}
}

void KCPSocket::socketUpdate(IUINT32 clock)
{
	if (!m_runIdle)
		return;

	m_last_update_time = clock;

	switch (m_kcpState)
	{
	case KCPSocket::State::CONNECT:
	{
		if (m_last_kcp_packet_recv_time == 0)
		{
			m_last_kcp_packet_recv_time = clock;
		}

		// 发送超时
		// 一分钟没有任何消息返回
		if (clock - m_last_kcp_packet_recv_time > 60000)
		{
			doSendTimeout();
			return;
		}

		if (m_kcp)
		{
			ikcp_update(m_kcp, clock);
		}

		// 连接成功后，持续发送消息一段时间。
		if (m_burrowCount <= 5 && clock - m_last_send_connect_msg_time >= 1000)
		{
			doSendConnectMsgPack(clock);
			m_burrowCount++;
		}
	}
	break;
	case KCPSocket::State::WAIT_CONNECT:
	{
		// 连接超时
		if (m_first_send_connect_msg_time > 0 && clock - m_first_send_connect_msg_time > m_connectTimeoutTime)
		{
			doConnectTimeout();
			return;
		}

		if (clock - m_last_send_connect_msg_time >= 1000)
		{
			if (m_socketMng)
			{
				doSendSvrConnectMsgPack(clock);
			}
			else
			{
				doSendConnectMsgPack(clock);
			}
		}
	}
		break;
	case KCPSocket::State::WAIT_DISCONNECT:
	{
		if (m_socketMng && m_socketMng->getOwner() == this)
		{
			if (m_socketMng->getAwaitConnectCount() <= 0)
			{
				m_releaseCount--;
				if (m_releaseCount <= 0)
				{
					shutdownSocket();
				}
			}
		}
		else
		{
			m_releaseCount--;
			if (m_releaseCount <= 0)
			{
				shutdownSocket();
			}
		}
	}
		break;
	}
}

void KCPSocket::shutdownSocket(bool isCallClose)
{
	m_first_send_connect_msg_time = 0;
	m_last_send_connect_msg_time = 0;
	m_kcpState = State::DISCONNECT;
	setConv(0);
	
	if (m_udp == NULL)
	{
		stopIdle();
		return;
	}
	uv_udp_recv_stop(m_udp);
	if (!isCallClose)
	{
		net_closeHandle((uv_handle_t*)m_udp, net_closehandle_defaultcallback);
	}
	else
	{
		net_closeHandle((uv_handle_t*)m_udp, uv_on_close_socket);
	}
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

void KCPSocket::udpSend(const char* data, int32_t len)
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
	int32_t r = uv_udp_send(udp_send, m_udp, buf, 1, getSocketAddr(), uv_on_udp_send);

	if (r != 0)
	{
		NET_UV_LOG(NET_UV_L_ERROR, "udp send error %s", uv_strerror(r));
	}
}

void KCPSocket::udpSend(const char* data, int32_t len, const struct sockaddr* addr)
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
	int32_t r = uv_udp_send(udp_send, m_udp, buf, 1, addr, uv_on_udp_send);

	if (r != 0)
	{
		NET_UV_LOG(NET_UV_L_ERROR, "udp send error %s", uv_strerror(r));
	}
}

void KCPSocket::kcpInput(const char* data, long size)
{
	if (size <= 0 || m_kcp == NULL)
		return;
	
	m_last_kcp_packet_recv_time = m_last_update_time;
	
	ikcp_input(m_kcp, data, size);

	int32_t kcp_recvd_bytes = 0;
	do
	{
		if(m_kcp == NULL) break;
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
	m_kcp->stream = 1;

	ikcp_wndsize(m_kcp, 128, 128);

	// 启动快速模式
	// 第二个参数 nodelay-启用以后若干常规加速将启动
	// 第三个参数 interval为内部处理时钟，默认设置为 10ms
	// 第四个参数 resend为快速重传指标，设置为2
	// 第五个参数 为是否禁用常规流控，这里禁止
	ikcp_nodelay(m_kcp, 1, 10, 2, 1);
	//ikcp_nodelay(m_kcp, 1, 5, 1, 1); // 设置成1次ACK跨越直接重传, 这样反应速度会更快. 内部时钟5毫秒.
}

void KCPSocket::onUdpRead(uv_udp_t* handle, ssize_t nread, const uv_buf_t* buf, const struct sockaddr* addr, uint32_t flags)
{
	// 监听套接字，只判断连接请求
	if (m_kcpState == KCPSocket::State::LISTEN)
	{
		if (kcp_is_connect_packet(buf->base, nread))
		{
			if (m_socketMng->isAccept(addr))
			{
				KCPSocket* socket = NULL;
				if (m_connectFilterCall != nullptr)
				{
					if (m_connectFilterCall(addr))
					{
						this->accept(addr, m_socketMng->getNewConv());
					}
				}
				else
				{
					this->accept(addr, m_socketMng->getNewConv());
				}
			}
		}
		return;
	}

	if (kcp_is_disconnect_packet(buf->base, nread))
	{
		if (m_kcpState == KCPSocket::CONNECT)
		{
			uint32_t conv = kcp_grab_conv_from_disconnect_packet(buf->base, nread);
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
	}
	else if (kcp_is_send_back_conv_packet(buf->base, nread)) 
	{
		if (m_kcpState == KCPSocket::WAIT_CONNECT)
		{
			uint32_t conv, port;
			bool suc = kcp_grab_conv_from_send_back_conv_packet(buf->base, nread, conv, port);
			if (suc == false)
			{
				connectResult(0);
				return;
			}

			// 获取IP
			std::string szIp;
			uint32_t tmp;
			if (net_getsockAddrIPAndPort(getSocketAddr(), szIp, tmp) <= 0)
			{
				connectResult(0);
				return;
			}
			// 端口重定向
			struct sockaddr* addr = net_getsocketAddr(szIp.c_str(), port, NULL);

			if (addr == NULL)
			{
				connectResult(0);
				return;
			}
			this->setSocketAddr(addr);

			m_first_send_connect_msg_time = m_last_update_time;
			this->setConnectTimeoutTime(KCP_SOCKET_CONNECT_SECOND_TIMEOUT);

			// 向新端口发送数据
			doSendConnectMsgPack(iclock());

			setConv(conv);
		}
	}
	else if (kcp_is_svr_connect_packet(buf->base, nread)) 
	{
		if (m_kcpState == State::WAIT_CONNECT)
		{
			uint32_t conv = kcp_grab_conv_from_svr_connect_packet(buf->base, nread);
			if (conv == 0)
			{
				connectResult(0);
				return;
			}

			// 地址重定向
			uint32_t addrlen = 0;
			if (addr->sa_family == AF_INET6)
			{
				addrlen = sizeof(struct sockaddr_in6);
			}
			else
			{
				addrlen = sizeof(struct sockaddr_in);
			}
			if (addrlen == 0)
			{
				connectResult(0);
				return;
			}
			struct sockaddr* socker_addr = (struct sockaddr*)fc_malloc(addrlen);
			memcpy(socker_addr, addr, addrlen);

			this->setSocketAddr(socker_addr);

			std::string packet = kcp_making_svr_send_back_conv_packet(conv);
			udpSend((char*)packet.c_str(), (int32_t)packet.size(), addr);

			setConv(conv);
			initKcp(conv);
			connectResult(1);
			return;
		}
	}
	else if (kcp_is_svr_send_back_conv_packet(buf->base, nread)) 
	{
		if (m_kcpState == State::WAIT_CONNECT)
		{
			uint32_t conv = kcp_grab_conv_from_svr_send_back_conv_packet(buf->base, nread);

			if (conv == 0 || conv != getConv())
			{
				connectResult(0);
				return;
			}
			initKcp(conv);
			connectResult(1);
			return;
		}
	}
	// 连接请求，客户端不进行处理，该消息可用于打洞，不影响kcpinput
	else if (kcp_is_connect_packet(buf->base, nread))
	{}
	else
	{
		if (m_kcpState == State::CONNECT)
		{
			kcpInput(buf->base, nread);
		}
	}
}

void KCPSocket::connectResult(int32_t status)
{
	if (status == 1)
	{
		m_kcpState = State::CONNECT;
		m_last_kcp_packet_recv_time = 0;
		m_last_kcp_packet_send_time = 0;
		m_burrowCount = 0;
	}
	else
	{
		m_kcpState = State::DISCONNECT;
	}
	if (m_connectCall)
	{
		m_connectCall(this, status);
	}
}

void KCPSocket::doSendSvrConnectMsgPack(IUINT32 clock)
{
	m_last_send_connect_msg_time = clock;
	std::string packet = kcp_making_svr_connect_packet(getConv());
	udpSend((char*)packet.c_str(), packet.size());
}

void KCPSocket::doSendConnectMsgPack(IUINT32 clock)
{
	m_last_send_connect_msg_time = clock;
	std::string packet = kcp_making_connect_packet();
	udpSend((char*)packet.c_str(), packet.size());
}

void KCPSocket::doConnectTimeout()
{
	shutdownSocket(false);
	connectResult(2);
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

void KCPSocket::uv_on_udp_send(uv_udp_send_t *req, int32_t status)
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

int32_t KCPSocket::udp_output(const char *buf, int32_t len, ikcpcb *kcp, void *user)
{
	KCPSocket* socket = (KCPSocket*)user;
	socket->m_last_kcp_packet_send_time = socket->m_last_update_time;
	socket->udpSend(buf, len);
	return 0;
}

NS_NET_UV_END