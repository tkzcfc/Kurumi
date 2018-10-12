#pragma once

#include "KCPCommon.h"
#include <time.h>
#include "ikcp.h"

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#include <windows.h>
#elif !defined(__unix)
#define __unix
#endif

#ifdef __unix
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#endif

NS_NET_UV_BEGIN

std::string kcp_making_connect_packet(void);
bool kcp_is_connect_packet(const char* data, size_t len);

std::string kcp_making_send_back_conv_packet(uint32_t conv);
bool kcp_is_send_back_conv_packet(const char* data, size_t len);
uint32_t kcp_grab_conv_from_send_back_conv_packet(const char* data, size_t len);


std::string kcp_making_disconnect_packet(uint32_t conv);
bool kcp_is_disconnect_packet(const char* data, size_t len);
uint32_t kcp_grab_conv_from_disconnect_packet(const char* data, size_t len);

std::string kcp_making_heart_packet();
bool kcp_is_heart_packet(const char* data, size_t len);

std::string kcp_making_heart_back_packet();
bool kcp_is_heart_back_packet(const char* data, size_t len);

//加密
NET_UV_EXTERN char* kcp_uv_encode(const char* data, unsigned int len, unsigned int &outLen);
//解密
NET_UV_EXTERN char* kcp_uv_decode(const char* data, unsigned int len, unsigned int &outLen);
// 打包数据
NET_UV_EXTERN uv_buf_t* kcp_packageData(char* data, unsigned int len, int* bufCount);
// 打包心跳消息
NET_UV_EXTERN char* kcp_packageHeartMsgData(NET_HEART_TYPE msg, unsigned int* outBufSize);


/* get system time */
static inline void itimeofday(long *sec, long *usec)
{
#if defined(__unix)
	struct timeval time;
	gettimeofday(&time, NULL);
	if (sec) *sec = time.tv_sec;
	if (usec) *usec = time.tv_usec;
#else
	static long mode = 0, addsec = 0;
	BOOL retval;
	static IINT64 freq = 1;
	IINT64 qpc;
	if (mode == 0) {
		retval = QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
		freq = (freq == 0) ? 1 : freq;
		retval = QueryPerformanceCounter((LARGE_INTEGER*)&qpc);
		addsec = (long)time(NULL);
		addsec = addsec - (long)((qpc / freq) & 0x7fffffff);
		mode = 1;
	}
	retval = QueryPerformanceCounter((LARGE_INTEGER*)&qpc);
	retval = retval * 2;
	if (sec) *sec = (long)(qpc / freq) + addsec;
	if (usec) *usec = (long)((qpc % freq) * 1000000 / freq);
#endif
}

/* get clock in millisecond 64 */
static inline IINT64 iclock64(void)
{
	long s, u;
	IINT64 value;
	itimeofday(&s, &u);
	value = ((IINT64)s) * 1000 + (u / 1000);
	return value;
}

static inline IUINT32 iclock()
{
	return (IUINT32)(iclock64() & 0xfffffffful);
}

NS_NET_UV_END

