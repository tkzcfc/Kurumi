#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/ArmatureComponent.h"
#include "ecs/components/TransformComponent.h"

#if  G_TARGET_SERVER
#else
class ArmatureDebugSystem : public anax::System<anax::Requires<ArmatureComponent, TransformComponent>>
{
public:

	void render(cocos2d::DrawNode* drawNode);

};


DEFINE_SYSTEM(ArmatureDebugSystem);
#endif
