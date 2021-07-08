#pragma once

#include "ecs/anaxHelper.h"

class TransformComponent : public BaseComponent
{
public:
	TransformComponent()
		: scaleX(1.0f)
		, scaleY(1.0f)
	{
	}

	// 实际渲染坐标
	Vec2 renderPos;
	// 逻辑渲染坐标
	Vec2 logicRenderPos;
	// 最后一帧逻辑帧实际渲染坐标
	Vec2 lastRenderPos;
	// 逻辑坐标
	GVec3 logicPos;
	// 缩放
	float32 scaleX;
	// 缩放
	float32 scaleY;
};


