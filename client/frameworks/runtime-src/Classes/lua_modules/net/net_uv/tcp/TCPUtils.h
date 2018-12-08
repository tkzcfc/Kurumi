#pragma once

#include "TCPCommon.h"

NS_NET_UV_BEGIN

//加密
char* tcp_uv_encode(const char* data, uint32_t len, uint32_t &outLen);
//解密
char* tcp_uv_decode(const char* data, uint32_t len, uint32_t &outLen);
// 打包数据
uv_buf_t* tcp_packageData(char* data, uint32_t len, int32_t* bufCount);
// 打包心跳消息
char* tcp_packageHeartMsgData(NET_HEART_TYPE msg, uint32_t* outBufSize);

NS_NET_UV_END