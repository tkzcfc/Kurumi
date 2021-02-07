#pragma once

#include "ecs/anaxHelper.h"


class GlobalComponent : public BaseComponent
{
public:
	GlobalComponent()
	{
		fAccumilatedTime = 0.0f;
		fNextGameTime = 0.0f;
		gameLogicFrame = 0U;
	}

#if G_TARGET_SERVER

#else
	cocos2d::Node* stageNode;
	cocos2d::Node* mapNode;
#endif


	// 累计运行时间
	float32 fAccumilatedTime;
	// 下一个逻辑帧时间
	float32 fNextGameTime;
	// 游戏逻辑帧数
	uint32_t gameLogicFrame;
};
