#pragma once

#include "GLibBase.h"
#include "game/GGameWorld.h"

// 战斗玩家信息
struct FightPlayerInfo
{
	// 玩家id
	int64_t id;
	// 是否在线
	bool online;
};
struct FightWorldInfo
{
	// 在线人数
	int32_t onlineCount;
	// 世界id
	int32_t worldId;
	// 世界逻辑
	GGameWorld* logicWorld;
	FightPlayerInfo players[G_FIGHT_MAX_PLAYER_COUNT];
};

/// 战斗服务
class ServiceFight : public GIService
{
public:

	virtual bool onInit() override;

	virtual void onStartService() override;

	virtual void onStopService() override;

	virtual void onUpdate(float) override;

	virtual void onDestroy() override;

private:

	// 创建新的世界
	int32_t genNewWorld(int32_t mapId, FightPlayerInfo* arrInfo, int32_t playerCount);

	// 更新世界在线人数
	void updateWorldOnlineCount(FightWorldInfo* info);

	// 销毁世界
	void destroyWorld(int32_t worldId);

private:
	std::vector<FightWorldInfo> m_arrFightInfo;

	int32_t m_seed;
};

