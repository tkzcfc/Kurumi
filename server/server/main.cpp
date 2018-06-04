#include "lua-modules/lua_modules.h"
#include "DUGame.h"

void lua_pre_register_all(lua_State* L)
{
	luaL_openlibs(L);
	preload_lua_modules(L);

	const luaL_reg global_functions[] =
	{
		{ "print", lua_print },
		{ "release_print",lua_release_print },
		{ nullptr, nullptr }
	};
	luaL_register(L, "_G", global_functions);
}

void main()
{
	const char* startlua = "lua_code/main.lua";

	auto instance = DUGame::getInstance();

	if (!instance->isFileExist(startlua))
	{
		return;
	}

	lua_State* L = instance->luaState();
	
	lua_pre_register_all(L);

	luaL_dofile(L, startlua);

	instance->setInterval(1 / 40.0f);
	instance->run();

	DUGame::destroy();
}

