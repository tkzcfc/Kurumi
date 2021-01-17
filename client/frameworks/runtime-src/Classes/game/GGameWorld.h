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

#if G_TARGET_CLIENT
	bool init(int mapId, Node* rootNode);
#else
	bool init(int mapId);
#endif
	
	void updateLogic(float32 dt);

	void render();

private:
	
	// 初始化世界边界碰撞
	bool initBorder();

	bool initAdmin(int mapId);

	bool initTest();

	bool initPlayer();

	bool spawnPlayer();

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

	DrawNode* m_debugDrawNode;
	Node* m_rootNode;
	GVirtualCamera* m_camera;
#endif

	std::vector<anax::Entity> m_players;
};

