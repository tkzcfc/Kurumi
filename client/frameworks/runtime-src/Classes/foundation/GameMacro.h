#pragma once

#include <assert.h>

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
#define G_LOG_I(...) do {} while (0)
#define G_LOG_W(...) do {} while (0)
#define G_LOG_E(...) do {} while (0)
#define G_LOG_F(...) do {} while (0)
#define G_ASSERT assert
#endif

#if G_TARGET_SERVER
#define G_TARGET_CLIENT 0
#else
#define G_TARGET_CLIENT 1
#endif



#include "cocos2d.h"
#include <string>
#include <unordered_map>

using namespace cocos2d;

#define PHYSICS_PIXEL_TO_METER 100.0f

enum BOX2D_FILTER_MASK
{
	B2DM_GROUND		= 1 << 1, // 地面
	B2DM_SIDE_WALL	= 1 << 2, // 墙壁
	B2DM_PLAYER		= 1 << 3, // 玩家
	B2DM_MONSTER	= 1 << 4, // 怪物
	B2DM_SKILL		= 1 << 5, // 技能
};

#define GAMEWORLD_NODE_MAP 0
#define GAMEWORLD_NODE_UI  1
#define GAMEWORLD_NODE_MAX 2


#if COCOS2D_DEBUG == 1 
#define ENABLE_ARMATURE_COLLISION_DRAW_DEBUG 1
#define ENABLE_BOX2D_DEBUG_DRAW
#else
#define ENABLE_ARMATURE_COLLISION_DRAW_DEBUG 0
#endif