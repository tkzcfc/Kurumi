#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/components/ArmatureComponent.h"

#if G_TARGET_SERVER
class TransformSyncSystem : public anax::System<anax::Requires<TransformComponent>>
#else
class TransformSyncSystem : public anax::System<anax::Requires<TransformComponent, ArmatureRenderComponent>>
#endif
{
public:

	void sync();

	void syncRender();
};

DEFINE_SYSTEM(TransformSyncSystem);
