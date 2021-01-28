#pragma once

#include "GGameWorld.h"

#if G_TARGET_CLIENT

class GGameLayer : public Node
{
public:

	CREATE_FUNC(GGameLayer);

	virtual bool init();

	virtual void update(float delta)override;

	GGameWorld* m_world;
};

#endif