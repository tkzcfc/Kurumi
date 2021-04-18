
#include "lua_modules.h"


#include "LuaBasicConversions.h"
#include "ext/MyButton.h"


#if __cplusplus
extern "C" {
#endif

// cjson
#include "cjson/lua_cjson.h"
//lfs
#include "lfs/lfs.h"
//bit
extern int luaopen_bit(lua_State *L);
//pbc
extern int luaopen_protobuf_c(lua_State *L);

#if __cplusplus
} /// extern "C"
#endif

#include "assets/game_assets_tolua.h"
#include "http/lua_http.hpp"
#include "md5/lua_md5.hpp"
#include "game/lua_game.h"

static luaL_Reg modules[] = {
    { "cjson", luaopen_cjson_safe },
	{ "bit", luaopen_bit },
	{ "http", luaopen_http },
	{ "md5", luaopen_md5 },
    { NULL, NULL }
};

void preload_lua_modules(lua_State *L)
{
	LuaFunction::setGlobalLuaState(L);

	luaopen_game(L);

	//load pbc
	luaopen_protobuf_c(L);
	//lfs
	luaopen_lfs(L);
	// assets
	luaopen_game_assets(L);

    // load extensions
    luaL_Reg* lib = modules;
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "preload");
    for (; lib->func; lib++)
    {
        lua_pushcfunction(L, lib->func);
        lua_setfield(L, -2, lib->name);
    }
    lua_pop(L, 2);


	std::string typeName = typeid(MyButton).name();
	g_luaType[typeName] = "MyButton";
	g_typeCast["MyButton"] = "MyButton";
}
