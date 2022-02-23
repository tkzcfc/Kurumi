#pragma once

#include "GPlayer.h"

// 玩家管理服务
class GPlayerMngService : public GIService
{
public:
	G_DEFINE_SERVICE(GPlayerMngService);

	virtual uint32_t onInit() override;

	virtual void onUpdate(float dt) override;

	G_FORCEINLINE std::vector< std::unique_ptr<GPlayer> >& getAllPlayer();

public:

	// 玩家数据创建
	GPlayer* createPlayer(const std::string& account);

	// 获取玩家数据
	GPlayer* getPlayer(int64_t playerId);

	// 通过会话id获取对应登录角色
	GRole* getRoleBySessionID(uint32_t sessionID);

	// 通过会话id获取玩家
	GPlayer* getPlayerBySessionID(uint32_t sessionID);

	bool queryPlayerInfo(const std::string& account, std::vector<GPlayer*>& players);

	uint32_t getSessionID(int64_t playerId);

	// 向玩家发送另一个玩家当前登录的角色信息
	bool sendLoginRoleToPlayer(GPlayer* toPlayer, GPlayer* infoPlayer);

	// 向玩家发送角色信息
	bool sendRoleInfoToPlayer(GPlayer* toPlayer, GRole* roleInfo);

private:

	// 读取玩家数据
	bool readPlayer();
	
private:

	csqliter* m_sqliter;
	std::vector< std::unique_ptr<GPlayer> > m_allPlayer;
	int32_t m_svrId;
};

std::vector< std::unique_ptr<GPlayer> >& GPlayerMngService::getAllPlayer()
{
	return m_allPlayer;
}
