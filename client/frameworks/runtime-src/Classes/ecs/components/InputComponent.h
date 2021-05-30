#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/utils/opmsg/GOPMsg.h"

class InputComponent : public BaseComponent
{
public:

	InputComponent()
	{
		lastKeyDown = G_KEY_NONE;
		keyDown = G_KEY_NONE;
	}

	// 上一帧按键状态
	G_BIT_TYPE lastKeyDown;
	// 按下的键
	G_BIT_TYPE keyDown;
};

