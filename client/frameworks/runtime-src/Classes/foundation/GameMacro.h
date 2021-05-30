#pragma once

#include <assert.h>
#include <string>
#include <vector>
#include <unordered_map>

#ifdef COCOS2D_DEBUG
#define G_TARGET_SERVER 0
#define G_DEBUG COCOS2D_DEBUG
#define G_LOG_I CCLOG
#define G_LOG_W CCLOG
#define G_LOG_E CCLOG
#define G_LOG_F CCLOG
#define G_ASSERT assert
#else
#define G_TARGET_SERVER 1
#define G_DEBUG _DEBUG
#define G_LOG_I(format, ...) flog::log_i(format, ##__VA_ARGS__)
#define G_LOG_W(format, ...) flog::log_w(format, ##__VA_ARGS__)
#define G_LOG_E(format, ...) flog::log_e(format, ##__VA_ARGS__)
#define G_LOG_F(format, ...) flog::log_f(format, ##__VA_ARGS__)
#endif

#if G_TARGET_SERVER
#define G_TARGET_CLIENT 0
#include "GLibBase.h"
#include "GLog.h"
#else
#define G_TARGET_CLIENT 1
#include "cocos2d.h"

#include "json/document.h"
#include "json/stringbuffer.h"

using namespace cocos2d;
#endif

#ifndef G_FORCEINLINE
#define G_FORCEINLINE inline
#endif


//! 位操作相关
#define G_BIT_SET(b, flag) (b) |= (flag)
#define G_BIT_GET(b, flag) (b) & (flag)
#define G_BIT_REMOVE(b, flag) (b) &= ~(flag)
#define G_BIT_EQUAL(b, flag) ((b) & (flag)) == (flag)
#define G_BIT_NO_EQUAL(b, flag) ((b) & (flag)) != (flag)


//! 获取数组长度
#ifndef G_ARRAY_LEN
#define G_ARRAY_LEN(array) sizeof(array) / sizeof(array[0])
#endif

////////////////////////////////////////////////////////////////////////////////////

//! 在地图中战斗的玩家最大个数
#define G_FIGHT_MAX_PLAYER_COUNT 4

//! 物理引擎对应渲染像素比
#define PHYSICS_PIXEL_TO_METER 100.0f


inline bool str_equal(const char* str1, const char* str2)
{
	return strcmp(str1, str2) == 0;
}

inline bool float_equal(float a, float b)
{
	return std::abs(a - b) <= 0.0001f;
}


typedef int32_t GUUID;
#define INVALID_UUID 0U