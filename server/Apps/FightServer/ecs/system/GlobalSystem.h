#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/GlobalComponent.h"

class GlobalSystem : public anax::System<anax::Requires<GlobalComponent>>
{
public:

	virtual void initialize()override;

	anax::Entity admin;
};
