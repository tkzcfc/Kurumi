#include "GCollisionFrame.h"
#include "mugen/collision/GCollision.h"
#include "mugen/act/GAct.h"
#include "mugen/component/GActorComponent.h"

NS_G_BEGIN

GCollisionFrame::GCollisionFrame()
	: m_shape(NULL)
{
	m_type = GFrameType::ATT_COLLISION_FRAME;
}

GCollisionFrame::~GCollisionFrame()
{
	setShape(NULL);
}

void GCollisionFrame::onUpdate(int32_t currentFrameIndex)
{
	GFrame::onUpdate(currentFrameIndex);

	if (m_shape == NULL) return;

	if (m_shape->getBody() == NULL)
	{
		auto actorComponent = m_timeline->getTrack()->getSkill()->getActorComponent();
		m_shape->setBody(actorComponent);
	}
	m_shape->boundingBoxDirty();
}

void GCollisionFrame::serialize(GByteBuffer& byteBuffer)
{
	GFrame::serialize(byteBuffer);

	if (m_shape)
	{
		byteBuffer.writeInt32(m_shape->getType());
		m_shape->serialize(byteBuffer);
	}
}

bool GCollisionFrame::deserialize(GByteBuffer& byteBuffer)
{
	setShape(NULL);
	do
	{
		G_BREAK_IF(!GFrame::deserialize(byteBuffer));
				
		int32_t type;
		G_BREAK_IF(!byteBuffer.getInt32(type));

		GShape* shape = NULL;
		if (type == ECollisionType::RECT_AABB)
		{
			shape = new GShapeAABB();
		}
		else if (type == ECollisionType::POLYGON)
		{
			shape = new GShapePolygon();
		}
		else if (type == ECollisionType::CIRCLE)
		{
			shape = new GShapeCircle();
		}

		if (shape == NULL)
		{
			G_ASSERT(0);
			break;
		}

		if (shape->deserialize(byteBuffer))
		{
			setShape(shape);
			return true;
		}
		else
		{
			delete shape;
		}
	} while (0);
	return false;
}


void GCollisionFrame::setShape(GShape* shape)
{
	if (m_shape)
	{
		delete m_shape;
		m_shape = NULL;
	}
	m_shape = shape;
}

GShape* GCollisionFrame::getShape()
{
	return m_shape;
}

bool GCollisionFrame::intersects(GCollisionFrame* other)
{
	if (m_shape && other->m_shape)
	{
		return m_shape->intersects(other->m_shape);
	}
	return false;
}

NS_G_END
