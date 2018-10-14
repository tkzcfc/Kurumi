#pragma once

#include "Common.h"

NS_NET_UV_BEGIN

void net_alloc_buffer(uv_handle_t* handle, size_t  size, uv_buf_t* buf);

void net_closehandle_defaultcallback(uv_handle_t* handle);

void net_closeHandle(uv_handle_t* handle, uv_close_cb closecb);

// 调整socket缓冲区大小
void net_adjustBuffSize(uv_handle_t* handle, int minRecvBufSize, int minSendBufSize);

//hash
unsigned int net_getBufHash(const void *buf, unsigned int len);

NS_NET_UV_END
