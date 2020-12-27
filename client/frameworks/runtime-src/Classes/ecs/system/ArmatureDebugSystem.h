#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/ArmatureComponent.h"
#include "ecs/components/TransformComponent.h"

class ArmatureDebugSystem : public anax::System<anax::Requires<ArmatureComponent, TransformComponent>>
{
public:

	void debugDraw();

};

DEFINE_SYSTEM(ArmatureDebugSystem);
