#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/ArmatureComponent.h"

class ArmatureRenderSystem : public anax::System<anax::Requires<ArmatureComponent, ArmatureRenderComponent>>
{
public:

	void render();
	
private:
	void pause(cocostudio::ArmatureAnimation* animation, ArmatureComponent& component, ArmatureRenderComponent& renderComponent);
};

