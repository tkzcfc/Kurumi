#pragma once

#include <anax/detail/ClassTypeId.hpp>
#include <functional>
#include <string>

namespace anax
{

#define REGISTER_COMPONENT(TYPE) registerComponent(#TYPE, anax::ComponentTypeId<TYPE>(), [](anax::Component*){ return NULL; });

#define REGISTER_SYSTEM(TYPE) registerSystem(#TYPE, ComponentTypeId<TYPE>());


	class Component;
	//class System;

	void registerComponent(const std::string& componentName, detail::TypeId typeId, const std::function<Component*()>& func);

	Component* createComponent(const std::string& componentName);

	detail::TypeId getTypeIdByComponentName(const std::string& componentName);

	void registerSystem(const std::string& systemName, detail::TypeId typeId);

	detail::TypeId getTypeIdBySystemName(const std::string& componentName);

}