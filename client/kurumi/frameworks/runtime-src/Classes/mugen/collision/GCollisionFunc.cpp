#include "GCollisionFunc.h"
#include "GShapePolygon.h"
#include "GShapeAABB.h"
#include "GShapeCircle.h"

NS_G_BEGIN


static GFixedVec2 sVertexsA[MAX_POLY_VERTEX_COUNT];
static GFixedVec2 sVertexsB[MAX_POLY_VERTEX_COUNT];


CollisionCallback GCollisionFunc::dispatch[ECollisionType::NONE][ECollisionType::NONE] = {
	{ GCollisionFunc::aabbToAABB, GCollisionFunc::aabbToPolygon, GCollisionFunc::aabbToCircle },
	{ GCollisionFunc::polygonToAABB, GCollisionFunc::polygonToPolygon, GCollisionFunc::polygonToCircle },
	{ GCollisionFunc::circleToAABB, GCollisionFunc::circleToPolygon, GCollisionFunc::circleToCircle },
};


////////////////////////////////////////////////////////////////////////////////

static bool GameMath_Tmp(const GFixedVec2& IS, const GFixedVec2* A, const GFixedVec2* B)
{
	fixedPoint v[4];
	for (int i = 0; i < 4; i++)
	{
		fixedPoint tmp = (IS.x * A[i].x + IS.y * A[i].y) / (IS.x * IS.x + IS.y * IS.y);
		v[i] = tmp * IS.x * IS.x + tmp * IS.y * IS.y;
	}
	fixedPoint vv[4];
	for (int i = 0; i < 4; i++)
	{
		fixedPoint tmp = (IS.x * B[i].x + IS.y * B[i].y) / (IS.x * IS.x + IS.y * IS.y);
		vv[i] = tmp * IS.x * IS.x + tmp * IS.y * IS.y;
	}
	//表示暂时不知道是否碰撞
	if (MAX(MAX(v[0], v[1]), MAX(v[2], v[3])) > MIN(MIN(vv[0], vv[1]), MIN(vv[2], vv[3])) && MIN(MIN(v[0], v[1]), MIN(v[2], v[3])) < MAX(MAX(vv[0], vv[1]), MAX(vv[2], vv[3])))
	{
		return false;
	}
	//表示知道未碰撞
	else
	{
		return true;
	}
}

// 矩形碰撞检测
static bool isRectIntersect(const GFixedVec2* A, const GFixedVec2* B)
{
	static GFixedVec2 Ax, Ay, Bx, By;

	Ax.x = A[0].x - A[1].x;
	Ax.y = A[0].y - A[1].y;
	Ay.x = A[0].x - A[3].x;
	Ay.y = A[0].y - A[3].y;
	Bx.x = B[0].x - B[1].x;
	Bx.y = B[0].y - B[1].y;
	By.x = B[0].x - B[3].x;
	By.y = B[0].y - B[3].y;

	if (GameMath_Tmp(Ax, A, B)) return false;
	if (GameMath_Tmp(Ay, A, B)) return false;
	if (GameMath_Tmp(Bx, A, B)) return false;
	if (GameMath_Tmp(By, A, B)) return false;
	return true;
}



////////////////////////////////////////////////////////////////////////////////

bool GCollisionFunc::aabbToAABB(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb)
{
	return true;
}

bool GCollisionFunc::aabbToPolygon(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb)
{
	GShapePolygon* shapeB = static_cast<GShapePolygon*>(b);

	for (auto i = 0U; i < shapeB->getVerticesCount(); ++i)
	{
		mulT_quick(tfb, shapeB->getVertexs()[i], sVertexsB[i]);
	}

	return polyRect(sVertexsB, shapeB->getVerticesCount(), a->getAABB());
}

bool GCollisionFunc::aabbToCircle(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb)
{
	return circleToAABB(b, a, tfb, tfa);
}

bool GCollisionFunc::polygonToAABB(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb)
{
	return aabbToPolygon(b, a, tfb, tfa);
}

bool GCollisionFunc::polygonToPolygon(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb)
{
	GShapePolygon* shapeA = static_cast<GShapePolygon*>(a);
	GShapePolygon* shapeB = static_cast<GShapePolygon*>(b);

	for (auto i = 0U; i < shapeA->getVerticesCount(); ++i)
	{
		mulT_quick(tfa, shapeA->getVertexs()[i], sVertexsA[i]);
	}
	for (auto i = 0U; i < shapeB->getVerticesCount(); ++i)
	{
		mulT_quick(tfb, shapeB->getVertexs()[i], sVertexsB[i]);
	}

#if 0
	// 经过测试 isRectIntersect 方法与 polyPoly 效率差距不大,且通用性没有 polyPoly 好
	if (shapeA->getVerticesCount() == 4 && shapeB->getVerticesCount() == 4)
	{
		return isRectIntersect(sVertexsA, sVertexsB);
	}
#endif
	return polyPoly(sVertexsA, shapeA->getVerticesCount(), sVertexsB, shapeB->getVerticesCount());
}


