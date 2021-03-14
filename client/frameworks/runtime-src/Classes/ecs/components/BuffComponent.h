#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/utils/buff/Buff.h"

// buff
class BuffComponent : public BaseComponent
{
public:
	BuffComponent()
	{
		buffList.reserve(5);
	}

	std::vector< std::shared_ptr<Buff> > buffList;
};


