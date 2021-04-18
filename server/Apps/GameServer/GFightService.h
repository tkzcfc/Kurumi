#pragma once

#include "GLibBase.h"
#include "GameProto.h"
#include "GPlayerMngService.h"

#define FIGHT_MAX_PLAYER_COUNT 4

// 战斗服务
class GFightService : public GIService
{
	// 战斗申请组
	struct FightApplyGroup
	{
		PLAYER_ID playerid[FIGHT_MAX_PLAYER_COUNT];
		int32_t count;
		time_t time;
		int32_t fightType;
	};

public:
	G_DEFINE_SERVICE(GFightService);

	virtual uint32_t onInit() override;

	virtual void onUpdate(float) override;

protected:
	
	void onMsg_NewFightAck(uint32_t sessionID, const svr_msg::NewFightAck& msg);

	////////////////////////////////////////////////////////////////////////////////////////////////
	void onMsg_StartPVEFightReq(uint32_t sessionID, const msg::StartPVEFightReq& msg);

	void onMsg_StartPVPFightReq(uint32_t sessionID, const msg::StartPVPFightReq& msg);

	void onMsg_StopPVPFightReq(uint32_t sessionID, const msg::Null& msg);


private:

	void onUpdate_PVPCheck(float dt);
	
	const SlaveNodeInfo* getFightSvr();

	int32_t newFightGroup(PLAYER_ID* arrPlayer, int32_t playerCount, int32_t fightType);

	FightApplyGroup* getPlayerApplyGroup(PLAYER_ID playerId);
	
private:

	GNetService* m_pNetService;
	GMasterNodeService* m_pMasterNodeService;
	GPlayerMngService* m_pPlayerMngService;

	std::map<int32_t, FightApplyGroup> m_applyGroupMap;
	uint32_t m_applyGroupSeed;

	// pvp申请玩家合集
	std::set<PLAYER_ID> m_pvpSet;
};