bool GCollisionFunc::polygonToCircle(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb)
{
	return circleToPolygon(b, a, tfb, tfa);
}

bool GCollisionFunc::circleToAABB(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb)
{
	return circleToPolygon(a, b, tfb, tfa);
}

bool GCollisionFunc::circleToPolygon(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb)
{
	GShapeCircle* shapeA = static_cast<GShapeCircle*>(a);
	GShapePolygon* shapeB = static_cast<GShapePolygon*>(b);

	auto cA = mulT(tfa, shapeA->getCenter());

	auto polygonVcount = shapeB->getVerticesCount();
	for (auto i = 0U; i < polygonVcount; ++i)
	{
		mulT_quick(tfb, shapeB->getVertexs()[i], sVertexsB[i]);
	}

	if (isPointInPolygon(sVertexsB, polygonVcount, cA))
		return true;

	for (auto i = 0; i < polygonVcount; i++)
	{
		const auto& start = i == 0 ? sVertexsB[polygonVcount - 1] : sVertexsB[i - 1];
		const auto& end = sVertexsB[i];

		if (pointLineDistance(cA, start, end, true) < shapeA->getRadius()) {
			return true;
		}
	}

	return false;
}

bool GCollisionFunc::circleToCircle(GShape* a, GShape* b, const GFixedTransform& tfa, const GFixedTransform& tfb)
{
	GShapeCircle* shapeA = static_cast<GShapeCircle*>(a);
	GShapeCircle* shapeB = static_cast<GShapeCircle*>(b);

	auto cA = mulT(tfa, shapeA->getCenter());
	auto cB = mulT(tfb, shapeB->getCenter());

	auto dx = cA.x - cB.x;
	auto dy = cA.y - cB.y;

	auto distance = dx * dx + dy * dy;

	return distance.sqrt() < (shapeA->getRadius() + shapeB->getRadius());
}











// 多边形和点碰撞检测
bool GCollisionFunc::isPointInPolygon(GFixedVec2* vertices, int count, const GFixedVec2& p)
{
	// 此处逻辑是aabb检测
	fixedPoint minX = vertices[0].x;
	fixedPoint maxX = vertices[0].x;
	fixedPoint minY = vertices[0].y;
	fixedPoint maxY = vertices[0].y;
	for (int i = 1; i < count; i++)
	{
		auto q = vertices + i;
		minX = MIN(q->x, minX);
		maxX = MAX(q->x, maxX);
		minY = MIN(q->y, minY);
		maxY = MAX(q->y, maxY);
	}

	if (p.x < minX || p.x > maxX || p.y < minY || p.y > maxY)
	{
		return false;
	}

	// https://wrf.ecse.rpi.edu/Research/Short_Notes/pnpoly.html
	bool inside = false;
	for (int i = 0, j = count - 1; i < count; j = i++)
	{
		if ((vertices[i].y > p.y) != (vertices[j].y > p.y) &&
			(p.x < (vertices[j].x - vertices[i].x) * (p.y - vertices[i].y) / (vertices[j].y - vertices[i].y) + vertices[i].x))
		{
			inside = !inside;
		}
	}

	return inside;
}


// http://www.jeffreythompson.org/collision-detection/poly-poly.php
// https://github.com/cocos-creator/engine/blob/develop/cocos/physics-2d/builtin/intersection-2d.ts
// POLYGON/POLYGON
bool GCollisionFunc::polyPoly(GFixedVec2* p1, int count1, GFixedVec2* p2, int count2)
{
	// go through each of the vertices, plus the next
	// vertex in the list
	int next = 0;
	for (int current = 0; current < count1; current++) {

		// get next vertex in list
		// if we've hit the end, wrap around to 0
		next = current + 1;
		if (next == count1) next = 0;

		// get the PVectors at our current position
		// this makes our if statement a little cleaner
		const GFixedVec2& vc = p1[current];    // c for "current"
		const GFixedVec2& vn = p1[next];       // n for "next"

		// now we can use these two points (a line) to compare
		// to the other polygon's vertices using polyLine()
		bool collision = polyLine(p2, count2, vc, vn);
		if (collision) return true;
	}

	// check if a contains b
	for (auto i = 0; i < count2; ++i)
	{
		if (isPointInPolygon(p1, count1, p2[i])) return true;
	}

	// check if b contains a
	for (auto i = 0; i < count1; ++i)
	{
		if (isPointInPolygon(p2, count2, p1[i])) return true;
	}

	return false;
}

