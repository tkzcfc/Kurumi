#pragma once

#include "LuaFunction.h"
#include <map>
#include <string>

class LuaFunctionBond
{
public:
	LuaFunctionBond();

	virtual ~LuaFunctionBond();

	void registerLuaHandle(const std::string& name, const LuaFunction& handle);

	void unregisterLuaHandle(const std::string& name);

	void clearLuaHandle();

protected:

	LuaFunction* getLuaHandle(const std::string& name);

protected:

	std::map<std::string, LuaFunction*> m_luaHandleMap;
};
