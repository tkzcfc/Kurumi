#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/InputComponent.h"
#include "ecs/components/SIMPhysComponent.h"
#include "ecs/components/PropertyComponent.h"

class InputSystem : anax::System< anax::Requires<InputComponent, SIMPhysComponent, PropertyComponent> >
{
public:

	void update();

};

