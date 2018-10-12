#include "uv_func.h"

NS_NET_UV_BEGIN


NET_UV_EXTERN void net_alloc_buffer(uv_handle_t* handle, size_t  size, uv_buf_t* buf)
{
	buf->base = (char*)fc_malloc(size);
	buf->len = size;
}

NET_UV_EXTERN void net_closehandle_defaultcallback(uv_handle_t* handle)
{
	fc_free(handle);
}

NET_UV_EXTERN void net_closeHandle(uv_handle_t* handle, uv_close_cb closecb)
{
	if (handle && !uv_is_closing(handle))
	{
		uv_close(handle, closecb);
	}
}

// 调整socket缓冲区大小
NET_UV_EXTERN void net_adjustBuffSize(uv_handle_t* handle, int minRecvBufSize, int minSendBufSize)
{
	int len = 0;
	int r = uv_recv_buffer_size(handle, &len);
	CHECK_UV_ASSERT(r);

	if (len < minRecvBufSize)
	{
		len = minRecvBufSize;
		r = uv_recv_buffer_size(handle, &len);
		CHECK_UV_ASSERT(r);
	}

	len = 0;
	r = uv_send_buffer_size(handle, &len);
	CHECK_UV_ASSERT(r);

	if (len < minSendBufSize)
	{
		len = minSendBufSize;
		r = uv_send_buffer_size(handle, &len);
		CHECK_UV_ASSERT(r);
	}
}

// hash
NET_UV_EXTERN unsigned int net_getBufHash(const void *buf, unsigned int len)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;
	unsigned int i = 0;
	char *str = (char *)buf;
	while (i < len)
	{
		hash = hash * seed + (*str++);
		++i;
	}

	return (hash & 0x7FFFFFFF);
}

NS_NET_UV_END
