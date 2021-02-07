#pragma once

#include "ecs/anaxHelper.h"

#if G_TARGET_CLIENT
#include "foundation/render/GMapLayer.h"
#endif

class MapComponent : public BaseComponent
{
public:
	MapComponent()
	{
#if G_TARGET_CLIENT
		render = NULL;
#endif
		mapWidth = 0.0f;
		mapHeight = 0.0f;
		minPosy = 0.0f;
		maxPosy = 0.0f;
	}

#if G_TARGET_CLIENT
	GMapLayer* render;
#endif
	float32 mapWidth;
	float32 mapHeight;
	
	float32 minPosy;
	float32 maxPosy;
};
