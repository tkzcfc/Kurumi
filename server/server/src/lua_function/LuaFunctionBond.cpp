#include "LuaFunctionBond.h"

LuaFunctionBond::LuaFunctionBond()
{}

LuaFunctionBond::~LuaFunctionBond()
{
	for (const auto& it : m_luaHandleMap)
	{
		delete it.second;
	}
	m_luaHandleMap.clear();
}

void LuaFunctionBond::registerLuaHandle(const std::string& name, const LuaFunction& handle)
{
	auto it = m_luaHandleMap.find(name);
	if (it != m_luaHandleMap.end())
	{
		*it->second = handle;
	}
	else
	{
		LuaFunction* pHandle = new LuaFunction(handle);
		m_luaHandleMap.insert(std::make_pair(name, pHandle));
	}
}

void LuaFunctionBond::unregisterLuaHandle(const std::string& name)
{
	auto it = m_luaHandleMap.find(name);
	if (it != m_luaHandleMap.end())
	{
		it->second->invalid();
	}
}

void LuaFunctionBond::clearLuaHandle()
{
	for (const auto& it : m_luaHandleMap)
	{
		it.second->invalid();
	}
}

LuaFunction* LuaFunctionBond::getLuaHandle(const std::string& name)
{
	auto it = m_luaHandleMap.find(name);
	if (it != m_luaHandleMap.end() && it->second->isvalid())
	{
		return it->second;
	}
	return NULL;
}
