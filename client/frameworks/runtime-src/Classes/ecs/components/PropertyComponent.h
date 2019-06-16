#pragma once

#include "ecs/anaxHelper.h"
#include "cocos2d.h"
#include "lua_function/LuaFunction.h"

using namespace cocos2d;

class Actor;
class PropertyComponent : public anax::Component, public Ref
{
public:
	PropertyComponent()
	{
		m_HP = 100;
	}

	virtual ~PropertyComponent()
	{}

	int m_HP;
};

DEFINE_COMPONENT(PropertyComponent);
