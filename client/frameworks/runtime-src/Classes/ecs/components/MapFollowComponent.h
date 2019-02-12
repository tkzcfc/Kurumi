#pragma once

#include "ecs/anaxHelper.h"
#include "cocos2d.h"

using namespace cocos2d;

class MapFollowComponent : public anax::Component, public Ref
{
public:
	MapFollowComponent()
		:m_owner(NULL)
	{}

	virtual ~MapFollowComponent()
	{}

	Node* m_owner;
};

DEFINE_COMPONENT(MapFollowComponent);
