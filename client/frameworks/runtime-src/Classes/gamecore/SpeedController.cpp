#include "SpeedController.h"

SpeedController::SpeedController()
{
	m_condi = SpeedControllerStopCondi::SC_CD_ALL;

	m_friction = 0.1;

	m_target = NULL;

	m_enableLuaCall = false;
	m_enableGravity = false;	
	m_enableForce = false;		
	m_enableFriction = false;	
	m_enableMaxValue = false;	
	m_enableMinValue = false;	
	m_isCallForceZero = false;
}

SpeedController::~SpeedController()
{}

void SpeedController::setEventCall(const LuaFunction& luaCall)
{
	m_luaCall = luaCall;
	m_enableLuaCall = true;
}

void SpeedController::callEvent(const std::string& eventName)
{
	if (m_enableLuaCall)
	{
		m_luaCall(eventName);
	}
}

void SpeedController::logicUpdate(float time)
{
	if (m_condi == SpeedControllerStopCondi::SC_CD_ALL || m_target == NULL)
		return;

	m_appedValue = Vec2::ZERO;

	forceUpdate(time);

	if (m_enableGravity)
	{
		m_appedValue = m_appedValue + m_gravity * time;
	}

	Vec2 v = m_target->getPosition();
	v = v + m_appedValue;

	if (m_enableMinValue)
	{
		v.x = MAX(v.x, m_minValue.x);
		v.y = MAX(v.y, m_minValue.y);
	}

	if (m_enableMaxValue)
	{
		v.x = MIN(v.x, m_maxValue.x);
		v.y = MIN(v.y, m_maxValue.y);
	}

	m_target->setPosition(v);
}

void SpeedController::forceUpdate(float time)
{
	if (!m_enableForce)
		return;

	float len = m_force.length();

	if (m_enableFriction)
	{
		len = len - (m_friction * time);
	}

	if (fabs(len) < 0.00001f)
	{
		if (m_condi == SpeedControllerStopCondi::SC_CD_FORCE_EQ_ZERO)
		{
			callEvent("stop");
			m_force.setZero();
			m_condi = SpeedControllerStopCondi::SC_CD_ALL;
			return;
		}
		else
		{
			if (!m_isCallForceZero)
			{
				m_isCallForceZero = true;
				callEvent("forceZero");
			}
		}
	}
	m_force = m_force.getNormalized() * len;

	if (m_condi == SpeedControllerStopCondi::SC_CD_FORCE_X_EQ_MIN 
		&& fabs(m_force.x - m_forceMinValue.x) < 0.00001f)
	{
		callEvent("stop");
		m_condi = SpeedControllerStopCondi::SC_CD_ALL;
		return;
	}

	if (m_condi == SpeedControllerStopCondi::SC_CD_FORCE_Y_EQ_MIN 
		&& fabs(m_force.y - m_forceMinValue.y) < 0.00001f)
	{
		callEvent("stop");
		m_condi = SpeedControllerStopCondi::SC_CD_ALL;
		return;
	}

	if (m_condi == SpeedControllerStopCondi::SC_CD_FORCE_EQ_MIN
		&& fabs(m_force.x - m_forceMinValue.x) < 0.00001f
		&& fabs(m_force.y - m_forceMinValue.y) < 0.00001f)
	{
		callEvent("stop");
		m_condi = SpeedControllerStopCondi::SC_CD_ALL;
		return;
	}

	//m_force.x = MAX(m_force.x, m_forceMinValue.x);
	//m_force.y = MAX(m_force.y, m_forceMinValue.y);

	m_appedValue = m_appedValue + m_force * time;
}
