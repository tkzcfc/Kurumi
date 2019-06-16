#pragma once

#include "cocos2d.h"
#include "ecs/anaxHelper.h"
#include "lua_function/LuaFunctionBond.h"
#include "foundation/GLES-Render.h"
#include "foundation/GameMap.h"
#include "GameMacro.h"

using namespace cocos2d;

class GameWorld : public Node, public LuaFunctionBond
{
public:

	GameWorld();

	virtual ~GameWorld();

	static GameWorld* create();

protected:

	virtual bool init()override;

	virtual void onExit()override;

public:

	void initWorld(GameMap* gameMap, float left_offset, float right_offset, float top_offset, float bottom_offset);

	void destroy(class Actor* actor);

	void setDebugEnable(bool enable);
	
	bool isEnableDebug();

	void setGameMap(GameMap* gameMap);

	float getValidWorldX(float inValue, float actorRadius);

	float getValidWorldY(float inValue, float actorRadius);

public:

	inline GameMap* getGameMap();

	inline anax::World* getWorld();

	inline anax::Entity* getAdmin();

	inline Node* getNode(int nodeTag);

protected:

	void logicUpdate(float delta);

	void onWorldDestroy();

	void clearDestroyList();

	void callLuaLogicUpdate(float delta);

#ifdef ENABLE_BOX2D_DEBUG_DRAW
protected:
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

	void onDraw();

	GLESDebugDraw* m_physicsDebugDraw;
	cocos2d::CustomCommand _customCommand;
	cocos2d::Mat4 _modelViewMV;
#endif

protected:

	anax::World m_world;

	anax::Entity m_admin;

	Node* m_nodeArr[GAMEWORLD_NODE_MAX];

	Vector<class Actor*> m_destroyActorList;

	Vec2 m_offsetX;
	Vec2 m_offsetY;

protected:

	bool m_bDebugEnable;

	GameMap* m_gameMap;
	
	class Box2DSystem* m_box2DSystem;

	class MapFollowSystem* m_mapFollowSystem;

	class ArmatureCollisionSystem* m_armatureCollisionSystem;

	class UpdateSystem* m_updateSystem;

	class FilterSystem* m_filterSystem;
};


anax::World* GameWorld::getWorld()
{
	return &m_world;
}

anax::Entity* GameWorld::getAdmin()
{
	return &m_admin;
}

Node* GameWorld::getNode(int nodeTag)
{
	CC_ASSERT(nodeTag >= GAMEWORLD_NODE_MAP && nodeTag < GAMEWORLD_NODE_MAX);
	return m_nodeArr[nodeTag];
}


GameMap* GameWorld::getGameMap()
{
	return m_gameMap;
}
