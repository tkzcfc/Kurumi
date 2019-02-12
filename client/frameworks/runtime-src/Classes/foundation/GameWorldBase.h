#pragma once
#pragma once

#include "cocos2d.h"
#include "ecs/anaxHelper.h"
#include "lua_function/LuaFunctionBond.h"
#include "foundation/GLES-Render.h"
#include "foundation/GameMap.h"
#include "GameMacro.h"

using namespace cocos2d;

class GameWorldBase : public Node, public LuaFunctionBond
{
public:

	GameWorldBase();

	virtual ~GameWorldBase();

	static GameWorldBase* create();

	virtual bool init()override;

	void destroy(class Actor* actor);

public:

	inline anax::World* getWorld();

	inline anax::Entity* getAdmin();

	inline Node* getNode(int nodeTag);

protected:

	virtual void logicUpdate(float delta);

	virtual void onWorldDestroy();

protected:

	void clearDestroyList();

	void callLuaLogicUpdate(float delta);

protected:

	anax::World m_world;

	anax::Entity m_admin;

	Node* m_nodeArr[GAMEWORLD_NODE_MAX];

	Vector<class Actor*> m_destroyActorList;
};

anax::World* GameWorldBase::getWorld()
{
	return &m_world;
}

anax::Entity* GameWorldBase::getAdmin()
{
	return &m_admin;
}

Node* GameWorldBase::getNode(int nodeTag)
{
	CC_ASSERT(nodeTag >= GAMEWORLD_NODE_MAP && nodeTag < GAMEWORLD_NODE_MAX);
	return m_nodeArr[nodeTag];
}


