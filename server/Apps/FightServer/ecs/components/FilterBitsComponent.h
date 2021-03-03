#pragma once

#include "ecs/anaxHelper.h"

class FilterBitsComponent : public BaseComponent
{
public:
	FilterBitsComponent()
	{
		group = 0;
	}
	int32_t group;
};


