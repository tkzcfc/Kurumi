#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/PropertyComponent.h"

class UUIDSystem : public anax::System<anax::Requires<PropertyComponent>>
{
public:

	bool query(GUUID uuid, anax::Entity* pEntity = NULL);

};
