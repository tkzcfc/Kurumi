#pragma once

#include <stdint.h>


//////////////////////////////////////////////////////////////////////////////
// 类型定义
typedef uint32_t G_BIT_TYPE;

//////////////////////////////////////////////////////////////////////////////
//! 消息定义
#pragma pack(4)

// 基础消息
struct GOPMsg_Base
{
	uint32_t logicFrame;
	// 操作对象
	int32_t uuid;
	// cmd
	G_BIT_TYPE cmd;

	int32_t msgSize;
};

// 按键消息
struct GOPMsg_Key : GOPMsg_Base
{
	G_BIT_TYPE key;
};

#pragma pack()
