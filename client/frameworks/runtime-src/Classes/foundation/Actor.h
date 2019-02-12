#pragma once

#include "ecs/anaxHelper.h"
#include "lua_function/LuaFunctionBond.h"
#include "foundation/GameWorld.h"

using namespace cocos2d;

class Actor : public Node , public LuaFunctionBond
{
public:

	Actor(GameWorldBase* world);

	virtual ~Actor();

	static Actor* create(GameWorldBase* world);
	
	virtual void onExit()override;

public:

	void destroy();

public:

	inline GameWorldBase* getGameWorld();

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

	GameWorldBase* m_gameWorld;

};

GameWorldBase* Actor::getGameWorld()
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

