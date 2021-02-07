#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/utils/animator/GActorStateMachine.h"

// 可锁定的状态
enum G_LOCK_STATUS : G_BIT_TYPE
{
	LOCK_S_NONE			= 0,
	LOCK_S_MOVE_X		= G_FIXED_VALUE << 1,	// X轴移动锁定(X轴无法移动)
	LOCK_S_MOVE_Y		= G_FIXED_VALUE << 2,	// y轴移动锁定(Y轴无法移动)
	LOCK_S_FACE_CAHGNE	= G_FIXED_VALUE << 3,	// 朝向锁定(无法改变朝向)
	LOCK_S_JUMP			= G_FIXED_VALUE << 4,	// 跳跃锁定(无法跳跃)

	// 全部锁定
	//LOCK_S_ALL			= LOCK_S_MOVE_X | LOCK_S_MOVE_Y | LOCK_S_FACE_CAHGNE | LOCK_S_JUMP,
};

enum PROPERTY_STATUS : G_BIT_TYPE
{
	PS_IS_NONE		= G_FIXED_VALUE,
	PS_IS_MOVE		= G_FIXED_VALUE << 1,		// 是否在移动(主动移动)
	PS_IS_JUMP		= G_FIXED_VALUE << 2,		// 是否处于跳跃状态
	PS_IS_IN_AIR	= G_FIXED_VALUE << 3,		// 是否处于空中
	PS_IS_FACE_R	= G_FIXED_VALUE << 4,		// 是否面朝右边
	PS_IS_DEATH		= G_FIXED_VALUE << 5,		// 是否死亡
};

class PropertyComponent : public BaseComponent
{
public:

	PropertyComponent()
	{
		status = PS_IS_NONE;
		uuid = 0;
		stateMachine = std::make_unique<GActorStateMachine>();
	}

	// 动画状态机
	std::unique_ptr<GActorStateMachine> stateMachine;

	// 属性状态
	PROPERTY_STATUS status;
	// 锁定状态
	G_LOCK_STATUS lockStatus;
	
	// uuid
	uint32_t uuid;
	// 移动力
	GVec2 moveForce;
	// 跳跃冲力
	GVec2 jumpIm;
};

