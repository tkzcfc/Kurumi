#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/TransformComponent.h"

class InitSystem : public anax::System<anax::Requires<>>
{
public:
	void update();
};

DEFINE_SYSTEM(InitSystem);
