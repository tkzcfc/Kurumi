#pragma once

#include "foundation/math/GMath.h"

#if G_TARGET_CLIENT
#include "cocos2d.h"
USING_NS_CC;
#endif

#define MaxPolyVertexCount 64

/// GShape
class GShape
{
public:

	enum Type
	{
		eCircle,
		ePoly,
		eCount
	};

	GShape() {}

	virtual void setRotation(real radians) = 0;
	
	virtual Type getType(void) const = 0;

#if G_TARGET_CLIENT
	virtual void debugDraw(DrawNode* drawNode) = 0;
#endif

	class BodyComponent* body;
};

/// GCircle
class GCircle : public GShape
{
public:
	GCircle(real r);

	virtual void setRotation(real radians)override;

#if G_TARGET_CLIENT
	virtual void debugDraw(DrawNode* drawNode)override;
#endif

	virtual Type getType(void) const override;

	// °ë¾¶
	real radius;
};

/// GPolygonShape
class GPolygonShape : public GShape
{
public:

	GPolygonShape();

	virtual ~GPolygonShape();

	virtual void setRotation(real radians)override;

#if G_TARGET_CLIENT
	virtual void debugDraw(DrawNode* drawNode)override;
#endif
	
	virtual Type getType(void) const override;

	// Half width and half height
	void setBox(real hw, real hh);

	void set(GVec2 *vertices, uint32_t count);

	// The extreme point along a direction within a polygon
	GVec2 GetSupport(const GVec2& dir);

	uint32_t m_vertexCount;
	GVec2 m_vertices[MaxPolyVertexCount];
	GVec2 m_normals[MaxPolyVertexCount];
	GMat2 u; // Orientation matrix from model to world
};
