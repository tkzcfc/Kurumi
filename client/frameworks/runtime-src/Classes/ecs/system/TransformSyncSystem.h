#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/components/ArmatureComponent.h"
#include "ecs/components/SIMPhysComponent.h"

class TransformSyncSystem : public anax::System<anax::Requires<TransformComponent, SIMPhysComponent>>
{
public:

	void sync();
};

DEFINE_SYSTEM(TransformSyncSystem);
