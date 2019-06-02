#pragma once

#include "ecs/anaxHelper.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "lua_function/LuaFunction.h"

using namespace cocos2d;

class Box2DComponent : public anax::Component, public Ref
{
public:
	Box2DComponent()
	{}

	virtual ~Box2DComponent() 
	{
		if (m_body)
		{
			auto fixtureList = m_body->GetFixtureList();
			for (auto it = fixtureList; it != NULL; it = fixtureList->GetNext())
			{
				it->SetUserData(NULL);
			}
		}
	}

	b2Body* m_body;

	LuaFunction m_syncPhysicsTransformCall;
};

DEFINE_COMPONENT(Box2DComponent);
