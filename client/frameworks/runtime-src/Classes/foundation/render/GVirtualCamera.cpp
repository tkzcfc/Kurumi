#include "GVirtualCamera.h"


GVirtualCamera * GVirtualCamera::create()
{
	GVirtualCamera * ret = new (std::nothrow) GVirtualCamera();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

GVirtualCamera::GVirtualCamera()
	: m_animationNode(NULL)
	, m_enableCollision(false)
	, m_cameraAnchorPoint(Vec2::ANCHOR_MIDDLE)
{
}

bool GVirtualCamera::init()
{
	if (!Component::init())
	{
		return false;
	}

	m_viewSize = Director::getInstance()->getVisibleSize();
	setWorldSize(m_viewSize);

	return true;
}

void GVirtualCamera::setPosition(const Vec2& pos)
{
	if (m_animationNode)
	{
		m_animationNode->setPosition(pos);
	}
}

const Vec2& GVirtualCamera::getPosition()
{
	if (m_animationNode == NULL)
	{
		return Vec2::ZERO;
	}
	return m_animationNode->getPosition();
}

const Vec2& GVirtualCamera::getCenter()
{
	static Vec2 outCenter;

	outCenter = this->getPosition();
	outCenter.x = outCenter.x + m_viewSize.width * 0.5f;
	outCenter.y = outCenter.y + m_viewSize.height * 0.5f;

	return outCenter;
}

void GVirtualCamera::setViewPortSize(const Size& viewSize)
{
	m_viewSize = viewSize;
	setCameraBoundingBox(Vec2::ZERO, m_worldSize);
}

void GVirtualCamera::setWorldSize(const Size& worldSize)
{
	m_worldSize = worldSize;
	setCameraBoundingBox(Vec2::ZERO, worldSize);
}

Vec2 GVirtualCamera::validPosition(Vec2& pos)
{
	validPositionFast(pos);
	return pos;
}

void GVirtualCamera::setCameraBoundingBox(const Vec2& min, const Vec2& max)
{
	m_cameraBoundingBoxMin = min;
	m_cameraBoundingBoxMax = max - m_viewSize;
}

void GVirtualCamera::setEnableCollision(bool enable)
{
	m_enableCollision = enable;
}

bool GVirtualCamera::isEnableCollision()
{
	return m_enableCollision;
}

void GVirtualCamera::validPositionFast(Vec2& pos)
{
	if (m_enableCollision == false)
	{
		return;
	}

	pos.x = MAX(pos.x, m_cameraBoundingBoxMin.x);
	pos.x = MIN(pos.x, m_cameraBoundingBoxMax.x);
	pos.y = MAX(pos.y, m_cameraBoundingBoxMin.y);
	pos.y = MIN(pos.y, m_cameraBoundingBoxMax.y);
}

void GVirtualCamera::setCameraAnchorPoint(const Vec2& anchorPoint)
{
	m_cameraAnchorPoint = anchorPoint;
}

Node* GVirtualCamera::getAnimationNode()
{
	return m_animationNode;
}

void GVirtualCamera::forceUpdate()
{
	update(0.0f);
}

void GVirtualCamera::update(float delta)
{
	Component::update(delta);

	if (m_animationNode == NULL)
	{
		return;
	}

	Vec2 pos = m_animationNode->getPosition();
	float scale = m_animationNode->getScale();

	validPositionFast(pos);

	m_animationNode->setPosition(pos);

	if (m_cache_Position == pos && m_cache_Scale == scale)
	{
		return;
	}

	m_cache_Position = pos;
	m_cache_Scale = scale;
	
	pos *= scale;

	if (scale != 1.0f)
	{
		Vec2 v = (1.0f - scale) * m_viewSize;
		pos.x = pos.x - v.x * m_cameraAnchorPoint.x;
		pos.y = pos.y - v.y * m_cameraAnchorPoint.y;
	}

	m_call(pos.x, pos.y, scale);
}

void GVirtualCamera::onAdd()
{
	Component::onAdd();

	m_animationNode = Node::create();
	getOwner()->addChild(m_animationNode);
	CC_SAFE_RETAIN(m_animationNode);
}

void GVirtualCamera::onRemove()
{
	if (m_animationNode)
	{
		m_animationNode->removeFromParent();
		CC_SAFE_RELEASE_NULL(m_animationNode);
	}

	Component::onRemove();
}

