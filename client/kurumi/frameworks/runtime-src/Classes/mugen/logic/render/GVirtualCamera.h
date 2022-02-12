#pragma once

#include "mugen/base/GObject.h"

USING_NS_CC;

NS_G_BEGIN

class GVirtualCamera : public cocos2d::Component
{
public:

	GVirtualCamera();

	static GVirtualCamera * create();
	
	// 设置视口大小
	void setViewPortSize(const Size& viewSize);

	// 设置世界大小
	void setWorldSize(const Size& worldSize);

	// 返回一个有效位置
	Vec2 validPosition(Vec2& pos);
	void validPositionFast(Vec2& pos);

	// 设置包围摄像机的包围盒 
	/*
								(max.x, max.y)
	-----------BoundingBox-------
	|							|
	|	 ---camera---			|
	|	 |			|			|
	|	 ------------			|
	|							|
	|---------------------------|
	(min.x, min.y)
	*/
	void setCameraBoundingBox(const Vec2& min, const Vec2& max);

	// 是否启用包围盒碰撞
	void setEnableCollision(bool enable);
	bool isEnableCollision();
	
	void forceUpdate();

	void setCall(const std::function<void(float, float, float)>& call)
	{
		m_call = call;
	}

public:

	virtual bool init()override;

	virtual void update(float delta)override;

	virtual void onAdd()override;

	virtual void onRemove()override;

public:
	// 摄像机坐标
	G_SYNTHESIZE_PASS_BY_REF(Vec2, m_position, Position);
	// 摄像机缩放
	G_SYNTHESIZE(float, m_zoom, Zoom);
	// 摄像机焦点锚点
	G_SYNTHESIZE_PASS_BY_REF(Vec2, m_anchorPoint, AnchorPoint);


	// 视口大小
	Vec2 m_viewSize;
	// 世界大小
	Size m_worldSize;
		
	// 是否开启摄像机边缘碰撞
	bool m_enableCollision;

	std::function<void(float, float, float)> m_call;

	// 摄像机边界碰撞体
	Vec2 m_cameraBoundingBoxMin;
	Vec2 m_cameraBoundingBoxMax;

private:
	Vec2 m_logicPos;
	float m_cache_Scale;
};

NS_G_END