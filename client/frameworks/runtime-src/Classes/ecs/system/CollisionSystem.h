#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/ArmatureComponent.h"
#include "ecs/components/PropertyComponent.h"
#include "ecs/components/TransformComponent.h"

class CollisionSystem : public anax::System<anax::Requires<ArmatureComponent, PropertyComponent, TransformComponent>>
{
public:

	void update();

private:

	void test(const anax::Entity& entityA, const anax::Entity& entityB);

public:

	GAnimationData* getAnimData(ArmatureComponent& component);
};
