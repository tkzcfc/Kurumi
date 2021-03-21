#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/utils/animator/GActorStateMachine.h"

//! 锁定状态定义
static const G_BIT_TYPE G_LOCK_S_NONE			= 0;
static const G_BIT_TYPE G_LOCK_S_MOVE_X			= G_FIXED_VALUE << 1;	// X轴移动锁定(X轴无法移动)
static const G_BIT_TYPE G_LOCK_S_MOVE_Y			= G_FIXED_VALUE << 2;	// y轴移动锁定(Y轴无法移动)
static const G_BIT_TYPE G_LOCK_S_FACE_CAHGNE	= G_FIXED_VALUE << 3;	// 朝向锁定(无法改变朝向)
static const G_BIT_TYPE G_LOCK_S_JUMP			= G_FIXED_VALUE << 4;	// 跳跃锁定(无法跳跃)


//! 玩家状态定义
static const G_BIT_TYPE G_PS_IS_NONE		= 0;
static const G_BIT_TYPE G_PS_IS_IN_AIR		= G_FIXED_VALUE << 1;		// 是否处于空中
static const G_BIT_TYPE G_PS_IS_FACE_R		= G_FIXED_VALUE << 2;		// 是否面朝右边
static const G_BIT_TYPE G_PS_IS_DEATH		= G_FIXED_VALUE << 3;		// 是否死亡
static const G_BIT_TYPE G_PS_IS_BE_ATTACK	= G_FIXED_VALUE << 4;		// 是否被攻击


class PropertyComponent : public BaseComponent
{
public:

	PropertyComponent()
	{
		lockStatus = G_LOCK_S_NONE;
		status = G_PS_IS_NONE;
		uuid = 0;
		stateMachine = NULL;
		jumpCount = 0;
		jumpMaxCount = 2;
		modeDefaultScale = 1.0f;
		scale = 1.0f;

		attack = 10;
		armor = 10;
		maxHP = 100;
		HP = maxHP;
	}

	// 动画状态机
	std::shared_ptr<GActorStateMachine> stateMachine;

	// 属性状态
	G_BIT_TYPE status;
	// 锁定状态
	G_BIT_TYPE lockStatus;
	
	// uuid
	GUUID uuid;
	// 移动力
	GVec2 moveForce;
	// 跳跃冲力
	GVec2 jumpIm;

	// 攻击力
	int32_t attack;
	// 防御力
	int32_t armor;
	// 最大血量
	int32_t maxHP;
	// 当前血量
	int32_t HP;

	// 当前跳跃次数,落地时自动置为0
	int32_t jumpCount;
	// 跳跃最大次数
	int32_t jumpMaxCount;

	// 动画模型当前缩放值
	float32 scale;
	// 动画模型默认缩放值
	float32 modeDefaultScale;
};

