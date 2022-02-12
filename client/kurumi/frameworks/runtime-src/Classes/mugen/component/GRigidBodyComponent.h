#pragma once

#include "mugen/base/GComponent.h"
#include "mugen/geometry/GGeometry.h"

NS_G_BEGIN

class GRigidBodyComponent : public GComponent
{
public:

	G_DEFINE_COMPONENT(GRigidBodyComponent);

	GRigidBodyComponent();

	virtual ~GRigidBodyComponent();

	// 质量设置
	void setMass(const fixedPoint& mass);

	// 增加偏移量
	void appendOffset(const fixedPoint& x, const fixedPoint& y);

	// 力施加
	void applyForce(const GFixedVec3& f);

	// 冲力施加
	void applyImpulse(const GFixedVec3& impulse);


	void setBox(const GFixedVec3& origin, const GFixedVec3& size, const GFixedVec3& anchor);

	// 设置为静态box
	void setStaticBox(const GFixedVec2& origin, const GFixedVec2& size, const GFixedVec2& anchor);
	
public:

	bool isStatic;

	// 质量
	fixedPoint mass;
	// 1/质量
	fixedPoint invMass;

	// 线性阻尼
	// 使用阻尼模拟空气摩擦导致的减速情况
	fixedPoint linearDamping;

	// 重力缩放系数
	fixedPoint gravityScale;


	// 线性速度
	GFixedVec3 linearVelocity;

	// 当前力
	GFixedVec3 force;

	// postion + size = box
	GFixedVec3 position;
	GFixedVec3 size;


	// 物理模拟计算后对位置的偏移修改
	// 用于匀速运动模拟
	GFixedVec3 offsetOneFrame;
};

NS_G_END
