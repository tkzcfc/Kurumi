#pragma once

#include "ecs/anaxHelper.h"
#include "lua_function/LuaFunctionBond.h"
#include "foundation/GameWorld.h"

using namespace cocos2d;

class Actor : public Node , public LuaFunctionBond
{
public:

	Actor(GameWorld* world);

	virtual ~Actor();

	static Actor* create(GameWorld* world);
	
	virtual void onExit()override;

public:

	void destroy();

	void setFilterData(int inValue);

	int getFilterData();

public:

	inline GameWorld* getGameWorld();

	inline anax::Entity* getEntity();

	/// helper
	inline anax::Component* addAnaxComponent(const std::string& component);

	inline anax::Component* getAnaxComponent(const std::string& component);

	inline void removeAnaxComponent(const std::string& component);

	inline bool hasAnaxComponent(const std::string& component);

protected:

	virtual void killEntity();

protected:

	anax::Entity m_entity;

	GameWorld* m_gameWorld;

};

GameWorld* Actor::getGameWorld()
{
	return m_gameWorld;
}

anax::Entity* Actor::getEntity()
{
	return &m_entity;
}

/// helper
anax::Component* Actor::addAnaxComponent(const std::string& component)
{
	return AnaxHelper::addComponent(&m_entity, component);
}

anax::Component* Actor::getAnaxComponent(const std::string& component)
{
	return AnaxHelper::getComponent(&m_entity, component);
}

void Actor::removeAnaxComponent(const std::string& component)
{
	AnaxHelper::removeComponent(&m_entity, component);
}

bool Actor::hasAnaxComponent(const std::string& component)
{
	return AnaxHelper::hasComponent(&m_entity, component);
}

