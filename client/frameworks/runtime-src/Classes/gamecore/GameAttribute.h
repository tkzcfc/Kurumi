#pragma once

#include "cocos2d.h"

using namespace cocos2d;

#define GAME_ORI_LEFT (-1)
#define GAME_ORI_RIGHT (1)

class GameAttribute
{
public:
	int		m_HP;				// HP
	float	m_att;				// 攻击力
	float	m_def;				// 防御力

	Vec2	m_speed;			// 正常状态移动速度
	Vec2	m_curSpeed;			// 当前移动速度
	Vec2	m_moveDirection;	// 移动方向
	
	short	m_curOrientation;	// 当前朝向 -1 左 1 右边
	
	bool	m_isJumpState;		// 是否为跳跃状态
	bool	m_isBackState;		// 移动时，是否为后退状态，如果是则不进行自动转向

	///////////////////////////////////////////////////////////////////////////////////////////

	GameAttribute()
	{
		m_HP = 0;
		m_att = 0;
		m_def = 0;
		m_curOrientation = GAME_ORI_RIGHT;
		m_isJumpState = false;
		m_isBackState = false;
	}

	void setHP(int value) 
	{
		m_HP = value; 
	}
	int getHP() 
	{ 
		return m_HP;
	}

	
	void setAtt(float value) 
	{ 
		m_att = value; 
	}
	float getAtt() 
	{ 
		return m_att; 
	}


	void setDef(float value) 
	{ 
		m_def = value; 
	}
	float getDef() 
	{ 
		return m_def; 
	}

	void setSpeed(float value1, float value2) 
	{ 
		m_speed = Vec2(value1, value2); 
	}
	float getSpeedX()
	{
		return m_speed.x;
	}
	float getSpeedY()
	{
		return m_speed.y;
	}
	const Vec2& getSpeed() 
	{
		return m_speed;
	}

	void setCurSpeed(float value1, float value2) 
	{ 
		m_curSpeed = Vec2(value1, value2); 
	}
	float getCurSpeedX()
	{
		return m_curSpeed.x;
	}
	float getCurSpeedY()
	{
		return m_curSpeed.y;
	}
	const Vec2& getCurSpeed() 
	{ 
		return m_curSpeed; 
	}

	void setMoveDirection(float value1, float value2) 
	{
		m_moveDirection = Vec2(value1, value2); 
	}
	float getMoveDirectionX()
	{
		return m_moveDirection.x;
	}
	float getMoveDirectionY()
	{
		return m_moveDirection.y;
	}
	const Vec2& getMoveDirection() 
	{
		return m_moveDirection; 
	}

	void setCurOrientation(short value) 
	{
		m_curOrientation = value; 
	}
	short getCurOrientation() 
	{
		return m_curOrientation;
	}

	void setIsJumpState(bool value) 
	{
		m_isJumpState = value;
	}
	bool getIsJumpState() 
	{
		return m_isJumpState; 
	}

	void setIsBackState(bool value) 
	{
		m_isBackState = value;
	}
	bool getIsBackState() 
	{
		return m_isBackState;
	}

};