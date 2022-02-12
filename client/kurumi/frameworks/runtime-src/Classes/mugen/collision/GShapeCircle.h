#pragma once


#include "GShape.h"

NS_G_BEGIN

class GShapeCircle : public GShape
{
public:

	GShapeCircle();

	virtual ~GShapeCircle();

	G_SYNTHESIZE_READONLY_BY_REF(GFixedVec2, m_center, Center);
	G_SYNTHESIZE_READONLY(fixedPoint, m_radius, Radius);

	virtual void set(const GFixedVec2& center, fixedPoint radius);

public:

	virtual void serialize(GByteBuffer& byteBuffer) override;

	virtual bool deserialize(GByteBuffer& byteBuffer) override;

	virtual void updateAABB() override;
};

NS_G_END