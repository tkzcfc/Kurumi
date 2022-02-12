#include "GVirtualCamera.h"

NS_G_BEGIN

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
	: m_enableCollision(false)
	, m_zoom(1.0f)
	, m_anchorPoint(Vec2::ANCHOR_MIDDLE)
{
}

bool GVirtualCamera::init()
{
	if (!Component::init())
	{
		return false;
	}

	auto winSize = Director::getInstance()->getVisibleSize();
	m_viewSize = Vec2(winSize.width, winSize.height);
	setWorldSize(winSize);

	return true;
}

void GVirtualCamera::setViewPortSize(const Size& viewSize)
{
	m_viewSize = Vec2(viewSize.width, viewSize.height);
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

void GVirtualCamera::forceUpdate()
{
	update(0.0f);
}

void GVirtualCamera::update(float delta)
{
	Component::update(delta);

	Vec2 offset = m_viewSize;
	offset.scale(m_anchorPoint);

	Vec2 newPos = m_position - offset;
	validPositionFast(newPos);

	Vec2 diff = newPos - m_logicPos;
	if (diff.getLengthSq() < 0.001 && m_cache_Scale == m_zoom)
		return;

	float motion = MIN(1.0f, delta * 5.2f);
	diff.scale(motion);

	//// 防止镜头移动过快
	//if (diff.x < 0)
	//	diff.x = MAX(diff.x, -15.0f);
	//else
	//	diff.x = MIN(diff.x, 15.0f);

	m_logicPos += diff;
	newPos = m_logicPos;

	m_cache_Scale = m_zoom;
	
	newPos *= m_zoom;

	if (m_zoom != 1.0f)
	{
		Vec2 v = (1.0f - m_zoom) * m_viewSize;
		newPos.x = newPos.x - v.x * m_anchorPoint.x;
		newPos.y = newPos.y - v.y * m_anchorPoint.y;
	}

	m_call(newPos.x, newPos.y, m_zoom);
}

void GVirtualCamera::onAdd()
{
	Component::onAdd();
}

void GVirtualCamera::onRemove()
{
	Component::onRemove();
}

NS_G_END