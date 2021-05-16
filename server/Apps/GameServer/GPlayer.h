#pragma once

#include "GLibBase.h"
#include "GRole.h"

typedef int64_t PLAYER_ID;

// 玩家
class GPlayer
{
public:
	
	GPlayer();

	G_PROPERTY(bool, m_isonline, IsOnline);
	G_SYNTHESIZE(uint32_t, m_sessionID, SessionID);
	G_SYNTHESIZE_PASS_BY_REF(std::string, m_token, Token);

	// db
	G_SYNTHESIZE(int64_t, m_createTime, CreateTime);
	G_SYNTHESIZE(int64_t, m_lastTime, LastTime);
	G_SYNTHESIZE(PLAYER_ID, m_playerId, PlayerId);
	G_SYNTHESIZE(int32_t, m_svrId, SvrId);
	G_SYNTHESIZE_PASS_BY_REF(std::string, m_account, Account);
	G_SYNTHESIZE_PASS_BY_REF(std::string, m_name, Name);

public:

	void setRoles(const std::string& role);

	std::string getRoleString();

	GRole* getRole(ROLE_ID roleId);

	const std::vector<GRole*>& getRoles()
	{
		return m_allRole;
	}

	void addRole(GRole* role);

public:

	bool save(csqliter* sqliter);
			
public:
	
	void print();

private:

	std::vector<int64_t> m_roleIds;
	std::vector<GRole*> m_allRole;
};

