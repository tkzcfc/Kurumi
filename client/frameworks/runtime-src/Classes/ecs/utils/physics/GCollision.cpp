/*
    Copyright (c) 2013 Randy Gaul http://RandyGaul.net

    This software is provided 'as-is', without any express or implied
    warranty. In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:
      1. The origin of this software must not be misrepresented; you must not
         claim that you wrote the original software. If you use this software
         in a product, an acknowledgment in the product documentation would be
         appreciated but is not required.
      2. Altered source versions must be plainly marked as such, and must not be
         misrepresented as being the original software.
      3. This notice may not be removed or altered from any source distribution.
*/

#include "GCollision.h"
#include "GManifold.h"
#include "ecs/components/BodyComponent.h"

CollisionCallback GCollision::Dispatch[GShape::eCount][GShape::eCount] ={
  {
	GCollision::circletoCircle, GCollision::circletoPolygon
  },
  {
	GCollision::polygontoCircle, GCollision::polygontoPolygon
  },
};

//////////////////////////////////////////////////////////////////////////

static inline bool biasGreaterThan(real a, real b)
{
	const real k_biasRelative = 0.95f;
	const real k_biasAbsolute = 0.01f;
	return a >= b * k_biasRelative + a * k_biasAbsolute;
}


static bool GameMath_Tmp(const GVec2& IS, const GVec2* A, const GVec2* B)
{
	float v[4];
	for (int i = 0; i < 4; i++)
	{
		float tmp = (IS.x * A[i].x + IS.y * A[i].y) / (IS.x * IS.x + IS.y * IS.y);
		v[i] = tmp * IS.x * IS.x + tmp * IS.y * IS.y;
	}
	float vv[4];
	for (int i = 0; i < 4; i++)
	{
		float tmp = (IS.x * B[i].x + IS.y * B[i].y) / (IS.x * IS.x + IS.y * IS.y);
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

//////////////////////////////////////////////////////////////////////////

void GCollision::circletoCircle(GManifold *m)
{
	GCircle *A = reinterpret_cast<GCircle *>(m->bodyA->shape);
	GCircle *B = reinterpret_cast<GCircle *>(m->bodyB->shape);
	
	// Calculate translational vector, which is normal
	GVec2 normal = m->bodyB->position - m->bodyA->position;
	
	real dist_sqr = normal.lenSqr( );
	real radius = A->radius + B->radius;
	
	// Not in contact
	if(dist_sqr >= radius * radius)
	{
	  m->contact_count = 0;
	  return;
	}
	
	real distance = std::sqrt( dist_sqr );
	
	m->contact_count = 1;
	
	if(distance == 0.0f)
	{
		m->penetration = A->radius;
		m->normal = GVec2( 1, 0 );
		m->contacts[0] = m->bodyA->position;
	}
	else
	{
		m->penetration = radius - distance;
		m->normal = normal / distance; // Faster than using Normalized since we already performed sqrt
		m->contacts[0] = m->normal * A->radius + m->bodyA->position;
	}
}

static void circletoPolygonEx(GManifold *m, BodyComponent* bodyA, BodyComponent* bodyB)
{
	GCircle *A = reinterpret_cast<GCircle*>(bodyA->shape);
	GPolygonShape *B = reinterpret_cast<GPolygonShape*>(bodyB->shape);

	m->contact_count = 0;

	// Transform circle center to Polygon model space
	GVec2 center = bodyA->position;
	center = B->u.transpose() * (center - bodyB->position);

	// Find edge with minimum penetration
	// Exact concept as using support points in Polygon vs Polygon
	real separation = -FLT_MAX;
	uint32_t faceNormal = 0;
	for (uint32_t i = 0; i < B->m_vertexCount; ++i)
	{
		real s = dot(B->m_normals[i], center - B->m_vertices[i]);

		if (s > A->radius)
			return;

		if (s > separation)
		{
			separation = s;
			faceNormal = i;
		}
	}

	// Grab face's vertices
	GVec2 v1 = B->m_vertices[faceNormal];
	uint32_t i2 = faceNormal + 1 < B->m_vertexCount ? faceNormal + 1 : 0;
	GVec2 v2 = B->m_vertices[i2];

	// Check to see if center is within polygon
	if (separation < G_EPSILON)
	{
		m->contact_count = 1;
		m->normal = -(B->u * B->m_normals[faceNormal]);
		m->contacts[0] = m->normal * A->radius + bodyA->position;
		m->penetration = A->radius;
		return;
	}

	// Determine which voronoi region of the edge center of circle lies within
	real dot1 = dot(center - v1, v2 - v1);
	real dot2 = dot(center - v2, v1 - v2);
	m->penetration = A->radius - separation;

	// Closest to v1
	if (dot1 <= 0.0f)
	{
		if (distSqr(center, v1) > A->radius * A->radius)
			return;

		m->contact_count = 1;
		GVec2 n = v1 - center;
		n = B->u * n;
		n.normalize();
		m->normal = n;
		v1 = B->u * v1 + bodyB->position;
		m->contacts[0] = v1;
	}

	// Closest to v2
	else if (dot2 <= 0.0f)
	{
		if (distSqr(center, v2) > A->radius * A->radius)
			return;

		m->contact_count = 1;
		GVec2 n = v2 - center;
		v2 = B->u * v2 + bodyB->position;
		m->contacts[0] = v2;
		n = B->u * n;
		n.normalize();
		m->normal = n;
	}

	// Closest to face
	else
	{
		GVec2 n = B->m_normals[faceNormal];
		if (dot(center - v1, n) > A->radius)
			return;

		n = B->u * n;
		m->normal = -n;
		m->contacts[0] = m->normal * A->radius + bodyA->position;
		m->contact_count = 1;
	}
}


void GCollision::circletoPolygon(GManifold *m)
{
	circletoPolygonEx(m, m->bodyA, m->bodyB);
}

void GCollision::polygontoCircle(GManifold *m)
{
	circletoPolygonEx(m, m->bodyB, m->bodyA);
	m->normal = -m->normal;
}

real FindAxisLeastPenetration(uint32_t *faceIndex, GPolygonShape* A, GPolygonShape* B)
{
	real bestDistance = -FLT_MAX;
	uint32_t bestIndex;
	
	for(uint32_t i = 0; i < A->m_vertexCount; ++i)
	{
		// Retrieve a face normal from A
		GVec2 n = A->m_normals[i];
		GVec2 nw = A->u * n;
		
		// Transform face normal into B's model space
		GMat2 buT = B->u.transpose( );
		n = buT * nw;
		
		// Retrieve support point from B along -n
		GVec2 s = B->GetSupport( -n );
		
		// Retrieve vertex on face from A, transform into
		// B's model space
		GVec2 v = A->m_vertices[i];
		v = A->u * v + A->body->position;
		v -= B->body->position;
		v = buT * v;
		
		// Compute penetration distance (in B's model space)
		real d = dot( n, s - v );
		
		// Store greatest distance
		if(d > bestDistance)
		{
			bestDistance = d;
			bestIndex = i;
		}
	}
	
	*faceIndex = bestIndex;
	return bestDistance;
}

void FindIncidentFace(GVec2 *v, GPolygonShape *RefPoly, GPolygonShape *IncPoly, uint32_t referenceIndex )
{
	GVec2 referenceNormal = RefPoly->m_normals[referenceIndex];

	// Calculate normal in incident's frame of reference
	referenceNormal = RefPoly->u * referenceNormal; // To world space
	referenceNormal = IncPoly->u.transpose() * referenceNormal; // To incident's model space

	// Find most anti-normal face on incident polygon
	int32_t incidentFace = 0;
	real minDot = FLT_MAX;
	for (uint32_t i = 0; i < IncPoly->m_vertexCount; ++i)
	{
		real dotv = dot(referenceNormal, IncPoly->m_normals[i]);
		if (dotv < minDot)
		{
			minDot = dotv;
			incidentFace = i;
		}
	}

	// Assign face vertices for incidentFace
	v[0] = IncPoly->u * IncPoly->m_vertices[incidentFace] + IncPoly->body->position;
	incidentFace = incidentFace + 1 >= (int32_t)IncPoly->m_vertexCount ? 0 : incidentFace + 1;
	v[1] = IncPoly->u * IncPoly->m_vertices[incidentFace] + IncPoly->body->position;
}

int32_t Clip(GVec2 n, real c, GVec2 *face )
{
	uint32_t sp = 0;
	GVec2 out[2] = {
	  face[0],
	  face[1]
	};

	// Retrieve distances from each endpoint to the line
	// d = ax + by - c
	real d1 = dot(n, face[0]) - c;
	real d2 = dot(n, face[1]) - c;

	// If negative (behind plane) clip
	if (d1 <= 0.0f) out[sp++] = face[0];
	if (d2 <= 0.0f) out[sp++] = face[1];

	// If the points are on different sides of the plane
	if (d1 * d2 < 0.0f) // less than to ignore -0.0f
	{
		// Push interesection point
		real alpha = d1 / (d1 - d2);
		out[sp] = face[0] + alpha * (face[1] - face[0]);
		++sp;
	}

	// Assign our new converted values
	face[0] = out[0];
	face[1] = out[1];

	assert(sp != 3);

	return sp;
}


void GCollision::polygontoPolygon(GManifold *m)
{
	GPolygonShape *A = reinterpret_cast<GPolygonShape *>(m->bodyA->shape);
	GPolygonShape *B = reinterpret_cast<GPolygonShape *>(m->bodyB->shape);
	m->contact_count = 0;

	// Check for a separating axis with A's face planes
	uint32_t faceA;
	real penetrationA = FindAxisLeastPenetration(&faceA, A, B);
	if (penetrationA >= 0.0f)
		return;

	// Check for a separating axis with B's face planes
	uint32_t faceB;
	real penetrationB = FindAxisLeastPenetration(&faceB, B, A);
	if (penetrationB >= 0.0f)
		return;

	uint32_t referenceIndex;
	bool flip; // Always point from a to b

	GPolygonShape *RefPoly; // Reference
	GPolygonShape *IncPoly; // Incident

	// Determine which shape contains reference face
	if (biasGreaterThan(penetrationA, penetrationB))
	{
		RefPoly = A;
		IncPoly = B;
		referenceIndex = faceA;
		flip = false;
	}
	else
	{
		RefPoly = B;
		IncPoly = A;
		referenceIndex = faceB;
		flip = true;
	}

	// World space incident face
	GVec2 incidentFace[2];
	FindIncidentFace(incidentFace, RefPoly, IncPoly, referenceIndex);

	//        y
	//        ^  ->n       ^
	//      +---c ------posPlane--
	//  x < | i |\
	//      +---+ c-----negPlane--
	//             \       v
	//              r
	//
	//  r : reference face
	//  i : incident poly
	//  c : clipped point
	//  n : incident normal

	// Setup reference face vertices
	GVec2 v1 = RefPoly->m_vertices[referenceIndex];
	referenceIndex = referenceIndex + 1 == RefPoly->m_vertexCount ? 0 : referenceIndex + 1;
	GVec2 v2 = RefPoly->m_vertices[referenceIndex];

	// Transform vertices to world space
	v1 = RefPoly->u * v1 + RefPoly->body->position;
	v2 = RefPoly->u * v2 + RefPoly->body->position;

	// Calculate reference face side normal in world space
	GVec2 sidePlaneNormal = (v2 - v1);
	sidePlaneNormal.normalize();

	// Orthogonalize
	GVec2 refFaceNormal(sidePlaneNormal.y, -sidePlaneNormal.x);

	// ax + by = c
	// c is distance from origin
	real refC = dot(refFaceNormal, v1);
	real negSide = -dot(sidePlaneNormal, v1);
	real posSide = dot(sidePlaneNormal, v2);

	// Clip incident face to reference face side planes
	if (Clip(-sidePlaneNormal, negSide, incidentFace) < 2)
		return; // Due to floating point error, possible to not have required points

	if (Clip(sidePlaneNormal, posSide, incidentFace) < 2)
		return; // Due to floating point error, possible to not have required points

	  // Flip
	m->normal = flip ? -refFaceNormal : refFaceNormal;

	// Keep points behind reference face
	uint32_t cp = 0; // clipped points behind reference face
	real separation = dot(refFaceNormal, incidentFace[0]) - refC;
	if (separation <= 0.0f)
	{
		m->contacts[cp] = incidentFace[0];
		m->penetration = -separation;
		++cp;
	}
	else
		m->penetration = 0;

	separation = dot(refFaceNormal, incidentFace[1]) - refC;
	if (separation <= 0.0f)
	{
		m->contacts[cp] = incidentFace[1];

		m->penetration += -separation;
		++cp;

		// Average penetration
		m->penetration /= (real)cp;
	}

	m->contact_count = cp;
}


/// 检测2个矩形是否相交
bool GCollision::isRectIntersect(const GVec2* A, const GVec2* B)
{
	static GVec2 Ax, Ay, Bx, By;

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
