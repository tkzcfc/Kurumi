#pragma once

#include "GLibBase.h"
#include "GameProto.h"
// 游戏玩家

class GamePlayer
{
public:

	static uint32_t INVALID_SESSION_ID;

	GamePlayer();

	err::Code init(const ::svr_msg::FightRoleSpawnInfo& info);

	// 离线
	void offline();

	// 是否离线
	G_FORCEINLINE bool isOffline();



	// 当前加载进度
	G_SYNTHESIZE(float, m_loadPercent, LoadPercent);
	// 是否加载完成
	G_SYNTHESIZE(bool, m_loadFinish, LoadFinish);

	G_SYNTHESIZE(uint32_t, m_sessionID, SessionID);
	// 最后一次收到客户端消息时客户端逻辑帧
	G_SYNTHESIZE(uint32_t, m_lastRecvFrame, LastRecvFrame);
	// 离线的时间记录
	G_SYNTHESIZE(float, m_offlineTime, OfflineTime);
	// 当前ping值
	G_SYNTHESIZE(int32_t, m_ping, Ping);
	// playerid
	G_SYNTHESIZE(int64_t, m_playerID, PlayerID);

	// 战斗形象
	G_SYNTHESIZE_PASS_BY_REF(std::string, m_role, Role);
};

bool GamePlayer::isOffline()
{
	return getSessionID() == INVALID_SESSION_ID;
}

