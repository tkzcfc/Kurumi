#pragma once

#include "mugen/base/GEntityManager.h"
#include "mugen/GGameDef.h"
#include "mugen/algorithm/GRandom.h"

#include "lua_function/LuaFunctionBond.h"

#include "render/GMapLayer.h"
#include "system/GPhysSystem.h"
#include "system/GCollisionSystem.h"
#include "system/GInputSystem.h"

NS_G_BEGIN

class GGameWorld : public LuaFunctionBond
{
public:

	GGameWorld();

	~GGameWorld();

	static GGameWorld* getInstance();

	static GGameWorld* create(int32_t mapId, uint32_t randomSeed, Node* rootNode);

	bool init(int32_t mapId, uint32_t randomSeed, Node* rootNode);

	void step();

	void render(float dt);

	void input(uint32_t entityId, uint32_t frame, G_BIT_TYPE keydown);
	
	GEntity* spwanActor(const std::string& filename, const GFixedVec3& pos);

	// 设置启用debug draw
	void enableDebugDraw(bool enable);

	// 设置使用GameWorld的定时器
	void setScheduler(Node* node, bool recursive = true);
	
private:

	bool initMapInfo(int32_t mapId);

private:

	G_SYNTHESIZE_READONLY(Scheduler*, m_pScheduler, Scheduler);
	// 地图层
	G_SYNTHESIZE_READONLY(GMapLayer*, m_pMapLayer, MapLayer);
	// 根节点
	G_SYNTHESIZE_READONLY(Node*, m_pRootNode, RootNode);
	// 实体管理器
	G_SYNTHESIZE_READONLY(GEntityManager*, m_pEntityManager, EntityManager);

	// 随机数生成器
	G_SYNTHESIZE_READONLY(GRandom*, m_pRandom, Random);

	////////////////////////////////////// system //////////////////////////////////////
	// 物理系统模拟
	G_SYNTHESIZE_REF_PTR(GPhysSystem, m_physSystem, PhysSystem);
	// 碰撞系统
	G_SYNTHESIZE_REF_PTR(GCollisionSystem, m_collisionSystem, CollisionSystem);
	// 输入系统
	G_SYNTHESIZE_REF_PTR(GInputSystem, m_inputSystem, InputSystem);

	///! 帧同步相关
	// 累计运行时间
	G_SYNTHESIZE_READONLY(fixedPoint, m_fAccumilatedTime, AccumilatedTime);
	// 游戏逻辑帧数
	G_SYNTHESIZE_READONLY(uint32_t, m_gameLogicFrame, GameLogicFrame);

	bool m_enableDebugDraw;
	
	static GGameWorld* sGameWorldInstance;
};

NS_G_END
