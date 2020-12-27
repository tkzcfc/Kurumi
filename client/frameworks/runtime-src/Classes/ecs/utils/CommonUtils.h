#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/UniqueComponent.h"

class CommonUtils
{
public:

	static anax::Entity& getAdmin(anax::World& world);


#if G_TARGET_CLIENT
	static DrawNode* getDebugDraw(anax::World& world);
#endif

};
