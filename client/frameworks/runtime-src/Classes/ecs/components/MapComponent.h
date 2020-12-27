#pragma once

#include "ecs/anaxHelper.h"

#if G_TARGET_CLIENT
#include "foundation/render/GMapLayer.h"
#endif

// ¹Ç÷À¶¯»­×é¼þ
class MapComponent : public anax::Component
{
public:
	MapComponent()
	{
#if G_TARGET_CLIENT
		render = NULL;
#endif
	}

#if G_TARGET_CLIENT
	GMapLayer* render;
#endif
};
