#include "TCPSocket.h"
#include "TCPUtils.h"

NS_NET_UV_BEGIN

#define TC_SOCKET_TIMER_DELAY (100U)

////////////////////////////////////////////////////////////////////////////////////////////

TCPSocket::TCPSocket(uv_loop_t* loop, uv_tcp_t* tcp)
	: m_newConnectionCall(nullptr)
	, m_tcp(NULL)
{
	m_loop = loop;
	m_tcp = tcp;
}

TCPSocket::~TCPSocket()
{
	if (m_tcp)
	{
		net_closeHandle((uv_handle_t*)m_tcp, net_closehandle_defaultcallback);
		m_tcp = NULL;
	}
}

bool TCPSocket::bind(const char* ip, unsigned int port)
{
	this->setIp(ip);
	this->setPort(port);

	struct sockaddr_in bind_addr;
	int r = uv_ip4_addr(ip, port, &bind_addr);
	if (r != 0)
	{
		return false;
	}

	if (m_tcp == NULL)
	{
		m_tcp = (uv_tcp_t*)fc_malloc(sizeof(uv_tcp_t));
		int r = uv_tcp_init(m_loop, m_tcp);
		CHECK_UV_ASSERT(r);

		m_tcp->data = this;
	}

	r = uv_tcp_bind(m_tcp, (const struct sockaddr*) &bind_addr, 0);
	return (r == 0);
}

bool TCPSocket::bind6(const char* ip, unsigned int port)
{
	this->setIp(ip);
	this->setPort(port);

	struct sockaddr_in6 bind_addr;
	int r = uv_ip6_addr(ip, port, &bind_addr);
	if (r != 0)
	{
		return false;
	}

	if (m_tcp == NULL)
	{
		m_tcp = (uv_tcp_t*)fc_malloc(sizeof(uv_tcp_t));
		int r = uv_tcp_init(m_loop, m_tcp);
		CHECK_UV_ASSERT(r);

		m_tcp->data = this;
	}

	r = uv_tcp_bind(m_tcp, (const struct sockaddr*) &bind_addr, 0);
	return (r == 0);
}

bool TCPSocket::listen()
{
	int r = uv_listen((uv_stream_t *)m_tcp, TCP_MAX_CONNECT, server_on_after_new_connection);
	return (r == 0);
}

bool TCPSocket::connect(const char* ip, unsigned int port)
{
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

		auto tcp = m_tcp;
		if (tcp == NULL)
		{
			tcp = (uv_tcp_t*)fc_malloc(sizeof(uv_tcp_t));
			int r = uv_tcp_init(m_loop, tcp);
			CHECK_UV_ASSERT(r);

			tcp->data = this;
		}

		addr = addr4 ? (struct sockaddr*)addr4 : (struct sockaddr*)addr6;

		uv_connect_t* connectReq = (uv_connect_t*)fc_malloc(sizeof(uv_connect_t));
		connectReq->data = this;

		int r = uv_tcp_connect(connectReq, tcp, addr, uv_on_after_connect);
		if (r)
		{
			return false;
		}
		setTcp(tcp);
		net_adjustBuffSize((uv_handle_t*)tcp, TCP_UV_SOCKET_RECV_BUF_LEN, TCP_UV_SOCKET_SEND_BUF_LEN);
		return true;
	}
	NET_UV_LOG(NET_UV_L_ERROR, "[%s:%d]地址信息获取失败", ip, port);
	return false;
}

bool TCPSocket::send(char* data, int len)
{
	if (m_tcp == NULL)
	{
		fc_free(data);
		return false;
	}

	uv_buf_t* buf = (uv_buf_t*)fc_malloc(sizeof(uv_buf_t));
	buf->base = (char*)data;
	buf->len = len;
	
	uv_write_t *req = (uv_write_t*)fc_malloc(sizeof(uv_write_t));
	req->data = buf;

	int r = uv_write(req, (uv_stream_t*)m_tcp, buf, 1, uv_on_after_write);
	return (r == 0);
}

