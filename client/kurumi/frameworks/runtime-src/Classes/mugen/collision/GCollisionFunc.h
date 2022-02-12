#pragma once

#include "mugen/geometry/GGeometry.h"

NS_G_BEGIN

enum ECollisionType
{
	RECT_AABB,
	POLYGON,
	CIRCLE,
	NONE,
};

class GShape;
typedef bool(*CollisionCallback)(GShape*, GShape*, const GFixedTransform&, const GFixedTransform&);

class GCollisionFunc
{
public:

	static CollisionCallback dispatch[ECollisionType::NONE][ECollisionType::NONE];

	static bool aabbToAABB(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb);
	static bool aabbToPolygon(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb);
	static bool aabbToCircle(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb);


	static bool polygonToAABB(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb);
	static bool polygonToPolygon(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb);
	static bool polygonToCircle(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb);


	static bool circleToAABB(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb);
	static bool circleToPolygon(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb);
	static bool circleToCircle(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb);
	

public:

	static bool isPointInPolygon(GFixedVec2* vertices, int count, const GFixedVec2& p);

	static bool lineLine(const GFixedVec2& from1, const GFixedVec2& to1, const GFixedVec2& from2, const GFixedVec2& to2);

	static bool polyLine(GFixedVec2* vertices, int count, const GFixedVec2& from, const GFixedVec2& to);

	static bool polyPoly(GFixedVec2* p1, int count1, GFixedVec2* p2, int count2);

	static bool lineRect(const GFixedVec2& from, const GFixedVec2& to, const GFixedRect& rect);

	static bool polyRect(GFixedVec2* vertices, int count, const GFixedRect& rect);

	static fixedPoint pointLineDistance(const GFixedVec2& point, const GFixedVec2& start, const GFixedVec2& end, bool isSegment);
};

NS_G_END
