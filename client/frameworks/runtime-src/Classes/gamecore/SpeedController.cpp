#include "SpeedController.h"

SpeedController::SpeedController()
{
	defaultValue();
	m_target = NULL;
}

SpeedController::~SpeedController()
{}

void SpeedController::setLuaUpdateCall(const LuaFunction& luaCall)
{
	m_luaUpdateCall = luaCall;
	m_enableLuaUpdateCall = true;
}

void SpeedController::setGravityPositive(int x, int y)
{
	if(x > 0)
		m_gravity.x = fabs(m_gravity.x);
	else if(x < 0)
		m_gravity.x = -fabs(m_gravity.x);

	if (y > 0)
		m_gravity.y = fabs(m_gravity.y);
	else if(y < 0)
		m_gravity.y = -fabs(m_gravity.y);
}

void SpeedController::setForcePositive(int x, int y)
{
	if (x > 0)
		m_force.x = fabs(m_force.x);
	else if (x < 0)
		m_force.x = -fabs(m_force.x);

	if (y > 0)
		m_force.y = fabs(m_force.y);
	else if (y < 0)
		m_force.y = -fabs(m_force.y);
}

void SpeedController::logicUpdate(float time)
{
	if (m_isStopUpdate || m_target == NULL)
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

	if (m_enableLuaUpdateCall)
	{
		m_luaUpdateCall(v.x, v.y, time);
	}
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

	if (len <= 0.0f)
	{
		m_force.setZero();
		return;
	}
	m_force = m_force.getNormalized() * len;

	m_appedValue = m_appedValue + m_force * time;
}

void SpeedController::defaultValue()
{
	m_gravity = Vec2::ZERO;
	m_force = Vec2::ZERO;
	m_friction = 0.0f;
	m_minValue = Vec2::ZERO;
	m_maxValue = Vec2::ZERO;

	m_enableGravity = false;
	m_enableForce = false;
	m_enableFriction = false;
	m_enableMaxValue = false;
	m_enableMinValue = false;

	m_isStopUpdate = true;

	m_appedValue = Vec2::ZERO;

	m_enableLuaUpdateCall = false;
}