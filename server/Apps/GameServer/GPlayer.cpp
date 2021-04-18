#include "GPlayer.h"

// 玩家信息
GPlayer::GPlayer()
{
	setIsOnline(false);
}

void GPlayer::print()
{
	LOG(INFO) << "+++++++++" << m_playerId << "+++++++++";
	LOG(INFO) << "isonline" << m_isonline;
	LOG(INFO) << "sessionID" << m_sessionID;
	LOG(INFO) << "createTime" << m_createTime;
	LOG(INFO) << "lastTime" << m_lastTime;
	LOG(INFO) << "account" << m_account;
	LOG(INFO) << "name" << m_name;

	LOG(INFO) << "-----------------------------------\n";
}


/////////////////////////////////////////////////////////////////////
int16_t GPlayer::getServerId(PLAYER_ID playerid)
{
	return playerid >> 48;
}

PLAYER_ID GPlayer::genPlayerId(int16_t svrId, int16_t noise, int32_t uniqueId)
{
	/*
	|   2   |  2  |     4     |
	| svrId |  0  |  uniqueId |
	*/

	int64_t i64_svrId = int64_t(svrId) << 48;
	int64_t i64_noise = int64_t(noise) << 32;
	int64_t i64_uniqueId = uniqueId;

	return i64_svrId | i64_noise | i64_uniqueId;
}

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
