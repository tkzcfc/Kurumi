#pragma once

#include "GGameWorld.h"


class GGameLayer : public Node
{
public:

	virtual bool init();


	GGameWorld* m_world;
};

