#include "GVirtualCamera.h"
#include "mugen/GGameDef.h"

NS_G_BEGIN

GVirtualCamera * GVirtualCamera::create()
{
	GVirtualCamera * ret = new (std::nothrow) GVirtualCamera();
	if (ret && ret->init())
	{
		return ret;
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

void GVirtualCamera::doUpdate(float delta)
{
	Vec2 offset = m_viewSize;
	offset.scale(m_anchorPoint);

	Vec2 validPos = m_position - offset;
	validPositionFast(validPos);


#if ENABLE_CAMERA_LERP
	auto newPos = m_logicPos.lerp(validPos, delta * 5);
#else
	// 逻辑帧率和渲染帧率不同时，使用摄像机跟随算法人物会抖动
	auto newPos = validPos;
#endif

	if (std::fabs(newPos.x - m_logicPos.x) < 0.001f && std::fabs(newPos.y - m_logicPos.y) < 0.001f && m_cache_Scale == m_zoom) 
	{
		return;
	}
	
	m_logicPos = newPos;
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

NS_G_END