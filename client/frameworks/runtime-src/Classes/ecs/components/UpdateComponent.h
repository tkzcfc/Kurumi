#pragma once

#include "ecs/anaxHelper.h"
#include "lua_function/LuaFunction.h"


class UpdateComponent : public anax::Component, public Ref
{
public:
	UpdateComponent() 
	{}
	virtual ~UpdateComponent()
	{}

	LuaFunction m_updateCall;
	LuaFunction m_lastUpdateCall;
};

DEFINE_COMPONENT(UpdateComponent);
