#include "GRole.h"

// 玩家信息
GRole::GRole()
{
	setIsOnline(false);
}


/////////////////////////////////////////////////////////////////////
void GRole::setIsOnline(bool value)
{
	m_isonline = value;

	if (value == false)
	{
		m_sessionID = UINT32_MAX;
	}
}

bool GRole::getIsOnline() const
{
	return m_isonline;
}
