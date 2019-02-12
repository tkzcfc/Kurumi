#pragma once

#include "ecs/components/ArmatureComponent.h"
#include "ecs/components/Box2DComponent.h"

class ArmatureCollisionComponentUtil
{
public:

	static void bindAttCallback(ArmatureCollisionComponent* component, const LuaFunction& handle);

	static void bindDefCallback(ArmatureCollisionComponent* component, const LuaFunction& handle);

	static void clearAttCallback(ArmatureCollisionComponent* component);

	static void clearDefCallback(ArmatureCollisionComponent* component);
};

class Box2DComponentUtil
{
public:

	static void bindSyncPhysicsTransformCallback(Box2DComponent* component, const LuaFunction& handle);

	static void clearSyncPhysicsTransformCallback(Box2DComponent* component);

};

