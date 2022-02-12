#pragma once

#include "GRole.h"

// 角色管理服务
class GRoleMngService : public GIService
{
public:
	G_DEFINE_SERVICE(GRoleMngService);

	virtual uint32_t onInit() override;

public:

	// 角色数据创建
	GRole* createRole(const std::string& name, int32_t occ);

	// 获取角色数据
	GRole* getRole(ROLE_ID roleId);

	bool containName(const std::string& name);

private:

	// 读取玩家数据
	bool readAllRole();

private:

	csqliter* m_sqliter;
	std::vector<GRole> m_allRole;
};


