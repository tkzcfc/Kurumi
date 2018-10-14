#pragma once

#include "TCPCommon.h"

NS_NET_UV_BEGIN

//加密
char* tcp_uv_encode(const char* data, unsigned int len, unsigned int &outLen);
//解密
char* tcp_uv_decode(const char* data, unsigned int len, unsigned int &outLen);
// 打包数据
uv_buf_t* tcp_packageData(char* data, unsigned int len, int* bufCount);
// 打包心跳消息
char* tcp_packageHeartMsgData(NET_HEART_TYPE msg, unsigned int* outBufSize);

NS_NET_UV_END