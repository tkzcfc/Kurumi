#include "GShapeCircle.h"

NS_G_BEGIN

static GFixedVec2 cache_center;

GShapeCircle::GShapeCircle()
	: m_radius(1.0f)
{
	m_type = ECollisionType::CIRCLE;
}

GShapeCircle::~GShapeCircle()
{}

void GShapeCircle::updateAABB()
{
	if (this->getBody() == NULL)
	{
		cache_center = m_center;
	}
	else
	{
		const auto& transform = this->getBody()->transform;
		mulT_quick(transform, m_center, cache_center);
	}

	m_aabb.minx = cache_center.x - m_radius;
	m_aabb.maxx = cache_center.x + m_radius;
	m_aabb.miny = cache_center.y - m_radius;
	m_aabb.maxy = cache_center.y + m_radius;
}

void GShapeCircle::serialize(GByteBuffer& byteBuffer)
{
	GShape::serialize(byteBuffer);
	byteBuffer.writeFixedPoint(m_radius);
	byteBuffer.writeFixedPoint(m_center.x);
	byteBuffer.writeFixedPoint(m_center.y);
}

bool GShapeCircle::deserialize(GByteBuffer& byteBuffer)
{
	do
	{
		G_BREAK_IF(!GShape::deserialize(byteBuffer));

		G_BREAK_IF(!byteBuffer.getFixedPoint(m_radius));
		G_BREAK_IF(!byteBuffer.getFixedPoint(m_center.x));
		G_BREAK_IF(!byteBuffer.getFixedPoint(m_center.y));

		return true;
	} while (0);
	return false;
}

void GShapeCircle::set(const GFixedVec2& center, fixedPoint radius)
{
	G_ASSERT(radius >= 0.0f);
	m_center = center;
	m_radius = radius;
}

NS_G_END
