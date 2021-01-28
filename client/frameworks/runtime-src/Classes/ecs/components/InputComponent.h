#pragma once

#include "ecs/anaxHelper.h"
#include "opmsg/GOPMsg.h"

class InputComponent : public BaseComponent
{
public:

	InputComponent()
	{
		lastKeyDown = G_KEY_NONE;
		keyDown = G_KEY_NONE;
	}

	void reset()
	{

	}
	
	// 上一帧按键状态
	G_BIT_TYPE lastKeyDown;
	// 按下的键
	G_BIT_TYPE keyDown;
};

