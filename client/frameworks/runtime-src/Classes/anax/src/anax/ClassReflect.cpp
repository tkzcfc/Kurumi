#include "anax/ClassReflect.h"
#include <unordered_map>

namespace anax
{
	struct ComponentData
	{
		std::function<Component*()> func;
		detail::TypeId typeId;
	};

	struct SystemData
	{
		detail::TypeId typeId;
	};

	std::unordered_map<std::string, ComponentData> g_reflectComponentMap;
	std::unordered_map<std::string, SystemData> g_reflectSystemMap;

	void registerComponent(const std::string& componentName, detail::TypeId typeId, const std::function<Component*()>& func)
	{
		ComponentData data;
		data.func = std::move(func);
		data.typeId = typeId;
		g_reflectComponentMap.emplace(componentName, data);
	}

	detail::TypeId getTypeIdByComponentName(const std::string& componentName)
	{
		return g_reflectComponentMap[componentName].typeId;
	}

	Component* createComponent(const std::string& componentName)
	{
		return g_reflectComponentMap[componentName].func();
	}

	/*void registerSystem(const std::string& systemName, detail::TypeId typeId)
	{
		SystemData data;
		data.typeId = typeId;
		g_reflectSystemMap.emplace(systemName, data);
	}

	detail::TypeId getTypeIdBySystemName(const std::string& componentName)
	{
		return g_reflectSystemMap[componentName].typeId;
	}*/
}
