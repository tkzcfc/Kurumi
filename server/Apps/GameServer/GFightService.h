#pragma once

#include "GLibBase.h"
#include "GameProto.h"
#include "GPlayerMngService.h"
#include "GRoleMngService.h"

#define FIGHT_MAX_PLAYER_COUNT 4

// 战斗服务
class GFightService : public GIService
{
	// 战斗申请组
	struct FightApplyGroup
	{
		ROLE_ID roleid[FIGHT_MAX_PLAYER_COUNT];
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

	void onMsg_StopPVPFightReq(uint32_t sessionID, const msg::StopPVPFightReq& msg);


private:

	void onUpdate_PVPCheck(float dt);
	
	const SlaveNodeInfo* getFightSvr();

	int32_t newFightGroup(ROLE_ID* arrRole, int32_t roleCount, int32_t fightType);

	FightApplyGroup* getRoleApplyGroup(ROLE_ID roleid, int32_t fightType);
	
private:

	GNetService* m_pNetService;
	GMasterNodeService* m_pMasterNodeService;
	GPlayerMngService* m_pPlayerMngService;
	GRoleMngService* m_pRoleMngService;

	std::map<int32_t, FightApplyGroup> m_applyGroupMap;
	uint32_t m_applyGroupSeed;

	// pvp申请玩家合集
	std::set<ROLE_ID> m_pvpSet;
};
