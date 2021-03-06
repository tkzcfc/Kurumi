#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/ArmatureComponent.h"

class ArmatureSystem : public anax::System<anax::Requires<ArmatureComponent>>
{
public:

	ArmatureSystem();

	virtual ~ArmatureSystem();

	void update(float32 delta);

private:

	void stepAni(ArmatureComponent& component);

	void runAction(ArmatureComponent& component, struct GAnimationData* aniData);
	
	void playAudio(const std::string& audioName);
};
