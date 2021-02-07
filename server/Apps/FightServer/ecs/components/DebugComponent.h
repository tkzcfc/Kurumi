#pragma once

#include "ecs/anaxHelper.h"


class DebugComponent : public BaseComponent
{
public:

	DebugComponent()
	{
#if G_TARGET_CLIENT
		debugDrawNode = NULL;
#endif
	}

#if G_TARGET_CLIENT
	DrawNode* debugDrawNode;
#endif

};