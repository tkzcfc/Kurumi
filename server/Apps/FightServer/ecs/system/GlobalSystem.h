#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/GlobalComponent.h"
#include "ecs/components/DebugComponent.h"
#include "ecs/components/MapComponent.h"

class GlobalSystem : public anax::System<anax::Requires<GlobalComponent>>
{
public:

	virtual void initialize()override;

	anax::Entity admin;
};
