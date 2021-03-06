#pragma once

#include "GLibBase.h"
#include "GameProto.h"
// 游戏玩家

class GamePlayer
{
public:

	static uint32_t INVALID_SESSION_ID;

	GamePlayer();

	err::Code init(const ::svr_msg::FightPlayerSpawnInfo& info);

	// 离线
	void offline();

	G_FORCEINLINE bool isOffline() const;
	
	G_FORCEINLINE const std::string& playerID();

	G_FORCEINLINE uint32_t sessionID() const;

	G_FORCEINLINE void setSessionID(uint32_t value);
	
	G_FORCEINLINE float offlineTime() const;

	G_FORCEINLINE void setPing(int32_t value);

	G_FORCEINLINE int32_t ping() const;

	G_FORCEINLINE void setLastRecvFrame(uint32_t value);

	G_FORCEINLINE uint32_t lastRecvFrame() const;

private:
	uint32_t m_sessionID;
	// playerid
	std::string m_playerID;
	// 最后一次收到客户端消息时客户端逻辑帧
	uint32_t m_lastRecvFrame;
	// 当前ping值
	int32_t m_ping;
	// 离线的时间记录
	float m_offlineTime;
};

bool GamePlayer::isOffline() const
{
	return m_sessionID == INVALID_SESSION_ID;
}

const std::string& GamePlayer::playerID()
{
	return m_playerID;
}

uint32_t GamePlayer::sessionID() const
{
	return m_sessionID;
}

void GamePlayer::setSessionID(uint32_t value)
{
	m_sessionID = value;
}

float GamePlayer::offlineTime() const
{
	return m_offlineTime;
}

void GamePlayer::setPing(int32_t value)
{
	m_ping = value;
}

int32_t GamePlayer::ping() const
{
	return m_ping;
}

void GamePlayer::setLastRecvFrame(uint32_t value)
{
	m_lastRecvFrame = value;
}

uint32_t GamePlayer::lastRecvFrame() const
{
	return m_lastRecvFrame;
}

