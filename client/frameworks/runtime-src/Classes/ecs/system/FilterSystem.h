#pragma once

#include "ecs/components/FilterComponent.h"
#include "foundation/GameMacro.h"

class Actor;
class FilterSystem : public anax::System<anax::Requires<FilterComponent>>, public Ref
{
public:

	FilterSystem();

	virtual ~FilterSystem();

	std::vector<Actor*> getAllActorByFilterData(int filterData);

	Actor* randomGetActorByFilterData(int filterData);
};

DEFINE_SYSTEM(FilterSystem);

