#include "GAccountMgrService.h"

// 账号服务.cpp

uint32_t GAccountMgrService::onInit()
{
	G_CHECK_SERVICE(GLocalStorageService);

	auto local = m_serviceMgr->getService<GLocalStorageService>();
	m_sqliter = local->getsqliter();

	m_sqliter->setsql("CREATE TABLE IF NOT EXISTS account ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"username TEXT, "
		"password TEXT, "
		"account TEXT, "
		"time INTEGER, "
		"lastsvr INTEGER);");

	if (m_sqliter->runsinglestepstatement() != successdb) 
	{
		LOG(ERROR) << "sql failed: CREATE TABLE account";
		return SCODE_START_FAIL_EXIT_APP;
	}

	if (!readAccount())
		return SCODE_START_FAIL_EXIT_APP;
	
	return SCODE_START_SUCCESS;
}

bool GAccountMgrService::readAccount()
{
	m_sqliter->setsql("SELECT username, password, account, lastsvr FROM account;");
	m_sqliter->pushvaltypesout(strdbval, strdbval, strdbval, intdbval);

	AccountInfo info;
	m_allAcountInfo.clear();
	do
	{
		auto code = m_sqliter->runstep();
		if (code == successdb)
			break;

		if (code != rowresultdb)
		{
			LOG(ERROR) << "load account failed";
			return false;
		}
		
		info.username = m_sqliter->rowdata[0].sval;
		info.password = m_sqliter->rowdata[1].sval;
		info.account = m_sqliter->rowdata[2].sval;
		info.lastSvr  = m_sqliter->rowdata[3].ival;
		m_allAcountInfo.push_back(info);
	} while (true);

#if G_DEBUG
	for (size_t i = 0; i < m_allAcountInfo.size(); i++)
	{
		printf("[%zd]load db'%s' -> '%s',account: %s\n", i,
			m_allAcountInfo[i].username.c_str(), 
			m_allAcountInfo[i].password.c_str(),
			m_allAcountInfo[i].account.c_str());
	}
#endif
	return true;
}

bool GAccountMgrService::contain(const std::string& user)
{
	for (auto& it : m_allAcountInfo)
	{
		if (it.username == user)
			return true;
	}
	return false;
}

bool GAccountMgrService::containAccount(const std::string& account)
{
	for (auto& it : m_allAcountInfo)
	{
		if (it.account == account)
			return true;
	}
	return false;
}

int32_t GAccountMgrService::createAccount(const std::string& user, const std::string& pwd, int32_t platform)
{
	auto username = StringUtils::format("%s_%d", user.c_str(), platform);
	if (contain(username))
	{
		LOG(ERROR) << "Account number already exists, user:" << username;
		return -100;
	}
	
	uint32_t count = m_allAcountInfo.size() + std::rand();
	std::string account;
	uint16_t loopCount = 0;
	do
	{
		account = StringUtils::format("%08X%08X%04X", NFrame::CRC32(username), count, loopCount);
		if (!containAccount(account))
			break;
		loopCount++;
	} while (true);

	// username, password, account, lastsvr
	m_sqliter->setsql("INSERT INTO account ("
		"username, password, account, time, lastsvr) "
		"VALUES (:str1, :str2, :str3, :int1, :int2);");

	m_sqliter->bindstr("str1", username.c_str());
	m_sqliter->bindstr("str2", pwd.c_str());
	m_sqliter->bindstr("str3", account.c_str());
	m_sqliter->bindint("int1", time(NULL));
	m_sqliter->bindint("int2", 0);
	if (m_sqliter->runsinglestepstatement() != successdb) 
	{
		LOG(ERROR) << "sql failed: insert account, user:" << username;
		return -200;
	}

	AccountInfo info;
	info.username = username;
	info.password = pwd;
	info.account = account;
	info.lastSvr = 0;
	m_allAcountInfo.push_back(info);

	return 0;
}

err::Code GAccountMgrService::getAccount(const std::string& user, const std::string& pwd, int32_t platform, std::string& outAccount)
{
	auto username = StringUtils::format("%s_%d", user.c_str(), platform);
	for (auto& it : m_allAcountInfo)
	{
		if (it.username == username)
		{
			if (it.password == pwd)
			{
				outAccount = it.account;
				return err::Code::SUCCESS;
			}
			return err::Code::WRONG_PASSWORD;
		}
	}
	return err::Code::ACCOUNT_NOT_EXIST;
}
