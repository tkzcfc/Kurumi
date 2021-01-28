#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/components/ArmatureComponent.h"

class RenderSyncSystem : public anax::System<anax::Requires<TransformComponent, ArmatureRenderComponent>>
{
public:
	void sync();
};
