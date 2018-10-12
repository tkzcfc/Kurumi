#pragma once


// 日志等级
#define NET_UV_L_HEART	 (0)
#define NET_UV_L_INFO	 (1)
#define NET_UV_L_WARNING (2)
#define NET_UV_L_ERROR	 (3)
#define NET_UV_L_FATAL	 (4)


#if _DEBUG 

// 开启调试模式
#define OPEN_NET_UV_DEBUG 1
// 开启内存检测
#define OPEN_NET_MEM_CHECK 1
// log输出最低等级
#define NET_UV_L_MIN_LEVEL NET_UV_L_INFO

#else

// 开启调试模式
#define OPEN_NET_UV_DEBUG 0
// 开启内存检测
#define OPEN_NET_MEM_CHECK 0
// log输出最低等级
#define NET_UV_L_MIN_LEVEL NET_UV_L_ERROR

#endif


