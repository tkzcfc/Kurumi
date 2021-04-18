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

#include "tolua_ext.h"


class LuaRetValue
{
public:

	LuaRetValue();

	virtual ~LuaRetValue();

	void setString(const char* value);

	void setNumber(lua_Number value);

	void setBool(bool value);

	void setUserdata(void* value);

	void setNil();

	std::string getString();

	int getInt();

	float getFloat();

	double getDouble();

	void* getUserdata();

	bool isNil();

	bool getBool();

private:

	void reset();

	union Value
	{
		std::string* svalue;
		lua_Number nvalue;
		bool bvalue;
		void* userdata;
	};

	/*
	#define LUA_TNONE		(-1)
	#define LUA_TNIL		0
	#define LUA_TBOOLEAN		1
	#define LUA_TLIGHTUSERDATA	2
	#define LUA_TNUMBER		3
	#define LUA_TSTRING		4
	#define LUA_TUSERDATA		7
	*/
	int m_type;
	union Value m_value;
};

class LuaFunction
{
public:
	static lua_State* G_L;

	static void setGlobalLuaState(lua_State* L);

	static lua_State* getGlobalLuaState();

public:

	LuaFunction();

	LuaFunction(lua_State* aL, int index, int def);

	LuaFunction(int ref);

	LuaFunction(const LuaFunction& other);

	LuaFunction& operator=(const LuaFunction& rhs);

	LuaFunction(LuaFunction&& other);

	LuaFunction& operator=(LuaFunction&& rhs);

	virtual ~LuaFunction();

	void operator()();

	void ppush();

	bool pcall(LuaRetValue* retarr = NULL, int nresults = 0);

	inline bool isvalid();

	inline void invalid();

	void ref(int handle);

	void unref();

	void push() const;

	template<typename...Args>
	void operator()(Args&...args)
	{
		ppush();
		pusharg(args...);
		pcall();
	}

	void pusharg(bool v);

	void pusharg(float v);

	void pusharg(double v);

	void pusharg(int v);

	void pusharg(unsigned int v);

	void pusharg(const std::string& v);

	void pusharg(const char* v);

	void pushlstring(const char* v, unsigned int len);

	template<typename T, typename... Args>
	inline void pusharg(T first, Args... args) {
		pusharg(first);
		pusharg(args...);
	}

	template<typename T>
	void pushusertype(void* v, const char* type)
	{
#if IS_IN_COCOS2D_X_LUA
		tolua_ext_object_to_luaval<T>(G_L, v, type);
#else
		tolua_pushusertype(G_L, v, type);
#endif
	}
	
private:
	int m_trackback;
	int m_ref;
};

bool LuaFunction::isvalid()
{
	return (m_ref > 0);
}

void LuaFunction::invalid()
{
	this->unref();
}


