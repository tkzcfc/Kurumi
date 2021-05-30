#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/GlobalComponent.h"

// 演员身份信息
struct ActorIdentityInfo
{
	// 身体尺寸
	GVec2 bodySize;
	// 出生点
	GVec2 originPos;
	// 角色名
	std::string roleName;
	// uuid
	GUUID uuid;
	// 动画状态机文件
	std::string anifsm;
	// 移动力
	GVec2 moveForce;
	// 跳跃冲力
	GVec2 jumpIm;

	// X最大移动速度
	float32 moveMaxVelocityX;
};


namespace CommonUtils
{
	anax::Entity& getAdmin(anax::World& world);

	GlobalComponent& getGlobalComponent(anax::World& world);

	bool initMapSize(anax::Entity& admin, int mapId);

#if G_TARGET_CLIENT
	DrawNode* getDebugDraw(anax::World& world);
#endif

	// 演员创建
	bool spawnActor(anax::World& world, ActorIdentityInfo& info, anax::Entity* outActor);

	GUUID genUUID(anax::World& world);

	bool queryUUID(anax::World& world, GUUID uuid, anax::Entity* pEntity = NULL);

	uint32_t U32_OR(uint32_t src, uint32_t dst);

	uint32_t U32_AND(uint32_t src, uint32_t dst);

	uint32_t U32_BIT_SET(uint32_t b, uint32_t flag);

	uint32_t U32_BIT_GET(uint32_t b, uint32_t flag);

	uint32_t U32_BIT_REMOVE(uint32_t b, uint32_t flag);

	bool U32_BIT_EQUAL(uint32_t b, uint32_t flag);

	bool U32_BIT_NO_EQUAL(uint32_t b, uint32_t flag);

	uint32_t U32_L_SHIFT(uint32_t src, uint32_t move);
}