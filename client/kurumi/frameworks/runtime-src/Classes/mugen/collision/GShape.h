#pragma once

#include "GCollisionFunc.h"
#include "GBody.h"

NS_G_BEGIN


class GShape : public GObject
{
public:

	GShape();

	virtual ~GShape();

	G_SYNTHESIZE_READONLY_BY_REF(GFixedRect, m_aabb, AABB);
	G_SYNTHESIZE_READONLY_BY_REF(ECollisionType, m_type, Type);
	G_SYNTHESIZE(GBody*, m_body, Body);


	void boundingBoxDirty();

	virtual void updateAABB() = 0;

	virtual bool intersects(GShape* other);

	bool aabbTest(const GFixedRect& rect) const;

private:
	bool m_boundingBoxDirty;
};

NS_G_END

