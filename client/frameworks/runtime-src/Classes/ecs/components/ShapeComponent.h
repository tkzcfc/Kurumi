#pragma once

#include "ecs/anaxHelper.h"

#define MaxPolyVertexCount 64


class CircleComponent : public anax::Component
{
public:

	float32 radius;
	GMat2 u;
};


class PolygonComponent : public anax::Component
{
public:

	uint32_t m_vertexCount;
	GVec2 m_vertices[MaxPolyVertexCount];
	GVec2 m_normals[MaxPolyVertexCount];
};