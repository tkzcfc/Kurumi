#pragma once

#include "ecs/anaxHelper.h"

class TransformComponent : public anax::Component
{
public:
	TransformComponent()
		: scale(1.0f)
		, rotation(.0f)
	{
	}

	// äÖÈ¾×ø±ê
	GVec2 position;
	// Âß¼­×ø±ê
	GVec3 logicPos;
	// Ëõ·Å
	float32 scale;
	// Ðý×ª
	float32 rotation;
};


DEFINE_COMPONENT(TransformComponent);