TCPSocket* TCPSocket::accept(uv_stream_t* server, int status)
{
	if (status != 0)
	{
		return NULL;
	}
	uv_tcp_t *client = (uv_tcp_t*)fc_malloc(sizeof(uv_tcp_t));
	int r = uv_tcp_init(m_loop, client);
	CHECK_UV_ASSERT(r);

	uv_stream_t *handle = (uv_stream_t*)client;

	r = uv_accept(server, handle);
	CHECK_UV_ASSERT(r);
	if (r != 0)
	{
		fc_free(client); 
		return NULL;
	}

	//有的机子调用uv_tcp_getpeername报错
	//sockaddr_in client_addr;改为 sockaddr_in client_addr[2];
	//https://blog.csdn.net/readyisme/article/details/28249883
	//http://msdn.microsoft.com/en-us/library/ms737524(VS.85).aspx
	//
	//The buffer size for the local and remote address must be 16 bytes more than the size of the sockaddr structure for 
	//the transport protocol in use because the addresses are written in an internal format. For example, the size of a 
	//sockaddr_in (the address structure for TCP/IP) is 16 bytes. Therefore, a buffer size of at least 32 bytes must be 
	//specified for the local and remote addresses.

	int client_addr_length = sizeof(sockaddr_in6) * 2;
	struct sockaddr* client_addr = (struct sockaddr*)fc_malloc(client_addr_length);
	memset(client_addr, 0, client_addr_length);
	
	r = uv_tcp_getpeername((const uv_tcp_t*)handle, client_addr, &client_addr_length);
	CHECK_UV_ASSERT(r);
	if (r != 0)
	{
		fc_free(client);
		return NULL;
	}

	std::string strip;
	unsigned int port;
	if (client_addr->sa_family == AF_INET6)
	{
		struct sockaddr_in6* addr_in = (struct sockaddr_in6*) client_addr;

		char szIp[NET_UV_INET6_ADDRSTRLEN + 1] = { 0 };
		int r = uv_ip6_name(addr_in, szIp, NET_UV_INET6_ADDRSTRLEN);
		if (r != 0)
		{
			NET_UV_LOG(NET_UV_L_ERROR, "tcp服务器接受连接失败,地址解析失败");
			fc_free(client);
			return NULL;
		}

		strip = szIp;
		port = ntohs(addr_in->sin6_port);
	}
	else
	{
		struct sockaddr_in* addr_in = (struct sockaddr_in*) client_addr;

		char szIp[NET_UV_INET_ADDRSTRLEN + 1] = { 0 };
		int r = uv_ip4_name(addr_in, szIp, NET_UV_INET_ADDRSTRLEN);
		if (r != 0)
		{
			NET_UV_LOG(NET_UV_L_ERROR, "tcp服务器接受连接失败,地址解析失败");
			fc_free(client);
			return NULL;
		}

		strip = szIp;
		port = ntohs(addr_in->sin_port);
	}

	net_adjustBuffSize((uv_handle_t*)client, TCP_UV_SOCKET_RECV_BUF_LEN, TCP_UV_SOCKET_SEND_BUF_LEN);

	TCPSocket* newSocket = (TCPSocket*)fc_malloc(sizeof(TCPSocket));
	new (newSocket) TCPSocket(m_loop, client);
	client->data = newSocket;

	newSocket->setIp(strip);
	newSocket->setPort(port);

	r = uv_read_start(handle, uv_on_alloc_buffer, uv_on_after_read);
	if (r != 0)
	{
		newSocket->~TCPSocket();
		fc_free(newSocket);
		return NULL;
	}

	return newSocket;
}

void TCPSocket::disconnect()
{
	shutdownSocket();
}

void TCPSocket::shutdownSocket()
{
	if (m_tcp == NULL)
	{
		return;
	}
	net_closeHandle((uv_handle_t*)m_tcp, uv_on_close_socket);
	m_tcp = NULL;
}

void TCPSocket::uv_on_close_socket(uv_handle_t* socket)
{
	TCPSocket* s = (TCPSocket*)(socket->data);
	if (s->m_closeCall != nullptr)
	{
		s->m_closeCall(s);
	}
	fc_free(socket);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TCPSocket::uv_on_after_connect(uv_connect_t* handle, int status)
{
	TCPSocket* s = (TCPSocket*)handle->data;
	
	if (status == 0)
	{
		int r = uv_read_start(handle->handle, uv_on_alloc_buffer, uv_on_after_read);
		if (r == 0)
		{
			s->m_connectCall(s, 1);
		}
		else
		{
			s->m_connectCall(s, 0);
		}
	}
	else
	{
		//NET_UV_LOG(NET_UV_L_ERROR, "tcp connect error %s", uv_strerror(status));
		if (status == ETIMEDOUT)
		{
			s->m_connectCall(s, 2);
		}
		else
		{
			s->m_connectCall(s, 0);
		}
	}
	fc_free(handle);
}

void TCPSocket::server_on_after_new_connection(uv_stream_t *server, int status) 
{
	if (status != 0)
	{
		//NET_UV_LOG(NET_UV_L_ERROR, "tcp new connection error %s", uv_strerror(status));
		return;
	}
	TCPSocket* s = (TCPSocket*)server->data;
	s->m_newConnectionCall(server, status);
}

void TCPSocket::uv_on_after_read(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf) 
{
	TCPSocket* s = (TCPSocket*)handle->data;
	if (nread <= 0) 
	{
		s->disconnect();
		return;
	}
	s->m_recvCall(buf->base, nread);
}

void TCPSocket::uv_on_after_write(uv_write_t* req, int status)
{
	if (status != 0)
	{
		//NET_UV_LOG(NET_UV_L_ERROR, "tcp write error %s", uv_strerror(status));
	}
	uv_buf_t* buf = (uv_buf_t*)req->data;
	fc_free(buf->base);
	fc_free(buf);
	fc_free(req);
}

NS_NET_UV_END