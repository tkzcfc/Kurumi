#include "GamePlayer.h"

// 游戏玩家

uint32_t GamePlayer::INVALID_SESSION_ID = UINT32_MAX;

GamePlayer::GamePlayer()
{
	m_loadPercent = 0.0f;
	m_loadFinish = false;
	this->offline();
}

err::Code GamePlayer::init(const ::svr_msg::FightRoleSpawnInfo& info)
{
	m_playerID = info.roleid();
	return err::Code::SUCCESS;
}

void GamePlayer::offline()
{
	this->setSessionID(INVALID_SESSION_ID);
	this->setLastRecvFrame(0U);
	this->setPing(0);
	this->setOfflineTime(GApplication::getInstance()->getRunTime());
}

