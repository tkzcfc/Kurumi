#include "GamePlayer.h"

// 游戏玩家

uint32_t GamePlayer::INVALID_SESSION_ID = UINT32_MAX;

GamePlayer::GamePlayer()
{
	this->offline();
}

err::Code GamePlayer::init(const ::svr_msg::FightPlayerSpawnInfo& info)
{
	m_playerID = info.playerid();
	if (m_playerID.empty())
	{
		return err::Code::PARAM_ERROR;
	}

	return err::Code::SUCCESS;
}

void GamePlayer::offline()
{
	this->setSessionID(INVALID_SESSION_ID);
	this->setLastRecvFrame(0U);
	this->setPing(0);
	m_offlineTime = GApplication::getInstance()->getRunTime();
}

