#pragma once

#include "GCommon.h"
#include <unordered_map>


///////////////////////////////////////////////////////////////////////////////////////////
/// Component
///////////////////////////////////////////////////////////////////////////////////////////

class ComponentHelper
{
public:
	virtual anax::Component* addComponent(anax::Entity* entity) = 0;

	virtual anax::Component* getComponent(anax::Entity* entity) = 0;

	virtual void removeComponent(anax::Entity* entity) = 0;
	
	virtual bool hasComponent(anax::Entity* entity) = 0;

	anax::detail::TypeId typeId = 0;
};


#define DEFINE_COMPONENT(TYPE) class ComponentHelper_##TYPE : public ComponentHelper \
{ \
	public: \
	ComponentHelper_##TYPE() \
	{ \
		typeId = anax::ComponentTypeId<TYPE>(); \
	} \
	virtual anax::Component* addComponent(anax::Entity* entity) \
	{ \
		return &entity->addComponent<TYPE>(); \
	} \
	virtual anax::Component* getComponent(anax::Entity* entity) \
	{ \
		return &entity->getComponent<TYPE>(); \
	} \
	virtual void removeComponent(anax::Entity* entity) \
	{ \
		entity->removeComponent<TYPE>(); \
	} \
	virtual bool hasComponent(anax::Entity* entity) \
	{ \
		return entity->hasComponent<TYPE>(); \
	} \
};

#define IMPLEMENTATION_COMPONENT(TYPE) AnaxHelper::GComponentHelperMap[#TYPE] = new ComponentHelper_##TYPE();

///////////////////////////////////////////////////////////////////////////////////////////
/// System
///////////////////////////////////////////////////////////////////////////////////////////
class SystemHelper
{
public:
	virtual void addSystem(anax::World* world, void* sys) = 0;

	virtual void removeSystem(anax::World* world) = 0;

	virtual bool doesSystemExist(anax::World* world) = 0;

	virtual anax::World* getWorld(void* sys) = 0;

	anax::detail::TypeId typeId = 0;
};

#define DEFINE_SYSTEM(TYPE) class SystemHelper_##TYPE : public SystemHelper \
{ \
	public: \
	SystemHelper_##TYPE() \
	{ \
		typeId = anax::SystemTypeId<TYPE>(); \
		CCLOG("%s : %d", #TYPE, typeId); \
	} \
	virtual void addSystem(anax::World* world, void* sys) \
	{ \
		world->addSystem<TYPE>(*((TYPE*)sys)); \
	} \
	virtual void removeSystem(anax::World* world) \
	{ \
		return world->removeSystem<TYPE>(); \
	} \
	virtual bool doesSystemExist(anax::World* world) \
	{ \
		return world->doesSystemExist<TYPE>(); \
	} \
	anax::World* getWorld(void* sys) \
	{ \
		return &((TYPE*)sys)->getWorld();\
	} \
};

#define IMPLEMENTATION_SYSTEM(TYPE) AnaxHelper::GSystemHelperMap[#TYPE] = new SystemHelper_##TYPE();




//////////////////////////////////////////////////////////////////////////////
class AnaxHelper
{
public:
	static anax::Component* addComponent(anax::Entity* entity, const std::string& component)
	{
		return GComponentHelperMap[component]->addComponent(entity);
	}

	static anax::Component* getComponent(anax::Entity* entity, const std::string& component)
	{
		return GComponentHelperMap[component]->getComponent(entity);
	}

	static void removeComponent(anax::Entity* entity, const std::string& component)
	{
		GComponentHelperMap[component]->removeComponent(entity);
	}

	static bool hasComponent(anax::Entity* entity, const std::string& component)
	{
		return GComponentHelperMap[component]->hasComponent(entity);
	}

	static unsigned int getComponentTypeID(const std::string& component)
	{
		return (unsigned int)GComponentHelperMap[component]->typeId;
	}

	static void addSystem(anax::World* world, const std::string& systemName, void* sys)
	{
		GSystemHelperMap[systemName]->addSystem(world, sys);
	}

	static void removeSystem(anax::World* world, const std::string& systemName)
	{
		GSystemHelperMap[systemName]->removeSystem(world);
	}

	static bool doesSystemExist(anax::World* world, const std::string& systemName)
	{
		return GSystemHelperMap[systemName]->doesSystemExist(world);
	}

	static anax::World* getSystemWorld(const std::string& systemName, void* sys)
	{
		return GSystemHelperMap[systemName]->getWorld(sys);
	}

	static unsigned int getSystemTypeID(const std::string& systemName)
	{
		return (unsigned int)GSystemHelperMap[systemName]->typeId;
	}

	static void implementation();

	static std::unordered_map<std::string, SystemHelper*> GSystemHelperMap;
	static std::unordered_map<std::string, ComponentHelper*> GComponentHelperMap;
};
