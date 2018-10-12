#pragma once

#include "../base/Macros.h"

NS_NET_UV_BEGIN

typedef unsigned int NET_HEART_TYPE;

enum NET_MSG_TYPE : NET_HEART_TYPE
{
	MT_MIN = 0,
	MT_DEFAULT,		// 默认消息
	MT_HEARTBEAT,	// 心跳消息
	MT_MAX
};

#define NET_HEARTBEAT_MSG_C2S	  (0)		// 客户端->服务器心跳探测消息
#define NET_HEARTBEAT_MSG_S2C	  (1)		// 服务器->客户端心跳探测消息
#define NET_HEARTBEAT_RET_MSG_C2S (2)		// 客户端->服务器心跳回复消息
#define NET_HEARTBEAT_RET_MSG_S2C (3)		// 服务器->客户端心跳回复消息
#define NET_HEARTBEAT_MSG_SIZE	  sizeof(NET_HEART_TYPE)// 心跳消息大小

NS_NET_UV_END
