#pragma once

#include "ecs/anaxHelper.h"


class UniqueComponent : public anax::Component
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

DEFINE_COMPONENT(UniqueComponent);



