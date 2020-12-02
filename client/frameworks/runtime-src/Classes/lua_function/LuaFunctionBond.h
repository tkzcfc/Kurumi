#pragma once

#include "LuaFunction.h"
#include <unordered_map>
#include <string>

class LuaFunctionBond
{
public:
	LuaFunctionBond();

	virtual ~LuaFunctionBond();

	void registerLuaHandle(const std::string& name, int handle);

	void unregisterLuaHandle(const std::string& name);

	void clearLuaHandle();

	LuaFunction* getLuaHandle(const std::string& name);

protected:

	std::unordered_map<std::string, LuaFunction*> m_luaHandleMap;
};
