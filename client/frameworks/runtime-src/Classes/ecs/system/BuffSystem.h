#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/BuffComponent.h"

class BuffSystem : public anax::System<anax::Requires<BuffComponent>>
{
public:

	void removeInvalid();

	void update();

};
