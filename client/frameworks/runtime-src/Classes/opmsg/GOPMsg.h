#pragma once

#include "GCommon.h"


//////////////////////////////////////////////////////////////////////////////
// 类型定义
typedef uint32_t G_BIT_TYPE;

// 位偏移基数
static const G_BIT_TYPE G_FIXED_VALUE = 0x1U;

// 最大定义个数
static const uint32_t G_BIT_MAX_COUNT = sizeof(G_BIT_TYPE) * 8 - 1;


//! 游戏操作命令定义
static const G_BIT_TYPE G_CMD_NONE		= 0x0;				  // 空值
static const G_BIT_TYPE G_CMD_KEY_DOWN	= G_FIXED_VALUE << 1; // 按键按下命令
static const G_BIT_TYPE G_CMD_KEY_UP	= G_FIXED_VALUE << 2; // 按键抬起命令


//! 游戏按键定义
static const G_BIT_TYPE G_KEY_NONE			= 0x0;				  // 空值
static const G_BIT_TYPE G_KEY_MOVE_LEFT		= G_FIXED_VALUE << 1; // 左移
static const G_BIT_TYPE G_KEY_MOVE_RIGHT	= G_FIXED_VALUE << 2; // 右移
static const G_BIT_TYPE G_KEY_MOVE_UP		= G_FIXED_VALUE << 3; // 上移
static const G_BIT_TYPE G_KEY_MOVE_DOWN		= G_FIXED_VALUE << 4; // 下移
static const G_BIT_TYPE G_KEY_JUMP			= G_FIXED_VALUE << 5; // 跳跃
static const G_BIT_TYPE G_KEY_SKILL_1		= G_FIXED_VALUE << 6; // 技能1
static const G_BIT_TYPE G_KEY_SKILL_2		= G_FIXED_VALUE << 7; // 技能2
static const G_BIT_TYPE G_KEY_SKILL_3		= G_FIXED_VALUE << 8; // 技能3
static const G_BIT_TYPE G_KEY_SKILL_4		= G_FIXED_VALUE << 9; // 技能4
static const G_BIT_TYPE G_KEY_SKILL_5		= G_FIXED_VALUE << 10; // 技能5
static const G_BIT_TYPE G_KEY_SKILL_6		= G_FIXED_VALUE << 11; // 技能6
static const G_BIT_TYPE G_KEY_SKILL_7		= G_FIXED_VALUE << 12; // 技能7

static const G_BIT_TYPE G_KEY_MOVE_MUSTER = G_KEY_MOVE_LEFT | G_KEY_MOVE_RIGHT | G_KEY_MOVE_UP | G_KEY_MOVE_DOWN;
static const G_BIT_TYPE G_KEY_MOVE_X = G_KEY_MOVE_LEFT | G_KEY_MOVE_RIGHT;
static const G_BIT_TYPE G_KEY_MOVE_Y = G_KEY_MOVE_UP | G_KEY_MOVE_DOWN;


//////////////////////////////////////////////////////////////////////////////
// 判断该键位是否自动复位
extern bool isAutoResetKey(G_BIT_TYPE key);
extern G_BIT_TYPE getAutoResetKeys();



//////////////////////////////////////////////////////////////////////////////
//// 获取标志位(从右到左的)下标
//static inline int32_t bitFlagIndex(G_BIT_TYPE bvalue)
//{
//#if 1
//	for (auto i = 0; i < sizeof(G_BIT_TYPE) * 8; ++i)
//	{
//		if ((bvalue >> i) & G_BIT_TYPE(0x1))
//			return i;
//	}
//#else
//	for (auto i = 1; i < sizeof(G_BIT_TYPE) * 8; ++i)
//	{
//		if (bvalue & (G_BIT_TYPE(0x1) << i))
//			return i;
//	}
//#endif
//	G_ASSERT(false);
//	return 0;
//}



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
