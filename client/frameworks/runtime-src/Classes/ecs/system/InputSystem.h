#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/InputComponent.h"
#include "ecs/components/SIMPhysComponent.h"
#include "ecs/components/PropertyComponent.h"
#include "ecs/utils/opmsg/GOPMsg.h"

class InputSystem : public anax::System< anax::Requires<InputComponent, SIMPhysComponent, PropertyComponent> >
{
public:

	void update();
	
private:

	//  ‰»Î÷Æ«∞
	void beforeInput();

	void input(GOPMsg* msg);

	void keyUp(const anax::Entity& entity, G_BIT_TYPE key);
};

