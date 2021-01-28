#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/utils/animator/PlayerStateMachine.h"

// 可锁定的状态
enum G_LOCK_STATUS
{
	LOCK_S_NONE			= 0,
	LOCK_S_MOVE_X		= G_FIXED_VALUE << 1,	// X轴移动锁定(X轴无法移动)
	LOCK_S_MOVE_Y		= G_FIXED_VALUE << 2,	// y轴移动锁定(Y轴无法移动)
	LOCK_S_FACE_CAHGNE	= G_FIXED_VALUE << 3,	// 朝向锁定(无法改变朝向)
	LOCK_S_JUMP			= G_FIXED_VALUE << 4,	// 跳跃锁定(无法跳跃)

	// 全部锁定
	//LOCK_S_ALL			= LOCK_S_MOVE_X | LOCK_S_MOVE_Y | LOCK_S_FACE_CAHGNE | LOCK_S_JUMP,
};

class PropertyComponent : public BaseComponent
{
public:

	PropertyComponent()
	{
		isInAir = false;
		isJumping = false;
		faceRight = true;
		uuid = 0;
		stateMachine = std::make_unique<PlayerStateMachine>();
	}

	// 是否在空中
	bool isInAir;
	// 是否处于跳跃状态
	bool isJumping;

	// 动画状态机
	std::unique_ptr<PlayerStateMachine> stateMachine;

	// 锁定状态
	G_LOCK_STATUS lockStatus;
	// 面朝右侧
	bool faceRight;

	uint32_t uuid;

	// 移动力
	GVec2 moveForce;
	// 跳跃冲力
	GVec2 jumpIm;
};

