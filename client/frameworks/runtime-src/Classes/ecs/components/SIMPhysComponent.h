#pragma once

#include "ecs/anaxHelper.h"
#include "foundation/math/GMath.h"

class SIMPhysComponent : public BaseComponent
{
public:
	SIMPhysComponent()
	{
		linearDamping = 0.2f;
		gravityScale = 1.0f;
		isStatic = false;
		mass = 1.0f;
		invMass = 1 / mass;
	}

	bool isStatic;

	// 质量
	float32 mass;
	// 1/质量
	float32 invMass;

	// 线性阻尼
	float32 linearDamping;

	// 在没有空气阻力的地方，质量不会影响下降速度。
	// 要模拟真实的情况可以使用重力系数,或者使用阻尼模拟空气摩擦导致的减速情况
	float32 gravityScale;


	// 线性速度
	GVec2 linearVelocity;

	// 力
	GVec2 force;

	// postion + size = rect
	GVec2 position;
	GVec2 size;
};
