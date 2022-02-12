#pragma once

#include "GShapePolygon.h"

NS_G_BEGIN

// 使用aabb碰撞则只支持缩放不支持旋转
class GShapeAABB : public GShapePolygon
{
public:

	GShapeAABB();

	virtual ~GShapeAABB();
	
	virtual bool deserialize(GByteBuffer& byteBuffer) override;

	virtual void set(GFixedVec2* vertices, uint32_t count) override;

	void setRect(const GFixedVec2& pos, const GFixedVec2& size);

protected:

	void check();
};

NS_G_END