// POLYGON/LINE
bool GCollisionFunc::polyLine(GFixedVec2* vertices, int count, const GFixedVec2& from, const GFixedVec2& to)
{
	// go through each of the vertices, plus the next
	// vertex in the list
	int next = 0;
	for (int current = 0; current < count; current++) {

		// get next vertex in list
		// if we've hit the end, wrap around to 0
		next = current + 1;
		if (next == count) next = 0;

		// do a Line/Line comparison
		// if true, return 'true' immediately and
		// stop testing (faster)
		bool hit = lineLine(from, to, vertices[current], vertices[next]);
		if (hit) {
			return true;
		}
	}

	// never got a hit
	return false;
}

// LINE/LINE
bool GCollisionFunc::lineLine(const GFixedVec2& a1, const GFixedVec2& a2, const GFixedVec2& b1, const GFixedVec2& b2)
{
	fixedPoint ua_t = (b2.x - b1.x) * (a1.y - b1.y) - (b2.y - b1.y) * (a1.x - b1.x);
	fixedPoint ub_t = (a2.x - a1.x) * (a1.y - b1.y) - (a2.y - a1.y) * (a1.x - b1.x);
	fixedPoint u_b  = (b2.y - b1.y) * (a2.x - a1.x) - (b2.x - b1.x) * (a2.y - a1.y);

	if (u_b != 0.0f) {
		fixedPoint ua = ua_t / u_b;
		fixedPoint ub = ub_t / u_b;

		if (ua >= 0.0f && ua <= 1.0f && ub >= 0.0f && ub <= 1.0f) {
			return true;
		}
	}

	return false;

}

// LINE/RECTANGLE
bool GCollisionFunc::lineRect(const GFixedVec2& from, const GFixedVec2& to, const GFixedRect& rect)
{
	GFixedVec2 r0(rect.minx, rect.miny);
	GFixedVec2 r1(rect.minx, rect.maxy);
	GFixedVec2 r2(rect.maxx, rect.maxy);
	GFixedVec2 r3(rect.maxx, rect.miny);

	if (lineLine(from, to, r0, r1)) return true;

	if (lineLine(from, to, r1, r2)) return true;

	if (lineLine(from, to, r2, r3)) return true;

	if (lineLine(from, to, r3, r0)) return true;

	return false;
}

// POLYGON/RECTANGLE
bool GCollisionFunc::polyRect(GFixedVec2* vertices, int count, const GFixedRect& rect)
{
	GFixedVec2 r0(rect.minx, rect.miny);
	GFixedVec2 r1(rect.minx, rect.maxy);
	GFixedVec2 r2(rect.maxx, rect.maxy);
	GFixedVec2 r3(rect.maxx, rect.miny);

	// intersection check
	if (polyLine(vertices, count, r0, r1)) return true;

	if (polyLine(vertices, count, r1, r2)) return true;

	if (polyLine(vertices, count, r2, r3)) return true;

	if (polyLine(vertices, count, r3, r0)) return true;

	// check if a contains b
	for (auto i = 0; i < count; ++i) {
		if (rect.containsPoint(vertices[i])) return true;
	}

	// check if b contains a
	if (isPointInPolygon(vertices, count, r0)) return true;

	if (isPointInPolygon(vertices, count, r1)) return true;

	if (isPointInPolygon(vertices, count, r2)) return true;

	if (isPointInPolygon(vertices, count, r3)) return true;

	return false;
}

fixedPoint GCollisionFunc::pointLineDistance(const GFixedVec2& point, const GFixedVec2& start, const GFixedVec2& end, bool isSegment)
{
	auto dx = end.x - start.x;
	auto dy = end.y - start.y;
	auto d = dx * dx + dy * dy;
	auto t = ((point.x - start.x) * dx + (point.y - start.y) * dy) / d;
	GFixedVec2 p;

	if (!isSegment) 
	{
		p.x = start.x + t * dx;
		p.y = start.y + t * dy;
	}
	else 
	{
		if (d.isZero()) 
		{
			p = start;
		}
		else 
		{
			if (t < 0.0f) 
			{
				p = start;
			}
			else if (t > 1.0f)
			{
				p = end;
			}
			else 
			{
				p.x = start.x + t * dx;
				p.y = start.y + t * dy;
			}
		}
	}

	dx = point.x - p.x;
	dy = point.y - p.y;

	auto distanceSQ = dx * dx + dy * dy;

	return distanceSQ.sqrt();
}

NS_G_END
