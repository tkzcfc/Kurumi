#include "MapFollowSystem.h"


MapFollowSystem::MapFollowSystem(GameMap* gameMap)
	: m_gameMap(gameMap)
{}

MapFollowSystem::~MapFollowSystem()
{}

void MapFollowSystem::update()
{
#if COCOS2D_DEBUG == 1
	auto drawNode = m_gameMap->getDrawNode();
	if (drawNode != NULL)
	{
		drawNode->clear();
	}
#endif
	auto &entities = getEntities();
	if (entities.empty())
	{
		return;
	}

	CC_ASSERT(entities.size() == 1);
	auto& component = entities[0].getComponent<MapFollowComponent>();
	auto& pos = component.m_owner->getPosition();
	m_gameMap->setViewPos(pos.x, pos.y);
}

void MapFollowSystem::resetGameMap(GameMap* gameMap)
{
	m_gameMap = gameMap;
}

