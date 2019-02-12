#pragma once

#include "ecs/components/MapFollowComponent.h"
#include "foundation/GameMap.h"

class MapFollowSystem : public anax::System<anax::Requires<MapFollowComponent>>, public Ref
{
public:

	MapFollowSystem(GameMap* gameMap);

	virtual ~MapFollowSystem();

	void update();

	void resetGameMap(GameMap* gameMap);

protected:

	GameMap* m_gameMap;

};

DEFINE_SYSTEM(MapFollowSystem);
