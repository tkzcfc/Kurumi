#pragma once

#include "LuaFunction.hpp"
#include <map>
#include <string>

class LuaFunctionBond
{
public:
	LuaFunctionBond();

	virtual ~LuaFunctionBond();

	void registerLuaHandle(const std::string& name, const LuaFunction& handle);

	void unregisterLuaHandle(const std::string& name);

protected:

	void clearLuaHandle();

	LuaFunction* getLuaHandle(const std::string& name);

protected:

	std::map<std::string, LuaFunction*> m_luaHandleMap;
};
