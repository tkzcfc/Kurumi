#pragma once

#include "cocos2d.h"
#include "LuaFunction.hpp"

using namespace cocos2d;

// 停止条件
enum SpeedControllerStopCondi
{
	SC_CD_FORCE_EQ_ZERO,	// 力为0时终止更新
	SC_CD_FORCE_EQ_MIN,		// 力等于最小值时
	SC_CD_FORCE_X_EQ_MIN,	// 力X等于最小值时
	SC_CD_FORCE_Y_EQ_MIN,	// 力Y等于最小值时
	SC_CD_ALL,				// 终止更新
	SC_CD_NONE				// 没有任何限制
};

class SpeedController
{
public:

	SpeedController();

	~SpeedController();

	void setEventCall(const LuaFunction& luaCall);

	inline void resetCallForceZero()			{ m_isCallForceZero = false; }

	inline void setTarget(Node* target)			{ m_target = target; }

	inline void setStopCondition(SpeedControllerStopCondi condi) { m_condi = condi; }

	inline SpeedControllerStopCondi getStopCondition() { return m_condi; }

	// 重力设置
	inline void setGravity(float x, float y)	{ m_gravity = Vec2(x, y); }
	inline float getGravityX()					{ return m_gravity.x; }
	inline float getGravityY()					{ return m_gravity.y; }
	// 是否启用重力
	inline void setGravityEnable(bool enable)	{ m_enableGravity = enable; }
	inline bool isGravityEnable()				{	return m_enableGravity;	}

	// 力设置
	inline void setForce(float x, float y)		{ m_force = Vec2(x, y); }
	inline float getForceX()					{ return m_force.x; }
	inline float getForceY()					{ return m_force.y; }
	// 是否启用力
	inline void setForceEnable(bool enable)		{ m_enableForce = enable; }
	inline bool isForceEnable()					{ return m_enableForce; }

	// 力的最小值
	inline void setForceMinValue(float x, float y)	{ m_forceMinValue = Vec2(x, y); }
	inline float getForceMinValueX()				{ return m_forceMinValue.x; }
	inline float getForceMinValueY()				{ return m_forceMinValue.y; }
	// 是否启用力最小值
	inline void setForceMinValueEnable(bool enable) { m_enableForce = enable; }
	inline bool isForceMinValueEnable()			{ return m_enableForce; }

	// 摩擦力设置
	inline void setFriction(float friction)		{ m_friction = friction; }
	inline float getFriction()					{ return m_friction; }
	// 是否启用摩擦力
	inline void setFrictionEnable(bool enable)	{ m_enableFriction = enable; }
	inline bool isFrictionEnable()				{ return m_enableFriction; }

	// 设置最大值
	inline void setMaxValue(float x, float y)	{ m_maxValue = Vec2(x, y); }
	inline float getMaxValueX()					{ return m_maxValue.x; }
	inline float getMaxValueY()					{ return m_maxValue.y; }
	// 是否启用最大值
	inline void setMaxValueEnable(bool enable)	{ m_enableMaxValue = enable; }
	inline bool isMaxValueEnable()				{ return m_enableMaxValue; }

	// 设置最小值
	inline void setMinValue(float x, float y)	{ m_minValue = Vec2(x, y); }
	inline float getMinValueX()					{ return m_minValue.x; }
	inline float getMinValueY()					{ return m_minValue.y; }
	// 是否启用最大值
	inline void setMinValueEnable(bool enable)	{ m_enableMinValue = enable; }
	inline bool isMinValueEnable()				{ return m_enableMinValue; }

	// 设置终止更新条件

	// 逻辑更新
	void logicUpdate(float time);

protected:

	void forceUpdate(float time);

	void callEvent(const std::string& eventName);

private:
	SpeedControllerStopCondi m_condi;

	Vec2 m_gravity;		// 重力
	Vec2 m_force;		// 力
	Vec2 m_forceMinValue;//力最小值
	float m_friction;	// 摩擦力
	Vec2 m_minValue;	// 最小值
	Vec2 m_maxValue;	// 最大值

	bool m_enableGravity;	// 重力是否启用
	bool m_enableForce;		// 力是否启用
	bool m_enableFriction;	// 摩擦力是否启用
	bool m_enableMaxValue;	// 最大值是否启用
	bool m_enableMinValue;	// 最小值是否启用

	Vec2 m_appedValue;

	LuaFunction m_luaCall;
	bool m_enableLuaCall;

	bool m_isCallForceZero;

	Node* m_target;
};
