#include "GShape.h"

NS_G_BEGIN

static GFixedTransform zeroTransform;

GShape::GShape()
	: m_type(ECollisionType::NONE)
	, m_body(NULL)
	, m_boundingBoxDirty(true)
{}

GShape::~GShape()
{}

void GShape::boundingBoxDirty()
{
	m_boundingBoxDirty = true;
}

bool GShape::intersects(GShape* other)
{
	if (this->m_boundingBoxDirty)
	{
		this->updateAABB();
		this->m_boundingBoxDirty = false;
	}

	if (other->m_boundingBoxDirty)
	{
		other->updateAABB();
		other->m_boundingBoxDirty = false;
	}

	if (!aabbTest(other->getAABB()))
		return false;

	auto dispatch = GCollisionFunc::dispatch[this->getType()][other->getType()];

	if (m_body == NULL && other->getBody() == NULL)
	{
		return dispatch(this, other, zeroTransform, zeroTransform);

	}
	else if (m_body == NULL)
	{
		return dispatch(this, other, zeroTransform, other->getBody()->transform);
	}
	else if (other->getBody() == NULL)
	{
		return dispatch(this, other, this->getBody()->transform, zeroTransform);
	}
	else
	{
		return dispatch(this, other, this->getBody()->transform, other->getBody()->transform);
	}
}

bool GShape::aabbTest(const GFixedRect& rect) const
{
	return m_aabb.intersectsRect(rect);
}

NS_G_END
