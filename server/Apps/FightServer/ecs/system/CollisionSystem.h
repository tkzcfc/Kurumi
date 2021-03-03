#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/ArmatureComponent.h"
#include "ecs/components/PropertyComponent.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/components/FilterBitsComponent.h"
#include "ecs/components/InjuryListComponent.h"

class CollisionSystem : public anax::System<anax::Requires<ArmatureComponent, PropertyComponent, TransformComponent, FilterBitsComponent, InjuryListComponent>>
{
public:

	void update();

private:

	void test(const anax::Entity& entityA, const anax::Entity& entityB);

	bool collision(const anax::Entity& entityA, const anax::Entity& entityB);

public:

	GAnimationData* getAnimData(ArmatureComponent& component);
};
