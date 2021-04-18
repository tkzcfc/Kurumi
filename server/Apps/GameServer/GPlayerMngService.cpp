#include "GPlayerMngService.h"

uint32_t GPlayerMngService::onInit()
{
	G_CHECK_SERVICE(GConfigService);
	G_CHECK_SERVICE(GLocalStorageService);
	G_CHECK_SERVICE(GSlaveNodeService);

	/// GSlaveNodeService
	auto& json = m_serviceMgr->getService<GSlaveNodeService>()->descriptionJson();
	if (!json.HasMember("svrId"))
	{
		LOG(ERROR) << "[GPlayerMngService] \"svrId\" not found";
		return SCODE_START_FAIL_EXIT_APP;
	}

	auto value_svrId = json.FindMember("svrId");
	if (value_svrId->value.GetType() != rapidjson::Type::kNumberType)
	{
		LOG(ERROR) << "[GPlayerMngService] \"svrId\" is not a number";
		return SCODE_START_FAIL_EXIT_APP;
	}

	m_svrId = value_svrId->value.GetInt();

	/// GLocalStorageService
	auto local = m_serviceMgr->getService<GLocalStorageService>();
	m_sqliter = local->getsqliter();

	m_sqliter->setsql("CREATE TABLE IF NOT EXISTS player ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"playerid INTEGER, "
		"account TEXT, "
		"name TEXT, "
		"lastTime INTEGER, "
		"createTime INTEGER);");

	if (m_sqliter->runsinglestepstatement() != successdb)
	{
		LOG(ERROR) << "sql failed: CREATE TABLE player";
		return SCODE_START_FAIL_EXIT_APP;
	}

	if (!readPlayer())
		return SCODE_START_FAIL_EXIT_APP;

	return SCODE_START_SUCCESS;
}

// 读取玩家数据
bool GPlayerMngService::readPlayer()
{
	m_sqliter->setsql("SELECT playerid, account, name, lastTime, createTime FROM player;");
	m_sqliter->pushvaltypesout(intdbval, strdbval, strdbval, intdbval, intdbval);

	m_allPlayer.clear();
	do
	{
		auto code = m_sqliter->runstep();
		if (code == successdb)
			break;

		if (code != rowresultdb)
		{
			LOG(ERROR) << "load player failed";
			return false;
		}

		auto playerid	= m_sqliter->rowdata[0].ival;
		auto account	= m_sqliter->rowdata[1].sval;
		auto name		= m_sqliter->rowdata[2].sval;
		auto lastTime	=  m_sqliter->rowdata[3].ival;
		auto createTime = m_sqliter->rowdata[3].ival;

		m_allPlayer.push_back(GPlayer());

		auto& player = m_allPlayer.back();
		player.setPlayerId(playerid);
		player.setAccount(account);
		player.setName(name);
		player.setLastTime(lastTime);
		player.setCreateTime(createTime);		
	} while (true);

#if G_DEBUG
	for (auto& it : m_allPlayer)
	{
		it.print();
	}
#endif
	return true;
}

// 玩家数据创建
GPlayer* GPlayerMngService::createPlayer(const std::string& account)
{
	if (account.empty())
		return NULL;

	for (auto & it : m_allPlayer)
	{
		if (it.getAccount() == account)
		{
			// 该账号在本服已经有玩家数据
			if (GPlayer::getServerId(it.getPlayerId()) == m_svrId)
			{
				return NULL;
			}
		}
	}

	int64_t curTime = ::time(NULL);
	int64_t playerId = 0;
	int16_t count = 0;
	do
	{
		int16_t noise = 0xFFFF & curTime;
		noise += count;

		playerId = GPlayer::genPlayerId(m_svrId, noise, (int32_t)m_allPlayer.size());
		if (getPlayer(playerId) == NULL)
			break;

		count++;
	} while (true);

	std::string tmp = StringUtils::format("%s-%lld", account.c_str(), playerId);
	std::string name = StringUtils::format("p_%d", NFrame::CRC32(tmp));

	m_allPlayer.push_back(GPlayer());

	auto& player = m_allPlayer.back();
	player.setPlayerId(playerId);
	player.setAccount(account);
	player.setName(name);
	player.setLastTime(curTime);
	player.setCreateTime(curTime);

	return &player;
}

GPlayer* GPlayerMngService::getPlayer(int64_t playerId)
{
	for (auto & it : m_allPlayer)
	{
		if (it.getPlayerId() == playerId)
		{
			return &it;
		}
	}
	return NULL;
}

GPlayer* GPlayerMngService::getPlayerBySessionID(uint32_t sessionID)
{
	for (auto & it : m_allPlayer)
	{
		if (it.getSessionID() == sessionID)
		{
			return &it;
		}
	}
	return NULL;
}

bool GPlayerMngService::queryPlayerInfo(const std::string& account, std::vector<GPlayer*> players)
{
	for (auto & it : m_allPlayer)
	{
		if (it.getAccount() == account)
		{
			players.push_back(&it);
		}
	}

	return players.size() > 0;
}

uint32_t GPlayerMngService::getSessionID(int64_t playerId)
{
	auto player = getPlayer(playerId);
	if (player == NULL)
		return UINT32_MAX;
	return player->getSessionID();
}
