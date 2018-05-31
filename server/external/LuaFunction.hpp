#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include "lua.h"
#include "lauxlib.h"
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include <string>

class LuaRef {
public:
	LuaRef();
	LuaRef(lua_State* aL, int index);
	virtual ~LuaRef();
	LuaRef(const LuaRef& other);
	LuaRef& operator=(const LuaRef& rhs);
	LuaRef(LuaRef&& other);
	LuaRef& operator=(LuaRef&& rhs);
	explicit operator bool() const;
	void reset(lua_State* aL, int index);
	void push() const;
	lua_State* state() const;
protected:
	void unref() const;
protected:
	lua_State* L;
	int ref_;
};



class LuaFunction : public LuaRef
{
public:
	LuaFunction();
	LuaFunction(lua_State* aL, int index, int);
	LuaFunction(const LuaFunction& other);
	LuaFunction& operator=(const LuaFunction& rhs);
	LuaFunction(LuaFunction&& other);
	LuaFunction& operator=(LuaFunction&& rhs);
	~LuaFunction();

	void operator()();
	void ppush();
	void pcall(int nresults = 0);
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
	template<typename T, typename... Args>
	inline void pusharg(T first, Args... args) {
		pusharg(first);
		pusharg(args...);
	}
	void pushusertype(void* v, const char* type);

	bool retbool(int index = 0, bool defaultvalue = false);
	int retint(int index = 0, int defaultvalue = 0);
	std::string retstring(int index = 0, const std::string& defaultvalue = "");
	int checktype(int index = 0);
	int retcount();

private:

	void clear_ret();

private:
	mutable int m_trackback;

	const static unsigned int MAX_RET_ARGS_COUNT = 5;

	union LuaRetValue
	{
		std::string* stringValue;
		int numberValue;
		bool boolValue;
	};
	struct LuaRetData
	{
		LuaRetData()
		{
			type = LUA_TNONE;
		}
		union LuaRetValue value;
		
		/*
		#define LUA_TNONE		(-1)

		#define LUA_TNIL		0
		#define LUA_TBOOLEAN		1
		#define LUA_TNUMBER		3
		#define LUA_TSTRING		4
		*/
		int type;
	};
	LuaRetData m_retValues[MAX_RET_ARGS_COUNT];
	int m_retCount;
};
