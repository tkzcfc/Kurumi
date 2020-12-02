#pragma once

#ifdef __cplusplus
extern "C" 
{
#endif
#include "lua.h"
#include "lauxlib.h"
#include "tolua++.h"
#ifdef __cplusplus
}
#endif
#include "tolua_fix.h"
#include "tolua_ext.h"
#include "CCLuaEngine.h"

class LuaFunction
{
public:
	LuaFunction();

	explicit LuaFunction(int handle);

	LuaFunction(const LuaFunction& other) = delete;

	LuaFunction& operator=(const LuaFunction& rhs) = delete;

	LuaFunction(LuaFunction&& other);

	LuaFunction& operator=(LuaFunction&& rhs);

	LuaFunction& operator=(int handle);

	virtual ~LuaFunction();

	void operator()();

	template<typename...Args>
	void operator()(Args&...args)
	{
		ppush();
		pusharg(args...);
		pcall();
	}

	void ppush();

	int pcall();

	int pcallEx(int argc);

	bool isvalid();

	void ref(int handle);

	void unref();

	void pusharg(bool v);

	void pusharg(float v);

	void pusharg(double v);

	void pusharg(int v);

	void pusharg(unsigned int v);

	void pusharg(const std::string& v);

	void pusharg(const char* v);

	void pushlstring(const char* v, unsigned int len);

	void pushfunction(int handle);

	void pushnil();

	void pushobject(cocos2d::Ref* objectValue, const char* typeName);

	template<typename T>
	void pushusertype(void* v, const char* type)
	{
		if (m_stack != NULL)
		{
			tolua_ext_object_to_luaval<T>(m_stack->getLuaState(), v, type);
			m_argCount++;
		}
	}

	void pushLuaValue(const LuaValue& value);

	void pushLuaValueDict(const LuaValueDict& dict);

	void pushLuaValueArray(const LuaValueArray& array);

private:
	cocos2d::LuaStack* m_stack;
	int m_argCount;
	int m_luaHandle;
};
