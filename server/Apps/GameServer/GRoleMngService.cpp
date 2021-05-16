#include "GRoleMngService.h"

uint32_t GRoleMngService::onInit()
{
	G_CHECK_SERVICE(GLocalStorageService);
	
	/// GLocalStorageService
	auto local = m_serviceMgr->getService<GLocalStorageService>();
	m_sqliter = local->getsqliter();

	m_sqliter->setsql("CREATE TABLE IF NOT EXISTS role ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"roleId INTEGER, "
		"name TEXT, "
		"occ INTEGER, "
		"lv INTEGER, "
		"lastTime INTEGER, "
		"createTime INTEGER);");

	if (m_sqliter->runsinglestepstatement() != successdb)
	{
		LOG(ERROR) << "sql failed: CREATE TABLE role";
		return SCODE_START_FAIL_EXIT_APP;
	}

	if (!readAllRole())
		return SCODE_START_FAIL_EXIT_APP;

	return SCODE_START_SUCCESS;
}

// 读取玩家数据
bool GRoleMngService::readAllRole()
{
	m_sqliter->setsql("SELECT roleId, name, occ, lv, lastTime, createTime FROM role;");
	m_sqliter->pushvaltypesout(intdbval, strdbval, intdbval, intdbval, intdbval, intdbval);

	m_allRole.clear();
	do
	{
		auto code = m_sqliter->runstep();
		if (code == successdb)
			break;

		if (code != rowresultdb)
		{
			LOG(ERROR) << "load role failed";
			return false;
		}
		auto roleId		= m_sqliter->rowdata[0].ival;
		auto occ		= m_sqliter->rowdata[1].ival;
		auto lv			= m_sqliter->rowdata[2].ival;
		auto name		= m_sqliter->rowdata[3].sval;
		auto lastTime	= m_sqliter->rowdata[4].ival;
		auto createTime = m_sqliter->rowdata[5].ival;

		m_allRole.push_back(GRole());

		auto& role = m_allRole.back();
		role.setRoleId(roleId);
		role.setName(name);
		role.setOcc(occ);
		role.setLv(lv);
		role.setLastTime(lastTime);
		role.setCreateTime(createTime);
	} while (true);
	return true;
}


// 角色数据创建
GRole* GRoleMngService::createRole(const std::string& name, int32_t occ)
{
	if (name.empty())
		return NULL;

	int64_t curTime = ::time(NULL);
	ROLE_ID roleId = 0;
	int32_t count = 1;
	do
	{
		roleId = (int32_t)m_allRole.size() + count;
		if (getRole(roleId) == NULL)
			break;

		count++;
	} while (true);
	
	m_allRole.push_back(GRole());

	auto& role = m_allRole.back();
	role.setRoleId(roleId);
	role.setName(name);
	role.setLastTime(curTime);
	role.setCreateTime(curTime);
	role.setLv(1);
	role.setOcc(occ);

	// roleId, name, lastTime, createTime
	m_sqliter->setsql("INSERT INTO role ("
		"roleId, occ, lv, name, lastTime, createTime) "
		"VALUES (:int_roleId, :int_occ, :int_lv, :str_name, :int_lastTime, :int_createTime);");

	m_sqliter->bindint("int_roleId", roleId);
	m_sqliter->bindint("int_occ", role.getOcc());
	m_sqliter->bindint("int_lv", role.getLv());
	m_sqliter->bindstr("str_name", name.c_str());
	m_sqliter->bindint("int_lastTime", curTime);
	m_sqliter->bindint("int_createTime", curTime);
	if (m_sqliter->runsinglestepstatement() != successdb)
	{
		LOG(ERROR) << "sql failed: insert role, roleId:" << roleId << ", name:" << name;
		G_ASSERT(false);
		m_allRole.pop_back();
		return NULL;
	}

	return &role;
}

bool GRoleMngService::containName(const std::string& name)
{
	for (auto & it : m_allRole)
	{
		if (it.getName() == name)
		{
			return true;
		}
	}
	return false;
}

// 获取角色数据
GRole* GRoleMngService::getRole(ROLE_ID roleId)
{
	for (auto & it : m_allRole)
	{
		if (it.getRoleId() == roleId)
		{
			return &it;
		}
	}
	return NULL;
}
