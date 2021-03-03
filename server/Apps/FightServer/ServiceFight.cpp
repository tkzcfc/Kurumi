#include "ServiceFight.h"

#define ERR_GEN_WORD_NO_MEM -1
#define ERR_GEN_WORD_INIT_FAIL -2

uint32_t ServiceFight::onInit()
{
	m_seed = 0;
	m_arrFightInfo.reserve(20);
	return SCODE_START_SUCCESS;
}

void ServiceFight::onStartService()
{}

void ServiceFight::onStopService()
{}

void ServiceFight::onUpdate(float dt)
{
	for (auto& it : m_arrFightInfo)
	{
		// 没有玩家在世界中,将世界暂停
		if (it.onlineCount > 0)
		{
			it.logicWorld->update(dt);
		}
	}
}

void ServiceFight::onDestroy()
{
	while (m_arrFightInfo.size() > 0)
	{
		destroyWorld(m_arrFightInfo[0].worldId);
	}
}

int32_t ServiceFight::genNewWorld(int32_t mapId, FightPlayerInfo* arrInfo, int32_t playerCount)
{
	GGameWorld* world = new GGameWorld();
	if (world == NULL)
		return ERR_GEN_WORD_NO_MEM;
	if (!world->init(mapId))
	{
		delete world;
		return ERR_GEN_WORD_INIT_FAIL;
	}

	FightWorldInfo info;
	info.worldId = m_seed++;
	info.logicWorld = new GGameWorld();

	for (auto i = 0; i < G_FIGHT_MAX_PLAYER_COUNT; ++i)
	{
		auto& player = info.players[i];
		player.id = 0;
		player.online = false;
	}
	
	for (auto i = 0; i < playerCount; ++i)
	{
		info.players[i] = arrInfo[i];
	}


	updateWorldOnlineCount(&info);

	m_arrFightInfo.emplace_back(info);

	return info.worldId;
}

void ServiceFight::updateWorldOnlineCount(FightWorldInfo* info)
{
	int32_t count = 0;
	for (auto i = 0; i < G_FIGHT_MAX_PLAYER_COUNT; ++i)
	{
		if (info->players[i].online)
			count++;
	}
	info->onlineCount = count;
}

// 销毁世界
void ServiceFight::destroyWorld(int32_t worldId)
{
	for (auto it = m_arrFightInfo.begin(); it != m_arrFightInfo.end(); ++it)
	{
		if (it->worldId == worldId)
		{
			delete it->logicWorld;
			m_arrFightInfo.erase(it);
			break;
		}
	}
}

