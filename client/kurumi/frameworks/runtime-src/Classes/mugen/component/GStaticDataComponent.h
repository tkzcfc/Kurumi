#pragma once

#include "mugen/base/GComponent.h"
#include "mugen/geometry/GGeometry.h"

NS_G_BEGIN

class GStaticDataComponent : public GComponent
{
public:

	G_DEFINE_COMPONENT(GStaticDataComponent);

	GStaticDataComponent();

	virtual ~GStaticDataComponent();


	virtual void serialize(GByteBuffer& byteBuffer) override;

	virtual bool deserialize(GByteBuffer& byteBuffer) override;

public:

	// 资源朝向
	bool directionLeft;

	// 质量
	fixedPoint mass;

	// 尺寸大小
	GFixedVec3 size;
	
	// 角色半径
	fixedPoint radius;

	// 骨骼动画渲染位置偏移
	GFixedVec2 offset;

	// 骨骼动画资源路径
	std::string armatureFile;

	// 二进制文件名称
	// 比如: abc.bytes 则binaryFileName 值为abc
	std::string binaryFileName;

	//////////////////////////////// 动态属性字段 ////////////////////////////////
	// 移动速度
	GFixedVec2 moveSpeed;
	// 力
	GFixedVec3 force;

	// 跳跃冲力
	GFixedVec3 impulse;
};

NS_G_END
