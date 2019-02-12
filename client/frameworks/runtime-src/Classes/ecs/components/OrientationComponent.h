#pragma once

#include "ecs/anaxHelper.h"
#include "lua_function/LuaFunction.h"

// 朝向组件
/*
 * -1面朝左
 * 1面朝右
*/
class OrientationComponent : public anax::Component, public Ref
{
public:

	OrientationComponent()
	{
		m_lockOrientation = false;
		m_orientation = 1;
	}

	virtual ~OrientationComponent()
	{}

	bool setOrientation(int orientation)
	{
		if (m_lockOrientation || m_orientation == orientation)
		{
			return false;
		}
		m_orientation = orientation;
		if (m_orientationTurnCall.isvalid())
		{
			m_orientationTurnCall.ppush();
			m_orientationTurnCall.pusharg(orientation);
			m_orientationTurnCall.pcall();
		}
		return true;
	}

	int m_orientation;

	bool m_lockOrientation;

	LuaFunction m_orientationTurnCall;
};

DEFINE_COMPONENT(OrientationComponent);
