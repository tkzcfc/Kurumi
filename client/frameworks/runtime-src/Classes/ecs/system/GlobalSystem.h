#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/UniqueComponent.h"

class GlobalSystem : public anax::System<anax::Requires<UniqueComponent>>
{
public:

	virtual void initialize()override;

	anax::Entity admin;
};

DEFINE_SYSTEM(GlobalSystem);