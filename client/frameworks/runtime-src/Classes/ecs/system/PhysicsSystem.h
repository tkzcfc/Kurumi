#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/components/BodyComponent.h"

class Box2DSystem : public anax::System<anax::Requires<TransformComponent, BodyComponent>>
{
public:

	Box2DSystem();

	virtual ~Box2DSystem();

	void initBodyComponent(BodyComponent* component);

protected:

};

DEFINE_SYSTEM(Box2DSystem);
