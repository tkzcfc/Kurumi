#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/UniqueComponent.h"

// 演员身份信息
struct ActorIdentityInfo
{
	// 身体尺寸
	GVec2 bodySize;
	// 出生点
	GVec2 originPos;
	// 角色名
	std::string roleName;
};

class CommonUtils
{
public:

	static anax::Entity& getAdmin(anax::World& world);

	static bool initMapSize(anax::Entity& admin, int mapId);

#if G_TARGET_CLIENT
	static DrawNode* getDebugDraw(anax::World& world);
#endif

	// 演员创建
	static bool spawnActor(anax::World& world, ActorIdentityInfo& info, anax::Entity* outActor);

};
