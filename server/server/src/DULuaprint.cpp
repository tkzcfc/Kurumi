#include "DULuaprint.h"
#include "DUObject.h"
#define GLOG_NO_ABBREVIATED_SEVERITIES 
#include "glog/logging.h"

int lua_print(lua_State * luastate)
{
	int nargs = lua_gettop(luastate);

	std::string t;
	for (int i = 1; i <= nargs; i++)
	{
		if (lua_istable(luastate, i))
			t += "table";
		else if (lua_isnone(luastate, i))
			t += "none";
		else if (lua_isnil(luastate, i))
			t += "nil";
		else if (lua_isboolean(luastate, i))
		{
			if (lua_toboolean(luastate, i) != 0)
				t += "true";
			else
				t += "false";
		}
		else if (lua_isfunction(luastate, i))
			t += "function";
		else if (lua_islightuserdata(luastate, i))
			t += "lightuserdata";
		else if (lua_isthread(luastate, i))
			t += "thread";
		else
		{
			const char * str = lua_tostring(luastate, i);
			if (str)
				t += lua_tostring(luastate, i);
			else
				t += lua_typename(luastate, lua_type(luastate, i));
		}
		if (i != nargs)
			t += "\t";
	}
	//DU_LOG("[LUA-print] %s", t.c_str());
	//LOG(INFO) << "[LUA-print]" << t;
	printf("[LUA-print] %s\n", t.c_str());

	return 0;
}

int lua_release_print(lua_State * L)
{
	int nargs = lua_gettop(L);

	std::string t;
	for (int i = 1; i <= nargs; i++)
	{
		if (lua_istable(L, i))
			t += "table";
		else if (lua_isnone(L, i))
			t += "none";
		else if (lua_isnil(L, i))
			t += "nil";
		else if (lua_isboolean(L, i))
		{
			if (lua_toboolean(L, i) != 0)
				t += "true";
			else
				t += "false";
		}
		else if (lua_isfunction(L, i))
			t += "function";
		else if (lua_islightuserdata(L, i))
			t += "lightuserdata";
		else if (lua_isthread(L, i))
			t += "thread";
		else
		{
			const char * str = lua_tostring(L, i);
			if (str)
				t += lua_tostring(L, i);
			else
				t += lua_typename(L, lua_type(L, i));
		}
		if (i != nargs)
			t += "\t";
	}
	//MyLog("[LUA-print] %s", t.c_str());
	LOG(WARNING) << "[LUA-print]" << t;

	return 0;
}