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

	GUUID genUUID();

	bool queryUUID(anax::World& world, GUUID uuid, anax::Entity* pEntity = NULL);
}
