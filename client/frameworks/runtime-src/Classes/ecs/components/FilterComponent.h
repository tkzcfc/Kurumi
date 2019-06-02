#pragma once

#include "ecs/anaxHelper.h"
#include "cocos2d.h"
#include "lua_function/LuaFunction.h"

using namespace cocos2d;

class Actor;
class FilterComponent : public anax::Component, public Ref
{
public:
	FilterComponent()
	{}

	virtual ~FilterComponent()
	{}

	Actor* m_owner;

	int m_filterData;
};

DEFINE_COMPONENT(FilterComponent);
