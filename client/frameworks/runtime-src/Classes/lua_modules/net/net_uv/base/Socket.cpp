#include "Socket.h"

NS_NET_UV_BEGIN

Socket::Socket()
	: m_port(0)
	, m_isIPV6(false)
	, m_loop(nullptr)
	, m_connectCall(nullptr)
	, m_closeCall(nullptr)
	, m_userdata(nullptr)
	, m_recvCall(nullptr)
{
	m_uvReadBuf.base = 0;
	m_uvReadBuf.len = 0;
}

Socket::~Socket()
{
	if (m_uvReadBuf.base != NULL)
	{
		fc_free(m_uvReadBuf.base);
		m_uvReadBuf.base = NULL;
	}
}

void Socket::uv_on_alloc_buffer(uv_handle_t* handle, size_t  size, uv_buf_t* buf)
{
	Socket* s = (Socket*)handle->data;
	if (s->m_uvReadBuf.len != size)
	{
		if (s->m_uvReadBuf.base != NULL)
		{
			fc_free(s->m_uvReadBuf.base);
		}
		s->m_uvReadBuf.base = (char*)fc_malloc(size);
		s->m_uvReadBuf.len = size;
	}
	buf->base = s->m_uvReadBuf.base;
	buf->len = size;
}

NS_NET_UV_END