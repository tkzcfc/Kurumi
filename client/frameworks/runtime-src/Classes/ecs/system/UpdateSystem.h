#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/PropertyComponent.h"

// 更新系统
class UpdateSystem : public anax::System<anax::Requires<PropertyComponent>>
{
public:

	void update(float dt);
};
