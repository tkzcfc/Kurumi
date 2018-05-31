
#include <iostream>
#include <chrono>

#ifdef __cplusplus
extern "C" {
#endif
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#ifdef __cplusplus
}
#endif


#include "lua-modules/lua_modules.h"

#include "DUGame.h"


void main()
{
	lua_State* L = luaL_newstate();

	luaL_openlibs(L);
	preload_lua_modules(L);

	luaL_dofile(L, "lua_code/main.lua");

	auto instance = DUGame::getInstance();
	instance->setInterval(1 / 40.0f);
	instance->run();

	DUGame::destroy();

	lua_close(L);
}


















