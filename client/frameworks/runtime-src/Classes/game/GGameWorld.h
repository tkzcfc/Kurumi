#pragma once

#include "ecs/ECSDefine.h"
#include "ecs/utils/opmsg/GOPMsg.h"

class GGameWorld
{
public:

	GGameWorld();

	bool init(int32_t mapId, uint32_t randomSeed, uint32_t uuidSeed, Node* rootNode);
	
	void update(float32 dt);

	void input(GUUID uuid, uint32_t frame, G_BIT_TYPE keydown);

	void render();

public:

	G_FORCEINLINE uint32_t getGameLogicFrame() const;

private:

	// 逻辑更新
	void updateLogic(float32 dt);
	
	// 初始化世界边界碰撞
	bool initBorder();

	bool initAdmin(int32_t mapId);

	bool initPlayer();

	bool spawnPlayer();

private:

	// ecs world
	anax::World m_world;

	// admin
	GlobalComponent* m_pGlobal;

	// ecs 相关系统
	ArmatureSystem m_armatureSystem;
	CollisionSystem m_collisionSystem;
	GlobalSystem m_globalSystem;
	SIMPhysSystem m_SIMPhysSystem;
	TransformSyncSystem m_transformSyncSystem;
	InputSystem m_inputSystem;
	UpdateSystem m_updateSystem;
	BuffSystem m_buffSystem;
	SkillInjurySystem m_skillInjurySystem;
	UUIDSystem m_UUIDSystem;


	ArmatureDebugSystem m_armatureDebugSystem;
	ArmatureRenderSystem m_armatureRenderSystem;

	Node* m_rootNode;
	GVirtualCamera* m_camera;

	std::vector<anax::Entity> m_players;
};

uint32_t GGameWorld::getGameLogicFrame() const
{
	return m_pGlobal->gameLogicFrame;
}
