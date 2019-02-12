#pragma once


#include "Macros.h"
#include "Config.h"
#include "md5.h"
#include <string>
#include <map>
#include <list>
#include <queue>
#include <functional>
#include <assert.h>
#include "uv.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>


NS_NET_UV_BEGIN

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 调试相关
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if OPEN_NET_MEM_CHECK == 1

#define fc_malloc(len) fc_malloc_s(len, __FILE__, __LINE__)

void* fc_malloc_s(uint32_t len, const char* file, int32_t line);
void fc_free(void* p);

//打印内存信息
void printMemInfo();

#define NET_UV_LOG(level, format, ...) net_uvLog(level, format, ##__VA_ARGS__)

#else

#define fc_malloc malloc

#define fc_free free

#define printMemInfo() ((void) 0) 

#define NET_UV_LOG(level, format, ...) ((void) 0) 

#endif // !OPEN_NET_UV_DEBUG

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 日志输出
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define CHECK_UV_ERROR(r) if(r) { return false; }

#if OPEN_NET_UV_DEBUG == 1
#define CHECK_UV_ASSERT(r) if(r != 0) { auto str = net_getUVError(r); NET_UV_LOG(NET_UV_L_ERROR, str.c_str()); assert(0); }
#else
#define CHECK_UV_ASSERT(r) assert(0);
#endif

//日志输出
void net_uvLog(int32_t level, const char* format, ...);

//设置日志输出函数
void setNetUVLogPrintFunc(void(*func)(int32_t, const char*));

NS_NET_UV_END