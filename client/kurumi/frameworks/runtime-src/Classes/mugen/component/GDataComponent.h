#pragma once

#include "mugen/base/GComponent.h"
#include "mugen/geometry/GGeometry.h"

NS_G_BEGIN

// 动态数据组件
class GDataComponent  : public GComponent
{
public:

	G_DEFINE_COMPONENT(GDataComponent );

	GDataComponent ();

	virtual ~GDataComponent ();

	virtual void onAdd() override;

	void build();

public:

	// 移动速度
	GFixedVec2 moveSpeed;

	GFixedVec3 force;
	
	// 冲力
	GFixedVec3 impulse;
};

NS_G_END
