#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/utils/physics/GShape.h"

enum GBodyType
{
	STATIC_BODY,
	DYNAMIC_BODY
};

class BodyComponent : public BaseComponent
{
public:
	BodyComponent()
	{
		shape = NULL;
		angularVelocity = 0.0f;
		torque = 0.0f;
		radians = 0.0f;
		staticFriction = 0.5f;
		dynamicFriction = 0.3f;
		restitution = 0.2f;
		bodyType = GBodyType::DYNAMIC_BODY;
	}

	virtual ~BodyComponent()
	{
		if (shape)
			delete shape;
	}

	GBodyType bodyType;

	// 位置
	GVec2 position;
	// 速度
	GVec2 velocity;

	// 角速度
	real angularVelocity;
	// 扭矩
	real torque;
	// 旋转(弧度制)
	real radians;
	// 力
	GVec2 force;

	// 转动惯性,与角速度计算相关
	real I;
	//  1 / 转动惯性
	real iI;
	// 质量
	real m;
	//  1 / 质量
	real im;

	// http://gamedev.tutsplus.com/tutorials/implementation/how-to-create-a-custom-2d-physics-engine-friction-scene-and-jump-table/
	// 静态摩擦力
	real staticFriction;
	// 动态摩擦力
	real dynamicFriction;
	// 弹力
	real restitution;

	GShape* shape;
};
