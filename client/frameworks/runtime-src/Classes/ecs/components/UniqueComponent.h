#pragma once

#include "ecs/anaxHelper.h"


class UniqueComponent : public BaseComponent
{
public:
	UniqueComponent()
	{
	}

#if G_TARGET_SERVER

#else
	cocos2d::Node* stageNode;
	cocos2d::Node* mapNode;
#endif
};
