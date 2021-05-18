#pragma once

#include "GLibBase.h"

typedef int64_t ROLE_ID;

// 角色
class GRole
{
public:
	
	GRole();

	G_PROPERTY(bool, m_isonline, IsOnline);
	G_SYNTHESIZE(uint32_t, m_sessionID, SessionID);

	/// db
	G_SYNTHESIZE(int64_t, m_createTime, CreateTime);
	G_SYNTHESIZE(int64_t, m_lastTime, LastTime);
	G_SYNTHESIZE(ROLE_ID, m_roleId, RoleId);
	G_SYNTHESIZE_PASS_BY_REF(std::string, m_name, Name);
	// 职业
	G_SYNTHESIZE(int32_t, m_occ, Occ);
	// lv
	G_SYNTHESIZE(int32_t, m_lv, Lv);
};

