#pragma once

#include "ecs/components/UpdateComponent.h"

class UpdateSystem : public anax::System<anax::Requires<UpdateComponent>>, public Ref
{
public:
	UpdateSystem();

	virtual ~UpdateSystem();

	void update(float delta);

	void lastUpdate(float delta);
};

DEFINE_SYSTEM(UpdateSystem);

