#include "GShapePolygon.h"

NS_G_BEGIN

static GFixedVec2 vertexs_cache[MAX_POLY_VERTEX_COUNT];

GShapePolygon::GShapePolygon()
	: m_count(0)
{
	m_type = ECollisionType::POLYGON;
}

GShapePolygon::~GShapePolygon()
{}

void GShapePolygon::updateAABB()
{
	if (this->getBody() == NULL)
	{
		for (auto i = 0; i < m_count; ++i)
		{
			vertexs_cache[i] = m_vertexs[i];
		}
	}
	else
	{
		const auto& transform = this->getBody()->transform;

		for (auto i = 0; i < m_count; ++i)
		{
			mulT_quick(transform, m_vertexs[i], vertexs_cache[i]);
		}
	}
	m_aabb.minx = vertexs_cache[0].x;
	m_aabb.maxx = vertexs_cache[0].x;
	m_aabb.miny = vertexs_cache[0].y;
	m_aabb.maxy = vertexs_cache[0].y;

	for (int i = 1; i < m_count; i++)
	{
		auto q = vertexs_cache + i;
		m_aabb.minx = MIN(q->x, m_aabb.minx);
		m_aabb.maxx = MAX(q->x, m_aabb.maxx);
		m_aabb.miny = MIN(q->y, m_aabb.miny);
		m_aabb.maxy = MAX(q->y, m_aabb.maxy);
	}
}

void GShapePolygon::serialize(GByteBuffer& byteBuffer)
{
	GShape::serialize(byteBuffer);
	byteBuffer.writeUint32(m_count);
	for (auto i = 0; i < m_count; ++i)
	{
		byteBuffer.writeFixedPoint(m_vertexs[i].x);
		byteBuffer.writeFixedPoint(m_vertexs[i].y);
	}
}

bool GShapePolygon::deserialize(GByteBuffer& byteBuffer)
{
	do
	{
		G_BREAK_IF(!GShape::deserialize(byteBuffer));

		G_BREAK_IF(!byteBuffer.getUint32(m_count));

		G_ASSERT(m_count > 2);
		G_ASSERT(m_count <= MAX_POLY_VERTEX_COUNT);

		G_BREAK_IF(m_count > MAX_POLY_VERTEX_COUNT);
		
		bool ok = true;
		for (auto i = 0; i < m_count; ++i)
		{
			if (!byteBuffer.getFixedPoint(m_vertexs[i].x))
			{
				ok = false;
				break;
			}
			if(!byteBuffer.getFixedPoint(m_vertexs[i].y))
			{
				ok = false;
				break;
			}
		}
		return ok;
	} while (0);
	return false;
}

void GShapePolygon::set(GFixedVec2* vertices, uint32_t count)
{
	G_ASSERT(count > 2);
	G_ASSERT(count <= MAX_POLY_VERTEX_COUNT);

	m_count = count;

	for (auto i = 0; i < count; ++i)
	{
		m_vertexs[i] = vertices[i];
	}
}

NS_G_END
