#include "GPlayer.h"
#include "GRoleMngService.h"

// 玩家信息
GPlayer::GPlayer()
{
	m_dataDirty = false;
	m_loginRole = NULL;
	setIsOnline(false);
}

void GPlayer::print()
{
	LOG(INFO) << "+++++++++" << m_playerId << "+++++++++";
	LOG(INFO) << "isonline :\t" << m_isonline;
	LOG(INFO) << "sessionID :\t" << m_sessionID;
	LOG(INFO) << "svrId :\t" << m_svrId;
	LOG(INFO) << "createTime :\t" << m_createTime;
	LOG(INFO) << "lastTime :\t" << m_lastTime;
	LOG(INFO) << "account :\t" << m_account;
	LOG(INFO) << "name :\t" << m_name;
	LOG(INFO) << "roles:\t" << getRoleString();

	LOG(INFO) << "-----------------------------------\n";
}


/////////////////////////////////////////////////////////////////////
void GPlayer::setIsOnline(bool value)
{
	m_isonline = value;
	
	if (value == false)
	{
		m_sessionID = UINT32_MAX;
		if (m_loginRole)
		{
			m_loginRole->setIsOnline(false);
		}
	}
}

bool GPlayer::getIsOnline() const
{
	return m_isonline;
}

void GPlayer::setRoles(const std::string& role)
{
	m_allRole.clear();
	if (role.empty())
		return;

	rapidjson::Document json;
	rapidjson::StringStream stream(role.c_str());

	json.ParseStream<0>(stream);

	if (json.HasParseError())
	{
		LOG(ERROR) << "[GPlayer] -> setRoles json parse error : " << json.GetParseError();
		LOG(ERROR) << "error json:" << role;
		return;
	}

	if (json.IsArray() == false)
	{
		LOG(ERROR) << "[GPlayer] -> setRoles error json:" << role;
		return;
	}

	auto serviceMgr = GApplication::getInstance()->getServiceMgr();
	auto roleMngService = serviceMgr->getService<GRoleMngService>();

	m_allRole.reserve(json.Size());
	for (auto i = 0; i < json.Size(); ++i)
	{
		auto roleId = json[i].GetInt64();
		auto pRole = roleMngService->getRole(roleId);
		if (pRole == NULL)
		{
			LOG(ERROR) << "[GPlayer] -> setRoles invalue roleId:" << roleId << " in: " << this->getName();
		}
		else
		{
			pRole->setPlayer(this);
			m_allRole.push_back(pRole);
		}
	}
}

std::string GPlayer::getRoleString()
{
	rapidjson::Document document;
	document.SetArray();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	for (auto& it : m_allRole)
	{
		rapidjson::Value roleId(rapidjson::kNumberType);
		roleId.SetInt64(it->getRoleId());
		document.PushBack(roleId, allocator);
	}
	rapidjson::StringBuffer buffer;
	//rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	auto msg = buffer.GetString();

	return buffer.GetString();
}

GRole* GPlayer::getRole(ROLE_ID roleId)
{
	for (auto& it : m_allRole)
	{
		if (it->getRoleId() == roleId)
			return it;
	}
	return NULL;
}

void GPlayer::addRole(GRole* role)
{
	role->setPlayer(this);
	m_allRole.push_back(role);
	this->setDirty();
}

void GPlayer::setDirty()
{
	m_dataDirty = true;
}

void GPlayer::trySave(csqliter* sqliter)
{
	if (m_dataDirty)
	{
		m_dataDirty = false;
		save(sqliter);
	}
}

bool GPlayer::save(csqliter* sqliter)
{
	std::string sql = "UPDATE player SET ";

	sql += StringUtils::format("svrid = %d, ", this->getSvrId());
	sql += StringUtils::format("account = \"%s\", ", this->getAccount().c_str());
	sql += StringUtils::format("name = \"%s\", ", this->getName().c_str());
	sql += StringUtils::format("lasttime = %lld, ", this->getLastTime());
	sql += StringUtils::format("createtime = %lld, ", this->getCreateTime());
	sql += StringUtils::format("roles = \"%s\" ", this->getRoleString().c_str());

	sql += StringUtils::format("WHERE playerid = %lld", this->getPlayerId());

	sqliter->setsql(sql.c_str());

	if (sqliter->runsinglestepstatement() != successdb)
	{
		LOG(ERROR) << "sql failed: update player [GPlayer::save]";
		G_ASSERT(false);
		return false;
	}
	return true;
}

GRole* GPlayer::getLoginRole()
{
	return m_loginRole;
}

bool GPlayer::setLoginRole(ROLE_ID roleId)
{
	if (m_loginRole)
	{
		m_loginRole->setIsOnline(true);
		m_loginRole = NULL;
	}
	for (auto it : m_allRole)
	{
		if (it->getRoleId() == roleId)
		{
			m_loginRole = it;
			m_loginRole->setSessionID(m_sessionID);
			m_loginRole->setIsOnline(true);
			return true;
		}
	}
	return false;
}
