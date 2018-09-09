#include "LuaFunctionBond.h"

LuaFunctionBond::LuaFunctionBond()
{}

LuaFunctionBond::~LuaFunctionBond()
{
	clearLuaHandle();
}

void LuaFunctionBond::registerLuaHandle(const std::string& name, const LuaFunction& handle)
{
	unregisterLuaHandle(name);

	LuaFunction* pHandle = new LuaFunction(handle);
	m_luaHandleMap.insert(std::make_pair(name, pHandle));
}

void LuaFunctionBond::unregisterLuaHandle(const std::string& name)
{
	auto it = m_luaHandleMap.find(name);
	if (it != m_luaHandleMap.end())
	{
		delete it->second;
		m_luaHandleMap.erase(it);
	}
}

void LuaFunctionBond::clearLuaHandle()
{
	for (const auto& it : m_luaHandleMap)
		delete it.second;
	m_luaHandleMap.clear();
}

LuaFunction* LuaFunctionBond::getLuaHandle(const std::string& name)
{
	auto it = m_luaHandleMap.find(name);
	if (it != m_luaHandleMap.end())
	{
		return it->second;
	}
	return NULL;
}
