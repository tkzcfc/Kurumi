#pragma once

#include "cocos2d.h"

using namespace cocos2d;

#define GAME_ORI_LEFT (-1)
#define GAME_ORI_RIGHT (1)

class GameAttribute
{
public:
	int		m_HP;				// HP
	float	m_att;				// ¹¥»÷Á¦
	float	m_def;				// ·ÀÓùÁ¦

	///////////////////////////////////////////////////////////////////////////////////////////

	GameAttribute()
	{
		m_HP = 0;
		m_att = 0;
		m_def = 0;
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
};