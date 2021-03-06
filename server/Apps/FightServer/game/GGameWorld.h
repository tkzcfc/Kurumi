#pragma once

#include "ecs/ECSDefine.h"

class GGameWorld
{
public:

	GGameWorld();

#if G_TARGET_CLIENT
	bool init(int32_t mapId, Node* rootNode);
#else
	bool init(int32_t mapId);
#endif
	
	void update(float32 dt);

	void input(const std::string& data);

	void render();

public:

	G_FORCEINLINE uint32_t getGameLogicFrame() const;

private:

	// 逻辑更新
	void updateLogic();
	
	// 初始化世界边界碰撞
	bool initBorder();

	bool initAdmin(int32_t mapId);

	bool initTest();

	bool initPlayer();

	bool spawnPlayer();

public:

	// 每一帧的时间长度
	static float32 GGameFrameLen;

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


#if G_TARGET_CLIENT
	ArmatureDebugSystem m_armatureDebugSystem;
	ArmatureRenderSystem m_armatureRenderSystem;

	Node* m_rootNode;
	GVirtualCamera* m_camera;
#endif
	
	std::vector<anax::Entity> m_players;
};

uint32_t GGameWorld::getGameLogicFrame() const
{
	return m_pGlobal->gameLogicFrame;
}
