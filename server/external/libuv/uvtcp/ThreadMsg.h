#pragma once

#include "TCPCommon.h"

//消息类型
enum ThreadMsgType
{
	CONNECT_FAIL,	//连接失败
	CONNECT_ING,	//正在连接
	CONNECT,		//连接成功
	CONNECT_TIMEOUT,//连接超时
	DIS_CONNECT,	//断开连接
	EXIT_LOOP,		//退出loop
	RECV_DATA		//收到消息
};


struct ThreadMsg_S
{
public:
	ThreadMsgType msgType;
	void* pSocket;//tcpsocket指针
	void* data;
	int dataLen;
};

struct ThreadMsg_C
{
public:
	ThreadMsgType msgType;
	unsigned int key;
	void* data;
	int dataLen;
};

