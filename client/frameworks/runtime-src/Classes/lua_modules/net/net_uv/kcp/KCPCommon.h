#pragma once

#include "../base/Common.h"
#include "../base/Socket.h"
#include "../base/Runnable.h"
#include "../base/Misc.h"
#include "../base/Session.h"
#include "../base/SessionManager.h"
#include "../base/Mutex.h"
#include "../base/Client.h"
#include "../base/Server.h"
#include "../common/NetUVThreadMsg.h"
#include "../common/NetHeart.h"
#include "KCPConfig.h"

NS_NET_UV_BEGIN

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 消息包头
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma pack(4)
struct KCPMsgHead
{
	uint32_t len;// 消息长度，不包括本结构体
#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
	NET_HEART_TYPE tag;// 消息标记
#endif
};
#pragma pack()

NS_NET_UV_END
