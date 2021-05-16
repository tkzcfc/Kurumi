#pragma once

#include "GLibBase.h"
#include "GameProto.h"
#include "GPlayerMngService.h"
#include "GRoleMngService.h"

// 登录服务

class GLoginService : public GIService
{
public:
	G_DEFINE_SERVICE(GLoginService);

	virtual uint32_t onInit() override;

protected:

	void onMsg_CheckTokenAck(uint32_t sessionID, const svr_msg::CheckTokenAck& msg);

	void onMsg_TokenChangeNtf(uint32_t sessionID, const svr_msg::TokenChangeNtf& msg);

	void onMsg_LoginReq(uint32_t sessionID, const msg::LoginReq& msg);

	void onMsg_CreateRoleReq(uint32_t sessionID, const msg::CreateRoleReq& msg);

	void onMsg_EnterGameReq(uint32_t sessionID, const msg::EnterGameReq& msg);

private:

	void onPlayerLogin(int64_t playerId, uint32_t sessionID);

	/// 玩家下线
	void playerOffline(GPlayer* player, err::Code code);

private:

	GNetService* m_pNetService;
	GSlaveNodeService* m_pSlaveNodeService;
	GPlayerMngService* m_pPlayerMngService;
	GRoleMngService* m_pRoleMngService;
};


