#include "GPlayer.h"

// 玩家信息
GPlayer::GPlayer()
{
	setIsOnline(false);
}

void GPlayer::print()
{
	LOG(INFO) << "+++++++++" << m_playerId << "+++++++++";
	LOG(INFO) << "isonline :\t" << m_isonline;
	LOG(INFO) << "sessionID :\t" << m_sessionID;
	LOG(INFO) << "svrId :\t" << m_svrId;
	LOG(INFO) << "createTime :\t" << m_createTime;
	LOG(INFO) << "lastTime :\t" << m_lastTime;
	LOG(INFO) << "account :\t" << m_account;
	LOG(INFO) << "name :\t" << m_name;

	LOG(INFO) << "-----------------------------------\n";
}


/////////////////////////////////////////////////////////////////////
void GPlayer::setIsOnline(bool value)
{
	m_isonline = value;
	
	if(value == false)
		m_sessionID = UINT32_MAX;
}

bool GPlayer::getIsOnline() const
{
	return m_isonline;
}
