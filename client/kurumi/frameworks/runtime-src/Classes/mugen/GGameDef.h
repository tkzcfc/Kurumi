#pragma once

#include "mugen/platform/GStdC.h"

NS_G_BEGIN

#define GAME_LOGIC_FPS 30

static const fixedPoint LogicInterval = 1.0f / GAME_LOGIC_FPS;


//! 物理引擎对应渲染像素比
#define PHYSICS_PIXEL_TO_METER 100.0f



//////////////////////////////////////////////////////////////////////////////
// 类型定义
typedef uint32_t G_BIT_TYPE;

// 位偏移基数
static const G_BIT_TYPE G_FIXED_VALUE = 0x1U;

// 最大定义个数
static const uint32_t G_BIT_MAX_COUNT = sizeof(G_BIT_TYPE) * 8 - 1;


//! 游戏操作命令定义
//static const G_BIT_TYPE G_CMD_NONE		= 0x0;				  // 空值
//static const G_BIT_TYPE G_CMD_KEY_DOWN	= G_FIXED_VALUE << 1; // 按键按下命令
//static const G_BIT_TYPE G_CMD_KEY_UP	= G_FIXED_VALUE << 2; // 按键抬起命令


//! 游戏按键定义
static const G_BIT_TYPE G_KEY_NONE = 0x0U;				  // 空值
static const G_BIT_TYPE G_KEY_MOVE_LEFT = G_FIXED_VALUE << 1; // 左移
static const G_BIT_TYPE G_KEY_MOVE_RIGHT = G_FIXED_VALUE << 2; // 右移
static const G_BIT_TYPE G_KEY_MOVE_UP = G_FIXED_VALUE << 3; // 上移
static const G_BIT_TYPE G_KEY_MOVE_DOWN = G_FIXED_VALUE << 4; // 下移
static const G_BIT_TYPE G_KEY_JUMP = G_FIXED_VALUE << 5; // 跳跃
static const G_BIT_TYPE G_KEY_SKILL_1 = G_FIXED_VALUE << 6; // 技能1
static const G_BIT_TYPE G_KEY_SKILL_2 = G_FIXED_VALUE << 7; // 技能2
static const G_BIT_TYPE G_KEY_SKILL_3 = G_FIXED_VALUE << 8; // 技能3
static const G_BIT_TYPE G_KEY_SKILL_4 = G_FIXED_VALUE << 9; // 技能4
static const G_BIT_TYPE G_KEY_SKILL_5 = G_FIXED_VALUE << 10; // 技能5
static const G_BIT_TYPE G_KEY_SKILL_6 = G_FIXED_VALUE << 11; // 技能6
static const G_BIT_TYPE G_KEY_SKILL_7 = G_FIXED_VALUE << 12; // 技能7

static const uint32_t G_KEY_MAX_COUNT = 12;

static const G_BIT_TYPE G_KEY_MOVE_MUSTER = G_KEY_MOVE_LEFT | G_KEY_MOVE_RIGHT | G_KEY_MOVE_UP | G_KEY_MOVE_DOWN;
static const G_BIT_TYPE G_KEY_MOVE_X = G_KEY_MOVE_LEFT | G_KEY_MOVE_RIGHT;
static const G_BIT_TYPE G_KEY_MOVE_Y = G_KEY_MOVE_UP | G_KEY_MOVE_DOWN;


//////////////////////////////////////////////////////////////////////////////

static const int32_t INVALID_SKILL_ID = -1;



//////////////////////////////////////////////////////////////////////////////
// 碰撞相关类型定义

enum GCampEnums 
{
	CAMP_1,	// 阵营1
	CAMP_2,	// 阵营2
	CAMP_3,	// 阵营3
	CAMP_4,	// 阵营4
};

enum GCategoryEnums
{
	ROLE		= G_FIXED_VALUE << 1,
	FRIEND_BUFF = G_FIXED_VALUE << 2,// 增益型buff，施加给友方
	HURT_BUFF	= G_FIXED_VALUE << 3, // 伤害型buff，施加给敌方
};


//////////////////////////////////////////////////////////////////////////////
// 状态定义
enum class GActorStatus
{
	IDLE	= G_FIXED_VALUE << 1,
	DEATH	= G_FIXED_VALUE << 2,
	RUN     = G_FIXED_VALUE << 3,
};


//////////////////////////////////////////////////////////////////////////////
/// 标签定义

// 被锁定方向
static const G_BIT_TYPE Flag_Lock_Orientation = G_FIXED_VALUE << 1;

//////////////////////////////////////////////////////////////////////////////
// 朝向定义
enum class GActorOrientation : G_BIT_TYPE
{
	LEFT,
	RIGHT,
};

//////////////////////////////////////////////////////////////////////////////
// 值类型定义
enum class GValueType
{
	// 百分比
	VALUE_PERCENTAGE = 0,
	// 绝对值
	VALUE_ABSOLUTE,
};

enum class GForceOrientation
{
	Positive_Direction, // 正方向(actor面向的方向)
	Negative_Direction, // 反方向(actor背面的方向)
};

NS_G_END
