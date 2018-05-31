#include "TCPSocket.h"
#include "TCPUtils.h"

#define TC_SOCKET_TIMER_DELAY (500U)

//调整socket接收发送缓存大小
void adjustBuffSize(uv_handle_t* handle)
{
	int len = 0;
	int r = uv_recv_buffer_size(handle, &len);
	CHECK_UV_ASSERT(r);

	if (len < TCP_UV_SOCKET_RECV_BUF_LEN)
	{
		len = TCP_UV_SOCKET_RECV_BUF_LEN;
		r = uv_recv_buffer_size(handle, &len);
		CHECK_UV_ASSERT(r);
	}

	len = 0;
	r = uv_send_buffer_size(handle, &len);
	CHECK_UV_ASSERT(r);

	if (len < TCP_UV_SOCKET_SEND_BUF_LEN)
	{
		len = TCP_UV_SOCKET_SEND_BUF_LEN;
		r = uv_send_buffer_size(handle, &len);
		CHECK_UV_ASSERT(r);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////

TCPSocket::TCPSocket(uv_loop_t* loop, uv_tcp_t* tcp)
{
	m_loop = loop;
	m_tcp = tcp;
	m_port = 80;
	m_timeout = 10000;/// 10S
	m_curTime = 0;
	m_initConnectInfo = false;
	
	uv_mutex_init(&m_writeMutex);
	uv_mutex_init(&m_readMutex);
	uv_mutex_init(&m_basedataMutex);

	m_recvBuffer = (TCPBuffer*)fc_malloc(sizeof(TCPBuffer));
	new (m_recvBuffer)TCPBuffer(TCP_WRITE_MAX_LEN * 0.5);

	m_writeAsync = (uv_async_t*)fc_malloc(sizeof(uv_async_t));
	m_connectAsync = (uv_async_t*)fc_malloc(sizeof(uv_async_t));
	m_listenAsync = (uv_async_t*)fc_malloc(sizeof(uv_async_t));
	m_closeAsync = (uv_async_t*)fc_malloc(sizeof(uv_async_t));

	uv_async_init(loop, m_writeAsync, uv_write_async_callback);
	uv_async_init(loop, m_connectAsync, uv_connect_async_callback);
	uv_async_init(loop, m_listenAsync, uv_listen_async_callback);
	uv_async_init(loop, m_closeAsync, uv_close_async_callback);

	uv_timer_init(loop, &m_connectTimer);
	m_connectTimer.data = this;

	m_writeAsync->data = this;
	m_connectAsync->data = this;
	m_listenAsync->data = this;
	m_closeAsync->data = this;

	m_call.call = NULL;
	m_call.userdata = NULL;

	m_state = tcpSocketState::tcps_dis_connect;
}

TCPSocket::~TCPSocket()
{
	clearReadCache();
	clearWriteCache();

	m_writeAsync->data = NULL;
	m_connectAsync->data = NULL;
	m_listenAsync->data = NULL;
	m_closeAsync->data = NULL;

	closeHandle((uv_handle_t*)m_writeAsync, uv_closehandle_defaultcallback);
	closeHandle((uv_handle_t*)m_connectAsync, uv_closehandle_defaultcallback);
	closeHandle((uv_handle_t*)m_listenAsync, uv_closehandle_defaultcallback);
	closeHandle((uv_handle_t*)m_closeAsync, uv_closehandle_defaultcallback);

	stopConnectTimer();

	uv_mutex_lock(&m_basedataMutex);
	if (m_tcp)
	{
		m_tcp->data = NULL;
		closeHandle((uv_handle_t*)m_tcp, uv_on_close_socket);
		m_tcp = NULL;
	}
	uv_mutex_unlock(&m_basedataMutex);

	uv_mutex_destroy(&m_writeMutex);
	uv_mutex_destroy(&m_readMutex);
	uv_mutex_destroy(&m_basedataMutex);

	m_recvBuffer->~TCPBuffer();
	fc_free(m_recvBuffer);
}

void TCPSocket::listen(const char* ip, unsigned int port)
{
	this->setIp(ip);
	this->setPort(port);

	int r = uv_async_send(m_listenAsync);

	CHECK_UV_ASSERT(r);

#if OPEN_TCP_UV_DEBUG == 1
	UV_LOG("listen [%p][%s]:[%d]...", this, ip, port);
#endif
}

void TCPSocket::connect(const char* ip, unsigned int port, unsigned int timeout)
{
	if (getState() != tcpSocketState::tcps_dis_connect)
		return;

	m_initConnectInfo = true;

	this->setIp(ip);
	this->setPort(port);
	m_timeout = timeout;

	int r = uv_async_send(m_connectAsync);

	CHECK_UV_ASSERT(r);

#if OPEN_TCP_UV_DEBUG == 1
	UV_LOG("connect [%p][%s]:[%d]...", this, ip, port);
#endif
}

bool TCPSocket::reconnect()
{
	if (!m_initConnectInfo)
		return false;

	int r = uv_async_send(m_connectAsync);

	CHECK_UV_ASSERT(r);

#if OPEN_TCP_UV_DEBUG == 1
	UV_LOG("reconnect [%p][%s]:[%d]...", this, m_ip.c_str(), m_port);
#endif
	return true;
}

bool TCPSocket::isConnect()
{
	return (getState() == tcpSocketState::tcps_connect);
}

void TCPSocket::disconnect()
{
	if (isConnect())
	{
		uv_async_send(m_closeAsync);
	}
}

void TCPSocket::setCallback(socket_call call, void* userdata)
{
	uv_mutex_lock(&m_basedataMutex);

	m_call.call = call;
	m_call.userdata = userdata;

	uv_mutex_unlock(&m_basedataMutex);
}

void* TCPSocket::getCallbackUserdata()
{
	uv_mutex_lock(&m_basedataMutex);
	void* r = m_call.userdata;
	uv_mutex_unlock(&m_basedataMutex);

	return r;
}

void TCPSocket::invokeCallback(socket_call_type type, void* data)
{
	switch (type)
	{
	case connect_suc:
	{
		this->setState(tcpSocketState::tcps_connect);
		this->clearReadCache();
		this->clearWriteCache();
		this->resetReadBuffer();

#if OPEN_TCP_UV_DEBUG == 1
		UV_LOG("connect suc [%p][%s]:[%d]", this, m_ip.c_str(), m_port);
#endif
	}
		break;
	case connect_fail:
		this->setState(tcpSocketState::tcps_dis_connect);
		this->resetReadBuffer();

#if OPEN_TCP_UV_DEBUG == 1
		UV_LOG("connect fail [%p][%s]:[%d]", this, m_ip.c_str(), m_port);
#endif
		break;
	case connect_ing:
		this->setState(tcpSocketState::tcps_connecting);

#if OPEN_TCP_UV_DEBUG == 1
		UV_LOG("connecting [%p][%s]:[%d]", this, m_ip.c_str(), m_port);
#endif
		break;
	case connect_timeout:
		this->setState(tcpSocketState::tcps_dis_connect);

#if OPEN_TCP_UV_DEBUG == 1
		UV_LOG("connect timeout [%p][%s]:[%d]", this, m_ip.c_str(), m_port);
#endif
		break;
	case connect_close:
		this->setTcp(NULL);
		this->setState(tcpSocketState::tcps_dis_connect);
		this->clearReadCache();
		this->clearWriteCache();
		this->resetReadBuffer();

#if OPEN_TCP_UV_DEBUG == 1
		UV_LOG("connect close [%p][%s]:[%d]", this, m_ip.c_str(), m_port);
#endif
		break;
	default:
		break;
	}

	uv_mutex_lock(&m_basedataMutex);
	auto call = m_call.call;
	auto userdata = m_call.userdata;
	uv_mutex_unlock(&m_basedataMutex);

	if (call)
	{
		call(type, this, data, userdata);
	}
}

bool TCPSocket::getAllRecvData(std::list<blockdata>* list)
{
	if (uv_mutex_trylock(&m_readMutex) != 0)
	{
		return false;
	}

	if (m_readCache.empty())
	{
		uv_mutex_unlock(&m_readMutex);
		return false;
	}

	auto it = m_readCache.begin();
	for (; it != m_readCache.end(); ++it)
	{
		list->push_back(*it);
	}

	m_readCache.clear();
	uv_mutex_unlock(&m_readMutex);
	return true;
}

bool TCPSocket::getRecvData(blockdata* data)
{
	if (uv_mutex_trylock(&m_readMutex) != 0)
	{
		return false;
	}

	if (m_readCache.empty())
	{
		uv_mutex_unlock(&m_readMutex);
		return false;
	}

	*data = m_readCache.front();
	uv_mutex_unlock(&m_readMutex);

	return true;
}

void TCPSocket::shutdownSocket()
{
	setState(tcpSocketState::tcps_dis_connect);

	uv_mutex_lock(&m_basedataMutex);

	if (m_tcp == NULL)
	{
		uv_mutex_unlock(&m_basedataMutex);
		return;
	}

#if OPEN_TCP_UV_DEBUG == 1
	UV_LOG("shutdown [%p][%s]:[%d]...", this, m_ip.c_str(), m_port);
#endif

	closeHandle((uv_handle_t*)m_tcp, uv_on_close_socket);

	m_tcp = NULL;

	uv_mutex_unlock(&m_basedataMutex);
}

bool TCPSocket::send(const char* data, unsigned int len)
{
	if (data == NULL || len <= 0)
	{
#if OPEN_TCP_UV_DEBUG == 1
		UV_LOG("warning: The msg is nil");
#endif
		//assert(0);		
		return false;
	}

	if (len > TCP_BIG_MSG_MAX_LEN)
	{
#if defined (WIN32) || defined(_WIN32)
		MessageBox(NULL, TEXT("The msg is too big!!!"), TEXT("ERROR"), MB_OK);
#else
		printf("The msg is too big!!!");
#endif
		assert(0);
		return false;
	}

	if (getState() != tcpSocketState::tcps_connect)
		return false;

	const unsigned int headlen = sizeof(TCPMsgHead);

#if OPEN_TCP_UV_MD5_CHECK == 1

	unsigned int encodelen = 0;
	char* encodedata = tcp_uv_encode(data, len, encodelen);
	if (encodedata == NULL)
	{
		assert(0);
		return false;
	}

	char* p = (char*)fc_malloc(headlen + encodelen);

	TCPMsgHead* h = (TCPMsgHead*)p;
	h->len = encodelen;
	memcpy(p + headlen, encodedata, encodelen);

	fc_free(encodedata);

	blockdata block;
	block.data = p;
	block.len = headlen + encodelen;
#else
	char* p = (char*)fc_malloc(headlen + len);
	TCPMsgHead* h = (TCPMsgHead*)p;
	h->len = len;
	memcpy(p + headlen, data, len);

	blockdata block;
	block.data = p;
	block.len = headlen + len;
#endif

	//消息分片
	if (block.len > TCP_WRITE_MAX_LEN)
	{
		char* bigData = block.data;
		unsigned int bigLen = block.len;
		int curIndex = 0;
		blockdata framBlock;

		while (bigLen > 0)
		{
			if (bigLen < TCP_WRITE_MAX_LEN)
			{
				char* tmp = (char*)fc_malloc(bigLen);
				memcpy(tmp, bigData + curIndex, bigLen);

				framBlock.data = tmp;
				framBlock.len = bigLen;

				curIndex = curIndex + bigLen;
				bigLen = 0;
			}
			else
			{
				char* tmp = (char*)fc_malloc(TCP_WRITE_MAX_LEN);
				memcpy(tmp, bigData + curIndex, TCP_WRITE_MAX_LEN);

				framBlock.data = tmp;
				framBlock.len = TCP_WRITE_MAX_LEN;

				bigLen = bigLen - TCP_WRITE_MAX_LEN;
				curIndex = curIndex + TCP_WRITE_MAX_LEN;
			}
			this->pushWriteData(framBlock);
		}

		fc_free(bigData);
	}
	else
	{
		this->pushWriteData(block);
	}

	uv_async_send(m_writeAsync);

	return true;
}

uv_tcp_t* TCPSocket::getTcp() 
{
	uv_mutex_lock(&m_basedataMutex);
	auto r = m_tcp;
	uv_mutex_unlock(&m_basedataMutex);
	return r;
}

void TCPSocket::setTcp(uv_tcp_t* tcp)
{
	uv_mutex_lock(&m_basedataMutex);
	m_tcp = tcp;
	uv_mutex_unlock(&m_basedataMutex);
}

std::string TCPSocket::getIp()
{
	//uv_mutex_lock(&m_basedataMutex);
	auto r = m_ip;
	//uv_mutex_unlock(&m_basedataMutex);
	return r;
}

void TCPSocket::setIp(const std::string ip)
{
	//uv_mutex_lock(&m_basedataMutex);
	m_ip = ip;
	//uv_mutex_unlock(&m_basedataMutex);
}

unsigned int TCPSocket::getPort()
{
	//uv_mutex_lock(&m_basedataMutex);
	auto r = m_port; 
	//uv_mutex_unlock(&m_basedataMutex);
	return r;
}

void TCPSocket::setPort(unsigned int port)
{
	//uv_mutex_lock(&m_basedataMutex);
	m_port = port;
	//uv_mutex_unlock(&m_basedataMutex);
}

tcpSocketState TCPSocket::getState()
{
	uv_mutex_lock(&m_basedataMutex);
	auto r = m_state;
	uv_mutex_unlock(&m_basedataMutex);
	return r;
}

void TCPSocket::setState(tcpSocketState state)
{
	uv_mutex_lock(&m_basedataMutex);
	m_state = state;
	uv_mutex_unlock(&m_basedataMutex);
}

void TCPSocket::pushWriteData(const blockdata& data)
{
	uv_mutex_lock(&m_writeMutex);
	m_writeCache.push_back(data);
	uv_mutex_unlock(&m_writeMutex);
}

void TCPSocket::clearWriteCache()
{
	uv_mutex_lock(&m_writeMutex);
	for (auto & it : m_writeCache)
	{
		fc_free(it.data);
	}
	m_writeCache.clear();
	uv_mutex_unlock(&m_writeMutex);
}

void TCPSocket::pushReadData(const blockdata& data)
{
	uv_mutex_lock(&m_readMutex);
	m_readCache.push_back(data);
	uv_mutex_unlock(&m_readMutex);
}

void TCPSocket::clearReadCache()
{
	uv_mutex_lock(&m_readMutex);
	for (auto & it : m_readCache)
	{
		fc_free(it.data);
	}
	m_readCache.clear();
	uv_mutex_unlock(&m_readMutex);
}

void TCPSocket::write()
{
	if (getState() != tcpSocketState::tcps_connect)
		return;

	if (uv_mutex_trylock(&m_writeMutex) != 0)
	{
		uv_async_send(m_writeAsync);
		return;
	}

	auto size = m_writeCache.size();
	if (size <= 0)
	{
		uv_mutex_unlock(&m_writeMutex);
		return;
	}

	auto it = m_writeCache.begin();

	uv_buf_t* buf = (uv_buf_t*)fc_malloc(sizeof(uv_buf_t));
	buf->base = (char*)it->data;
	buf->len = it->len;

	m_writeCache.erase(it);

	uv_mutex_unlock(&m_writeMutex);

	uv_write_t *req = (uv_write_t*)fc_malloc(sizeof(uv_write_t));
	req->data = buf;

	int r = uv_write(req, (uv_stream_t*)getTcp(), buf, 1, uv_on_after_write);
	if (r)//if (r && r != UV__EINVAL)
	{
		shutdownSocket();
	}
	else
	{
		if (size > 1)
		{
			uv_async_send(m_writeAsync);
		}
	}
}

void TCPSocket::read(ssize_t nread, const uv_buf_t *buf)
{
	if (getState() != tcpSocketState::tcps_connect)
	{
		return;
	}

	m_recvBuffer->add(buf->base, nread);

	const unsigned int headlen = sizeof(TCPMsgHead);

	while (m_recvBuffer->getDataLength() >= headlen)
	{
		TCPMsgHead* h = (TCPMsgHead*)m_recvBuffer->getHeadBlockData();

		//不合法客户端
		if (h->len > TCP_BIG_MSG_MAX_LEN)
		{
			this->resetReadBuffer();
			this->disconnect();
			UV_LOG("data is wrongful (1)!!!!");
			break;
		}

		int subv = m_recvBuffer->getDataLength() - (h->len + headlen);
		
		//消息接收完成
		if (subv >= 0)
		{
			char* pMsg = (char*)fc_malloc(m_recvBuffer->getDataLength());
			m_recvBuffer->get(pMsg);

			char* src = pMsg + headlen;

#if OPEN_TCP_UV_MD5_CHECK == 1

			blockdata block;
			block.data = tcp_uv_decode(src, h->len, block.len);

			if (block.data != NULL && block.len > 0)
			{
				this->pushReadData(block);
			}
			else//数据不合法
			{
				UV_LOG("data is wrongful (2)!!!!");
			}
#else
			char* pdata = (char*)fc_malloc(h->len + 1);
			memcpy(pdata, src, h->len);
			pdata[h->len] = '\0';

			blockdata block;
			block.data = pdata;
			block.len = h->len;

			this->pushReadData(block);
#endif
			m_recvBuffer->clear();

			if (subv > 0)
			{
				m_recvBuffer->add(buf->base + (nread - subv), subv);
			}
			fc_free(pMsg);
		}
		else
		{
			break;
		}
	}
}

void TCPSocket::resetReadBuffer()
{
	m_recvBuffer->clear();
}

bool TCPSocket::setNoDelay(bool enable)
{
	if (m_tcp == NULL)
	{
		return false;
	}
	int r = uv_tcp_nodelay(m_tcp, enable);
	return (r == 0);
}

bool TCPSocket::setKeepAlive(int enable, unsigned int delay)
{
	if (m_tcp == NULL)
	{
		return false;
	}
	int r = uv_tcp_keepalive(m_tcp, enable, delay);
	return (r == 0);
}

void TCPSocket::stopConnectTimer()
{
	m_curTime = 0;
	uv_timer_stop(&m_connectTimer);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TCPSocket::closeHandle(uv_handle_t* handle, uv_close_cb closecb)
{
	if (handle && !uv_is_closing(handle))
	{
		uv_close(handle, closecb);
	}
}

void TCPSocket::uv_close_async_callback(uv_async_t* handle)
{
	TCPSocket* s = (TCPSocket*)handle->data;
	s->shutdownSocket();
}

void TCPSocket::uv_write_async_callback(uv_async_t* handle)
{
	TCPSocket* s = (TCPSocket*)handle->data;
	s->write();
}

void TCPSocket::uv_connect_async_callback(uv_async_t* handle)
{
	TCPSocket* s = (TCPSocket*)handle->data;

	if (s->getState() != tcpSocketState::tcps_dis_connect)
		return;

	s->stopConnectTimer();

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

	int ret = getaddrinfo(s->getIp().c_str(), NULL, &hints, &ainfo);

	if (ret == 0)
	{
		for (rp = ainfo; rp; rp = rp->ai_next)
		{
			if (rp->ai_family == AF_INET)
			{
				addr4 = (struct sockaddr_in*)rp->ai_addr;
				addr4->sin_port = htons(s->getPort());
				break;

			}
			else if (rp->ai_family == AF_INET6)
			{
				addr6 = (struct sockaddr_in6*)rp->ai_addr;
				addr6->sin6_port = htons(s->getPort());
				break;
			}
			else
			{
				continue;
			}
		}

		auto tcp = s->getTcp();
		if (tcp == NULL)
		{
			tcp = (uv_tcp_t*)fc_malloc(sizeof(uv_tcp_t));
			int r = uv_tcp_init(s->m_loop, tcp);
			CHECK_UV_ASSERT(r);

			tcp->data = s;
		}

		addr = addr4 ? (struct sockaddr*)addr4 : (struct sockaddr*)addr6;

		uv_connect_t* connectReq = (uv_connect_t*)fc_malloc(sizeof(uv_connect_t));
		connectReq->data = s;

		int r = uv_tcp_connect(connectReq, tcp, addr, uv_on_after_connect);
		if (r)
		{
			s->invokeCallback(socket_call_type::connect_fail, NULL);
			return;
		}

		s->setTcp(tcp);
		adjustBuffSize((uv_handle_t*)tcp);

		s->invokeCallback(socket_call_type::connect_ing, NULL);

		uv_timer_start(&s->m_connectTimer, uv_timer_run, (uint64_t)TC_SOCKET_TIMER_DELAY, (uint64_t)TC_SOCKET_TIMER_DELAY);
	}
	else
	{
#if OPEN_TCP_UV_DEBUG == 1
		static char* err = "get addr info fail!!!";
		UV_LOG("error : %s\n", err);
#endif

		s->invokeCallback(socket_call_type::connect_fail, NULL);
	}
}

void TCPSocket::uv_on_after_connect(uv_connect_t* handle, int status)
{
	TCPSocket* s = (TCPSocket*)handle->data;
	
	s->stopConnectTimer();

	if (status != 0)
	{
		s->invokeCallback(socket_call_type::connect_fail, NULL);
	}
	else
	{
		int r = uv_read_start(handle->handle, uv_alloc_buffer, uv_on_after_read);

		if (r)
		{
			s->invokeCallback(socket_call_type::connect_fail, NULL);
		}
		else
		{
			s->invokeCallback(socket_call_type::connect_suc, NULL);
		}
	}

	fc_free(handle);
}

void TCPSocket::uv_listen_async_callback(uv_async_t* handle)
{
	TCPSocket* s = (TCPSocket*)handle->data;

	auto tcp = s->getTcp();
	assert(tcp == NULL);

	tcp = (uv_tcp_t*)fc_malloc(sizeof(uv_tcp_t));
	int r = uv_tcp_init(s->m_loop, tcp);
	CHECK_UV_ASSERT(r);

	tcp->data = s;

	struct sockaddr_in bind_addr;
	r = uv_ip4_addr(s->getIp().c_str(), s->getPort(), &bind_addr);
	CHECK_UV_ASSERT(r);

	r = uv_tcp_bind(tcp, (const struct sockaddr*) &bind_addr, 0);
	CHECK_UV_ASSERT(r);

	r = uv_listen((uv_stream_t *)tcp, TCP_MAX_CONNECT, server_on_after_new_connection);
	CHECK_UV_ASSERT(r);

	adjustBuffSize((uv_handle_t*)tcp);
	s->setTcp(tcp);

	s->setState(tcpSocketState::tcps_connect);
}

void TCPSocket::server_on_after_new_connection(uv_stream_t *server, int status) 
{
	if (status != 0) //if (status == -1) 
	{
		return;
	}

	TCPSocket* s = (TCPSocket*)server->data;

	uv_tcp_t *client = (uv_tcp_t*)fc_malloc(sizeof(uv_tcp_t));
	int r = uv_tcp_init(s->m_loop, client);
	CHECK_UV_ASSERT(r);

	uv_stream_t *handle = (uv_stream_t*)client;

	r = uv_accept(server, handle);
	CHECK_UV_ASSERT(r);

	//有的机子调用uv_tcp_getpeername报错
	//sockaddr_in client_addr;改为 sockaddr_in client_addr[2];
	//https://blog.csdn.net/readyisme/article/details/28249883
	//http://msdn.microsoft.com/en-us/library/ms737524(VS.85).aspx
	//
	//The buffer size for the local and remote address must be 16 bytes more than the size of the sockaddr structure for 
	//the transport protocol in use because the addresses are written in an internal format. For example, the size of a 
	//sockaddr_in (the address structure for TCP/IP) is 16 bytes. Therefore, a buffer size of at least 32 bytes must be 
	//specified for the local and remote addresses.

	sockaddr_in client_addr[2];
	memset(&client_addr, 0, sizeof(client_addr));
	int client_addr_length = sizeof(client_addr);

	r = uv_tcp_getpeername((const uv_tcp_t*)handle, (struct sockaddr*)&client_addr, &client_addr_length);
	CHECK_UV_ASSERT(r);

	char* szIp = (char*)fc_malloc(TCP_IP_ADDR_LEN);
	memset(szIp, 0, TCP_IP_ADDR_LEN);
	r = uv_inet_ntop(AF_INET, &client_addr[0].sin_addr, szIp, TCP_IP_ADDR_LEN);
	CHECK_UV_ASSERT(r);
	
#if OPEN_TCP_UV_DEBUG == 1 
	TCPSocket* news = (TCPSocket*)fc_malloc(sizeof(TCPSocket));
	new (news) TCPSocket(s->m_loop, client);
	adjustBuffSize((uv_handle_t*)client);
#else
	TCPSocket* news = new TCPSocket(s->m_loop, client);
#endif

	news->m_ip = szIp;
	news->m_state = tcpSocketState::tcps_connect;
	client->data = news;
	s->invokeCallback(socket_call_type::connect_new, (void*)news);

#if OPEN_TCP_UV_DEBUG == 1 
	UV_LOG("accept [%p][%s]", news, szIp);
#endif

	fc_free(szIp);

	if (r == 0) 
	{
		uv_read_start(handle, uv_alloc_buffer, uv_on_after_read);
	}
	else 
	{
		closeHandle((uv_handle_t *)handle, uv_on_close_socket);
	}
}

void TCPSocket::uv_on_close_socket(uv_handle_t* socket) 
{
	TCPSocket* s = (TCPSocket*)(uv_tcp_t*)socket->data;

	if (s)
	{
		s->invokeCallback(socket_call_type::connect_close, NULL);
	}

	fc_free(socket);
}

void TCPSocket::uv_closehandle_defaultcallback(uv_handle_t* handle)
{
	fc_free(handle);
}

void TCPSocket::uv_on_after_read(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf) 
{
	if (nread == UV_EOF) 
	{
		closeHandle((uv_handle_t*)handle, uv_on_close_socket);
		fc_free(buf->base);
		return;
	}

	if (nread == 0) 
	{
		closeHandle((uv_handle_t*)handle, uv_on_close_socket);
		fc_free(buf->base);
		return;
	}

	if (nread > 0) 
	{
		TCPSocket* s = (TCPSocket*)handle->data;
		s->read(nread, buf);
	}
	else 
	{
		closeHandle((uv_handle_t *)handle, uv_on_close_socket);
	}

	fc_free(buf->base);
}


void TCPSocket::uv_alloc_buffer(uv_handle_t* handle, size_t  size, uv_buf_t* buf)
{
	buf->base = (char*)fc_malloc(size);
	buf->len = size;
}

void TCPSocket::uv_on_after_write(uv_write_t* req, int status)
{
	uv_buf_t* buf = (uv_buf_t*)req->data;
	fc_free(buf->base);
	fc_free(buf);
	fc_free(req);
}

void TCPSocket::uv_timer_run(uv_timer_t* handle)
{
	TCPSocket* s = (TCPSocket*)handle->data;

	s->m_curTime += TC_SOCKET_TIMER_DELAY;

	if (s->m_curTime >= s->m_timeout)
	{
		s->stopConnectTimer();
		s->shutdownSocket();
		s->invokeCallback(socket_call_type::connect_timeout, NULL);
	}
}
