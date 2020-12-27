#pragma once

#include "ecs/system/ArmatureDebugSystem.h"
#include "ecs/system/ArmatureRenderSystem.h"
#include "ecs/system/ArmatureSystem.h"
#include "ecs/system/CollisionSystem.h"
#include "ecs/system/GlobalSystem.h"
#include "ecs/system/PhysicsSystem.h"
#include "ecs/system/SIMPhysSystem.h"
#include "ecs/system/TransformSyncSystem.h"

class GGameWorld
{
public:

	GGameWorld();

	void init();

#if G_TARGET_CLIENT
	void initRender(Node* rootNode);
#endif

	void updateLogic(float32 dt);

	void render();

private:

	anax::World m_world;

	ArmatureSystem m_armatureSystem;
	CollisionSystem m_collisionSystem;
	GlobalSystem m_globalSystem;
	SIMPhysSystem m_SIMPhysSystem;
	TransformSyncSystem m_transformSyncSystem;

#if G_TARGET_CLIENT
	ArmatureDebugSystem m_armatureDebugSystem;
	ArmatureRenderSystem m_armatureRenderSystem;
#endif
};

