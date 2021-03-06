#pragma once

#include "GLibBase.h"
#include "GameLogic.h"
#include "GameProto.h"

//// 战斗玩家信息
//struct FightPlayerInfo
//{
//	// 玩家id
//	int64_t id;
//	// 是否在线
//	bool online;
//};
//struct FightWorldInfo
//{
//	// 在线人数
//	int32_t onlineCount;
//	// 世界id
//	int32_t worldId;
//	// 世界逻辑
//	GGameWorld* logicWorld;
//	FightPlayerInfo players[G_FIGHT_MAX_PLAYER_COUNT];
//};

/// 战斗服务
class ServiceFight : public GIService
{
public:
	
	G_DEFINE_SERVICE(ServiceFight);

	virtual uint32_t onInit() override;

	virtual void onStartService() override;

	virtual void onStopService() override;

	virtual void onUpdate(float) override;

	virtual void onDestroy() override;

protected:

	void onMsg_NewFightReq(uint32_t sessionID, const svr_msg::NewFightReq& msg);

	void onMsg_JoinFightReq(uint32_t sessionID, const msg::JoinFightReq& msg);

	void onMsg_ExitFightReq(uint32_t sessionID, const msg::ExitFightReq& msg);

private:

	// 销毁战斗
	void destroyFight(int32_t uuid);

	// 统计当前正在战斗的数量
	int32_t curFightCount();

	// 清除无效战斗
	void clearInvalid();

private:
	std::vector<GameLogic*> m_arrFightInfo;
	GNetService* m_pNetService;
	GSlaveNodeService* m_pSlaveNode;
};

