#pragma once


//加密
char* tcp_uv_encode(const char* data, unsigned int len, unsigned int &outLen);
//解密
char* tcp_uv_decode(const char* data, unsigned int len, unsigned int &outLen);
//hash
unsigned int GetBufHash(const void *buf, unsigned int len);