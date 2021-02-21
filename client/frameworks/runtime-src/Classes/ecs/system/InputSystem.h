#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/InputComponent.h"
#include "ecs/components/SIMPhysComponent.h"
#include "ecs/components/PropertyComponent.h"
#include "opmsg/GOPMsg.h"

class InputSystem : public anax::System< anax::Requires<InputComponent, SIMPhysComponent, PropertyComponent> >
{
public:

	void update();
	
private:

	// 输入之前
	void beforeInput();

	void input(GOPMsg_Base* msg);

	// 输入之后
	void afterInput();

};

