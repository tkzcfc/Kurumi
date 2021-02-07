#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/ArmatureComponent.h"

class CollisionSystem : public anax::System<anax::Requires<ArmatureComponent>>
{
public:

	void update();

	GAnimationData* getAnimData(ArmatureComponent& component);
};
