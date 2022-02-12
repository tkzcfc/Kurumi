#pragma once

#include "mugen/platform/GStdC.h"
#include "mugen/GGameDef.h"

NS_G_BEGIN

//////////////////////////////////////////////////////////////////////////////
//! 消息定义
// 基础消息
#pragma pack(4)
struct GOPMsg
{
	uint32_t logicFrame;
	// 操作对象
	uint32_t uuid;

	G_BIT_TYPE keydown;
};
#pragma pack()

NS_G_END