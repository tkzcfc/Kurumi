#pragma once

#include "GLibBase.h"
#include "GameLogic.h"
#include "GameProto.h"

/// 战斗服务
class GFightService : public GIService
{
public:
	
	G_DEFINE_SERVICE(GFightService);

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
	std::unique_ptr<GRandom> m_random;
};

