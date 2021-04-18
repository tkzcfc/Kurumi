#pragma once

#include "GLibBase.h"
#include "GameProto.h"
#include "GPlayerMngService.h"

// 登录服务

class GLoginService : public GIService
{
public:
	G_DEFINE_SERVICE(GLoginService);

	virtual uint32_t onInit() override;

protected:

	void onMsg_CheckTokenAck(uint32_t sessionID, const svr_msg::CheckTokenAck& msg);

	void onMsg_LoginReq(uint32_t sessionID, const msg::LoginReq& msg);

private:

	void onPlayerLogin(int64_t playerId, uint32_t sessionID);

	/// 玩家下线
	void playerOffline(GPlayer* player, err::Code code);

private:

	GNetService* m_pNetService;
	GSlaveNodeService* m_pSlaveNodeService;
	GPlayerMngService* m_pPlayerMngService;
};


