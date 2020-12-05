#pragma once


#include "GBody.h"

#define MaxPolyVertexCount 64

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
	virtual GShape *clone(void) const = 0;
	virtual void initialize(void) = 0;
	virtual void computeMass(real density) = 0;
	virtual void setOrient(real radians) = 0;
	virtual Type getType(void) const = 0;

	GBody *body;

	// For circle shape
	real radius;
	// 圆形用到的参数

	// For Polygon shape
	GMat2 u; // Orientation matrix from model to world
	// 从模型到世界的方向矩阵
};

struct GCircle : public GShape
{
	GCircle(real r)
	{
		radius = r;
	}

	GShape *clone(void) const
	{
		return new GCircle(radius);
	}

	void initialize(void)
	{
		computeMass(1.0f);
	}

	// 质量计算
	// @param density 密度,默认1
	void computeMass(real density)
	{
		// PI R 的平方 * 密度 = 面积*密度
		body->m = G_PI * radius * radius * density;
		body->im = (body->m) ? 1.0f / body->m : 0.0f;// 1/质量 
		body->I = body->m * radius * radius;  // 转动惯性
		body->iI = (body->I) ? 1.0f / body->I : 0.0f;
	}

	void setOrient(real radians)
	{
	}

	void Draw(void) const
	{
		/*
		const uint32 k_segments = 20;

		// Render a circle with a bunch of lines
		// 用一堆线渲染一个圆
		glColor3f(body->r, body->g, body->b);
		glBegin(GL_LINE_LOOP);
		real theta = body->orient;
		real inc = PI * 2.0f / (real)k_segments;
		for (uint32 i = 0; i < k_segments; ++i)
		{
			theta += inc;
			Vec2 p(std::cos(theta), std::sin(theta));
			p *= radius;
			p += body->position;
			glVertex2f(p.x, p.y);
		}
		glEnd();

		// Render line within circle so orientation is visible
		// 在圆内渲染线，以便方向可见
		glBegin(GL_LINE_STRIP);
		Vec2 r(0, 1.0f);
		real c = std::cos(body->orient);
		real s = std::sin(body->orient);
		r.Set(r.x * c - r.y * s, r.x * s + r.y * c);
		r *= radius;
		r = r + body->position;
		glVertex2f(body->position.x, body->position.y);
		glVertex2f(r.x, r.y);
		glEnd();
		*/
	}

	Type getType(void) const
	{
		return eCircle;
	}
};

struct GPolygonShape : public GShape
{
	void initialize(void)
	{
		computeMass(1.0f);
	}

	GShape *clone(void) const
	{
		GPolygonShape *poly = new GPolygonShape();
		poly->u = u;
		for (uint32_t i = 0; i < m_vertexCount; ++i)
		{
			poly->m_vertices[i] = m_vertices[i];
			poly->m_normals[i] = m_normals[i];
		}
		poly->m_vertexCount = m_vertexCount;
		return poly;
	}

	void computeMass(real density)
	{
		// Calculate centroid and moment of interia
		GVec2 c(0.0f, 0.0f); // centroid
		real area = 0.0f;
		real I = 0.0f;
		const real k_inv3 = 1.0f / 3.0f;

		for (uint32_t i1 = 0; i1 < m_vertexCount; ++i1)
		{
			// Triangle vertices, third vertex implied as (0, 0)
			GVec2 p1(m_vertices[i1]);
			uint32_t i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
			GVec2 p2(m_vertices[i2]);

			real D = cross(p1, p2);
			real triangleArea = 0.5f * D;

			area += triangleArea;

			// Use area to weight the centroid average, not just vertex position
			c += triangleArea * k_inv3 * (p1 + p2);

			real intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
			real inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;
			I += (0.25f * k_inv3 * D) * (intx2 + inty2);
		}

		c *= 1.0f / area;

		// Translate vertices to centroid (make the centroid (0, 0)
		// for the polygon in model space)
		// Not really necessary, but I like doing this anyway
		for (uint32_t i = 0; i < m_vertexCount; ++i)
			m_vertices[i] -= c;

		body->m = density * area;
		body->im = (body->m) ? 1.0f / body->m : 0.0f;
		body->I = I * density;
		body->iI = body->I ? 1.0f / body->I : 0.0f;
	}

	void setOrient(real radians)
	{
		u.set(radians);
	}

	void Draw(void) const
	{
		/*
		glColor3f(body->r, body->g, body->b);
		glBegin(GL_LINE_LOOP);
		for (uint32 i = 0; i < m_vertexCount; ++i)
		{
			Vec2 v = body->position + u * m_vertices[i];
			glVertex2f(v.x, v.y);
		}
		glEnd();
		*/
	}

	Type getType(void) const
	{
		return ePoly;
	}

	// Half width and half height
	void setBox(real hw, real hh)
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

	void set(GVec2 *vertices, uint32_t count)
	{
		// No hulls with less than 3 vertices (ensure actual polygon)
		assert(count > 2 && count <= MaxPolyVertexCount);
		count = MIN((uint32_t)count, MaxPolyVertexCount);

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
	GVec2 GetSupport(const GVec2& dir)
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

	uint32_t m_vertexCount;
	GVec2 m_vertices[MaxPolyVertexCount];
	GVec2 m_normals[MaxPolyVertexCount];
};
