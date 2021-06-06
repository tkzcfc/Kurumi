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

	void keyUp(const anax::Entity& entity, G_BIT_TYPE key);

	void keyDown(const anax::Entity& entity, G_BIT_TYPE key);

	void keepPress(const anax::Entity& entity, G_BIT_TYPE key);
};

