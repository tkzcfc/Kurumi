#pragma once

#include "ecs/anaxHelper.h"

enum IEvent_Move
{
	MOVE_NONE	= 0,
	MOVE_LEFT	= 1 << 1,
	MOVE_RIGHT	= 1 << 2,
	MOVE_UP		= 1 << 3,
	MOVE_DOWN	= 1 << 4,
};

enum IEvent_CMD
{
	CMD_JUMP,
	CMD_ATTACK,
	CMD_SKILL,
	CMD_NONE
};

class InputComponent : public BaseComponent
{
public:

	InputComponent()
	{
		reset();
	}

	void reset()
	{
		moveEvent = IEvent_Move::MOVE_NONE;
		cmdEvent = IEvent_CMD::CMD_NONE;
	}
	
	IEvent_Move moveEvent;
	IEvent_CMD cmdEvent;
};

