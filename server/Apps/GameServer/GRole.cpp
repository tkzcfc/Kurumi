#include "GRole.h"

// 玩家信息
GRole::GRole()
{
	m_player = NULL;
	m_dataDirty = false;
	setIsOnline(false);
	m_jsonData = "{}";
}


void GRole::print()
{
	LOG(INFO) << "+++++++++" << m_roleId << "+++++++++";
	LOG(INFO) << "createTime :\t" << m_createTime;
	LOG(INFO) << "lastTime :\t" << m_lastTime;

	LOG(INFO) << "createTime :\t" << m_createTime;
	LOG(INFO) << "lastTime :\t" << m_lastTime;
	LOG(INFO) << "occ :\t" << m_occ;
	LOG(INFO) << "lv :\t" << m_lv;
	LOG(INFO) << "name :\t" << m_name;
	LOG(INFO) << "jsonData:\t" << m_jsonData;

	LOG(INFO) << "\n";
}


/////////////////////////////////////////////////////////////////////
void GRole::setIsOnline(bool value)
{
	m_isonline = value;

	if (value == false)
	{
		m_sessionID = UINT32_MAX;
	}
}

bool GRole::getIsOnline() const
{
	return m_isonline;
}

void GRole::setJsonData(const std::string& var)
{
	if (var.empty())
	{
		m_jsonData = "{}";
	}
	else
	{
		m_jsonData = var;
	}
}

std::string& GRole::getJsonData()
{
	return m_jsonData;
}

void GRole::setDirty()
{
	m_dataDirty = true;
}

void GRole::trySave(csqliter* sqliter)
{
	if (m_dataDirty)
	{
		m_dataDirty = false;
		save(sqliter);
	}
}

bool GRole::save(csqliter* sqliter)
{
	std::string sql = "UPDATE role SET ";

	sql += StringUtils::format("name = \"%s\", ", this->getName().c_str());
	sql += StringUtils::format("occ = %lld, ", this->getOcc());
	sql += StringUtils::format("lv = %lld, ", this->getLv());
	sql += StringUtils::format("lastTime = %lld, ", this->getLastTime());
	sql += StringUtils::format("jsonData = \"%s\" ", this->getJsonData().c_str());

	sql += StringUtils::format("WHERE roleId = %lld", this->getRoleId());

	sqliter->setsql(sql.c_str());

	if (sqliter->runsinglestepstatement() != successdb)
	{
		LOG(ERROR) << "sql failed: update role [GRole::save]";
		G_ASSERT(false);
		return false;
	}
	return true;
}