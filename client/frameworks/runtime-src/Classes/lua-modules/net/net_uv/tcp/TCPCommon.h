#pragma once

#include "../base/Socket.h"
#include "../base/Server.h"
#include "../base/Client.h"
#include "../base/Runnable.h"
#include "../base/uv_func.h"
#include "../base/Mutex.h"
#include "../base/Session.h"
#include "../base/SessionManager.h"
#include "../common/NetUVThreadMsg.h"
#include "../common/NetHeart.h"
#include "TCPConfig.h"

NS_NET_UV_BEGIN


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 消息包头
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TCPMsgHead
{
	unsigned int len;// 消息长度，不包括本结构体
#if TCP_OPEN_UV_THREAD_HEARTBEAT == 1
	NET_HEART_TYPE tag;// 消息标记
#endif
};


NS_NET_UV_END