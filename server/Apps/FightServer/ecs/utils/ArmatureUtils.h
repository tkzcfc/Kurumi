#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/ArmatureComponent.h"

struct GAnimationData;
class ArmatureUtils
{
public:

	static void getAllAnimationData(anax::World& world, std::vector<GAnimationData*>& outDatas);

	static void initAnimationComponent(anax::Entity& entity);

	static void changeRole(anax::Entity& entity, const std::string& roleName);

	static void playAnimationCMD(anax::Entity& entity, const std::string& cmdName, kArmaturePlayMode mode = kArmaturePlayMode::ONCE);
};
