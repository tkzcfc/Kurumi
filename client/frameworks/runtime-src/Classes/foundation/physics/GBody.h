#pragma once

#include "foundation/math/GMath.h"

class GShape;

enum GBodyType
{
	STATIC_BODY,
	DYNAMIC_BODY
};

class GBody
{
public:

	GBody(GShape *shape_, uint32_t x, uint32_t y);


	// 施加力
	void applyForce(const GVec2& f)
	{
		force += f;
	}

	// 施加冲力
	void applyImpulse(const GVec2& impulse, const GVec2& contactVector)
	{
		velocity += im * impulse;
		angularVelocity += iI * cross(contactVector, impulse);
	}

	// 设置物体为静态物体
	void setStatic(void)
	{
		type = GBodyType::STATIC_BODY;
		I = 0.0f;
		iI = 0.0f;
		m = 0.0f;
		im = 0.0f;
	}

	// 旋转设置
	void setOrient(real radians);

	// 位置
	GVec2 position;
	// 速度
	GVec2 velocity;

	// 角速度
	real angularVelocity;
	// 扭矩
	real torque; 
	// 旋转(弧度制)
	real orient;
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

	// Shape interface
	GShape *shape;

	GBodyType type;
};
