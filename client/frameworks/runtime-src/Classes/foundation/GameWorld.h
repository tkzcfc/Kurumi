#pragma once

#include "foundation/GameWorldBase.h"

class GameWorld : public GameWorldBase
{
public:

	GameWorld();

	virtual ~GameWorld();

	static GameWorld* create();

public:

	virtual bool init()override;

public:

	void enableBox2DPhysics(bool enable, float left_offset, float right_offset, float top_offset, float bottom_offset);

	void setGameMap(GameMap* gameMap);

	void setDebugEnable(bool enable);
	
	bool isEnableDebug();

public:

	inline GameMap* getGameMap();

protected:

	virtual void logicUpdate(float delta)override;

	virtual void onWorldDestroy()override;

protected:

#ifdef ENABLE_BOX2D_DEBUG_DRAW

	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

	void onDraw();

	GLESDebugDraw* m_physicsDebugDraw;
	cocos2d::CustomCommand _customCommand;
	cocos2d::Mat4 _modelViewMV;

#endif

protected:

	bool m_bDebugEnable;

	GameMap* m_gameMap;
	
	class Box2DSystem* m_box2DSystem;

	class MapFollowSystem* m_mapFollowSystem;

	class ArmatureCollisionSystem* m_armatureCollisionSystem;

	class UpdateSystem* m_updateSystem;
};


GameMap* GameWorld::getGameMap()
{
	return m_gameMap;
}
