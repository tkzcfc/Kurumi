#pragma once

#include "ecs/anaxHelper.h"

class TransformComponent : public BaseComponent
{
public:
	TransformComponent()
		: scale(1.0f)
	{
	}

	// 渲染坐标
#if G_TARGET_SERVER
	GVec2 position;
#else
	Vec2 position;
#endif
	// 逻辑坐标
	GVec3 logicPos;
	// 缩放
	float32 scale;
};


