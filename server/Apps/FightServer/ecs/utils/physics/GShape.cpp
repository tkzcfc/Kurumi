#include "GShape.h"
#include "ecs/components/BodyComponent.h"

GCircle::GCircle(real r)
{
	radius = r;
}

void GCircle::setRotation(real radians)
{
}

#if G_TARGET_CLIENT
void GCircle::debugDraw(DrawNode* drawNode)
{
	if(body->bodyType == GBodyType::STATIC_BODY)
		drawNode->drawCircle(Vec2(body->position.x, body->position.y) * PHYSICS_PIXEL_TO_METER, radius * PHYSICS_PIXEL_TO_METER, body->radians, 100, true, Color4F::RED);
	else
		drawNode->drawCircle(Vec2(body->position.x, body->position.y) * PHYSICS_PIXEL_TO_METER, radius * PHYSICS_PIXEL_TO_METER, body->radians, 100, true, Color4F::WHITE);
}
#endif

GShape::Type GCircle::getType(void) const
{
	return GShape::Type::eCircle;
}


//////////////////////////////////////////////////////////////////////////


GPolygonShape::GPolygonShape()
{
	m_vertexCount = 0;
}

GPolygonShape::~GPolygonShape()
{}

void GPolygonShape::setRotation(real radians)
{
	u.set(radians);
}
#if G_TARGET_CLIENT
void GPolygonShape::debugDraw(DrawNode* drawNode)
{
	static Vec2 vertices[MaxPolyVertexCount];

	GVec2 v;
	for (uint32_t i = 0; i < m_vertexCount; ++i)
	{
		v = body->position + u * m_vertices[i];
		vertices[i].x = v.x * PHYSICS_PIXEL_TO_METER;
		vertices[i].y = v.y * PHYSICS_PIXEL_TO_METER;
	}
	if(body->bodyType == GBodyType::STATIC_BODY)
		drawNode->drawPoly(vertices, m_vertexCount, true, Color4F::RED);
	else
		drawNode->drawPoly(vertices, m_vertexCount, true, Color4F::WHITE);
}
#endif

GShape::Type GPolygonShape::getType(void) const
{
	return GShape::Type::ePoly;
}

// Half width and half height
void GPolygonShape::setBox(real hw, real hh)
{
	m_vertexCount = 4;
	m_vertices[0].set(-hw, -hh);
	m_vertices[1].set(hw, -hh);
	m_vertices[2].set(hw, hh);
	m_vertices[3].set(-hw, hh);
	m_normals[0].set(0.0f, -1.0f);
	m_normals[1].set(1.0f, 0.0f);
	m_normals[2].set(0.0f, 1.0f);
	m_normals[3].set(-1.0f, 0.0f);
}

void GPolygonShape::set(GVec2 *vertices, uint32_t count)
{
	// No hulls with less than 3 vertices (ensure actual polygon)
	assert(count > 2 && count <= MaxPolyVertexCount);
	count = MIN((int32_t)count, MaxPolyVertexCount);

	// Find the right most point on the hull
	int32_t rightMost = 0;
	real highestXCoord = vertices[0].x;
	for (uint32_t i = 1; i < count; ++i)
	{
		real x = vertices[i].x;
		if (x > highestXCoord)
		{
			highestXCoord = x;
			rightMost = i;
		}

		// If matching x then take farthest negative y
		else if (x == highestXCoord)
			if (vertices[i].y < vertices[rightMost].y)
				rightMost = i;
	}

	int32_t hull[MaxPolyVertexCount];
	int32_t outCount = 0;
	int32_t indexHull = rightMost;

	for (;;)
	{
		hull[outCount] = indexHull;

		// Search for next index that wraps around the hull
		// by computing cross products to find the most counter-clockwise
		// vertex in the set, given the previos hull index
		int32_t nextHullIndex = 0;
		for (int32_t i = 1; i < (int32_t)count; ++i)
		{
			// Skip if same coordinate as we need three unique
			// points in the set to perform a cross product
			if (nextHullIndex == indexHull)
			{
				nextHullIndex = i;
				continue;
			}

			// Cross every set of three unique vertices
			// Record each counter clockwise third vertex and add
			// to the output hull
			// See : http://www.oocities.org/pcgpe/math2d.html
			GVec2 e1 = vertices[nextHullIndex] - vertices[hull[outCount]];
			GVec2 e2 = vertices[i] - vertices[hull[outCount]];
			real c = cross(e1, e2);
			if (c < 0.0f)
				nextHullIndex = i;

			// Cross product is zero then e vectors are on same line
			// therefor want to record vertex farthest along that line
			if (c == 0.0f && e2.lenSqr() > e1.lenSqr())
				nextHullIndex = i;
		}

		++outCount;
		indexHull = nextHullIndex;

		// Conclude algorithm upon wrap-around
		if (nextHullIndex == rightMost)
		{
			m_vertexCount = outCount;
			break;
		}
	}

	// Copy vertices into shape's vertices
	for (uint32_t i = 0; i < m_vertexCount; ++i)
		m_vertices[i] = vertices[hull[i]];

	// Compute face normals
	for (uint32_t i1 = 0; i1 < m_vertexCount; ++i1)
	{
		uint32_t i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
		GVec2 face = m_vertices[i2] - m_vertices[i1];

		// Ensure no zero-length edges, because that's bad
		assert(face.lenSqr() > G_EPSILON * G_EPSILON);

		// Calculate normal with 2D cross product between vector and scalar
		m_normals[i1] = GVec2(face.y, -face.x);
		m_normals[i1].normalize();
	}
}

// The extreme point along a direction within a polygon
GVec2 GPolygonShape::GetSupport(const GVec2& dir)
{
	real bestProjection = -FLT_MAX;
	GVec2 bestVertex;

	for (uint32_t i = 0; i < m_vertexCount; ++i)
	{
		GVec2 v = m_vertices[i];
		real projection = dot(v, dir);

		if (projection > bestProjection)
		{
			bestVertex = v;
			bestProjection = projection;
		}
	}

	return bestVertex;
}

