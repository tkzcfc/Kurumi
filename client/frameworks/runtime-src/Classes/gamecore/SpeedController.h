#pragma once

#include "cocos2d.h"
#include "lua_function/LuaFunction.h"

using namespace cocos2d;

class SpeedController
{
public:

	SpeedController();

	~SpeedController();

	void setLuaUpdateCall(const LuaFunction& luaCall);
	inline void clearLuaUpdateCall()			{ m_enableLuaUpdateCall = false; }
	
	inline void setTarget(Node* target)			{ m_target = target; }
	inline Node* getTarget()					{ return m_target; }

	inline void setStopUpdate(bool isStop) { m_isStopUpdate = isStop; }

	inline bool isStopUpdate() { return m_isStopUpdate; }

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

	inline float getAppendX() { return m_appedValue.x; }
	inline float getAppendY() { return m_appedValue.y; }

	// 设置当前是否为正方向，如果是则该方向的值为正值
	// 1正 -1负 0忽略
	void setGravityPositive(int x, int y);
	void setForcePositive(int x, int y);

	// 逻辑更新
	void logicUpdate(float time);

	void defaultValue();

protected:

	void forceUpdate(float time);

private:
	Vec2 m_gravity;		// 重力
	Vec2 m_force;		// 力
	float m_friction;	// 摩擦力
	Vec2 m_minValue;	// 最小值
	Vec2 m_maxValue;	// 最大值

	bool m_enableGravity;	// 重力是否启用
	bool m_enableForce;		// 力是否启用
	bool m_enableFriction;	// 摩擦力是否启用
	bool m_enableMaxValue;	// 最大值是否启用
	bool m_enableMinValue;	// 最小值是否启用

	bool m_isStopUpdate;	// 是否停止逻辑更新

	Vec2 m_appedValue;

	LuaFunction m_luaUpdateCall;
	bool m_enableLuaUpdateCall;

	Node* m_target;
};
