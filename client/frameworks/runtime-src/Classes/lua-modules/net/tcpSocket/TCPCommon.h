#pragma once

#include "uv.h"
#include <string>
#include <assert.h>
#include <map>


#if defined (WIN32) || defined(_WIN32)

#include <windows.h>
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib,"Psapi.lib")
#pragma comment(lib, "Userenv.lib")

//睡眠ms毫秒
#define ThreadSleep(ms) Sleep(ms);

#elif defined __linux__

#include <unistd.h>
//睡眠ms毫秒
#define ThreadSleep(ms) usleep((ms) * 1000)

#endif

//套接字最小接收缓存大小
#define TCP_UV_SOCKET_RECV_BUF_LEN (1024 * 8)
//套接字最小发送缓存大小
#define TCP_UV_SOCKET_SEND_BUF_LEN (1024 * 8)

//大消息最大发送大小
//如果消息头的长度字段大于该值
//则直接认定为该客户端发送的消息为非法消息
//(10MB)
#define TCP_BIG_MSG_MAX_LEN (1024 * 1024 * 10)

//单次消息发送最大字节
//若超过该长度，则进行分片发送
//(4K)
#define TCP_WRITE_MAX_LEN (1024 * 4)

//IP地址长度
#define TCP_IP_ADDR_LEN (32)

//最大连接数
#define TCP_MAX_CONNECT (0xFFFF)


#define CHECK_UV_ERROR(r) if(r) { getUVError(r); return false; }

#define CHECK_UV_ASSERT(r) if(r) { auto str = getUVError(r); UV_LOG("uv error : %s\n", str.c_str()); assert(0); }


std::string getUVError(int errcode);


//开启md5校验
#define OPEN_TCP_UV_MD5_CHECK 1
//校验密码
#define TCP_UV_ENCODE_KEY "123456789"


//开启调试模式
#define OPEN_TCP_UV_DEBUG 1


#if OPEN_TCP_UV_DEBUG == 1

#define fc_malloc(len) fc_malloc_s(len, __FILE__, __LINE__)

void* fc_malloc_s(unsigned int len, const char* file, int line);
void fc_free(void* p);

//打印内存信息
void printMemInfo();
//日志输出
void tcp_uvLog(const char* format, ...);

#define UV_LOG(format, ...) tcp_uvLog(format, ##__VA_ARGS__)

#else

#define fc_malloc malloc

#define fc_free free

#define printMemInfo() ((void) 0) 

#define UV_LOG(format, ...) ((void) 0) 

#endif // !OPEN_TCP_UV_DEBUG


struct TCPMsgHead
{
	unsigned int len;//消息长度，不包括本结构体
};


//设置日志输出函数
extern void setUVLogPrintFunc(void(*func)(const char*));

