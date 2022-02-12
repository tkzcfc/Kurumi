#include "GShapeAABB.h"

NS_G_BEGIN

GShapeAABB::GShapeAABB()
{
	m_type = ECollisionType::RECT_AABB;
}

GShapeAABB::~GShapeAABB()
{}

bool GShapeAABB::deserialize(GByteBuffer& byteBuffer)
{
	if (!GShapePolygon::deserialize(byteBuffer))
		return false;
	check();
	return true;
}

void GShapeAABB::set(GFixedVec2* vertices, uint32_t count)
{
	GShapePolygon::set(vertices, count);
	check();
}

void GShapeAABB::setRect(const GFixedVec2& pos, const GFixedVec2& size)
{
	GFixedVec2 v[4];
	v[0] = pos;

	v[1].x = pos.x;
	v[1].y = pos.y + size.y;

	v[2].x = pos.x + size.x;
	v[2].y = pos.y + size.y;

	v[3].x = pos.x + size.x;
	v[3].y = pos.y;

	set(v, 4);
}

void GShapeAABB::check()
{
	G_ASSERT(m_count == 4);

	int32_t count_x = 0;
	int32_t count_y = 0;
	GFixedVec2 v = m_vertexs[0];

	for (int i = 1; i < m_count; i++)
	{
		if (v.x == m_vertexs[i].x)
			count_x++;
		if (v.y == m_vertexs[i].y)
			count_y++;
	}
	G_ASSERT(count_y >= 1);
	G_ASSERT(count_x >= 1);
}

NS_G_END