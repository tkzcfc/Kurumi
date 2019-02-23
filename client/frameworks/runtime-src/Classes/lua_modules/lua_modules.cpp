
#include "lua_modules.h"


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

#include "net/lua_net.h"
//#include "game/lua_game.h"
#include "foundation/lua_foundation.h"
#include "ecs/lua_ecs.h"
#include "assets/game_assets_tolua.h"

static luaL_Reg modules[] = {
    { "cjson", luaopen_cjson_safe },
	{ "bit", luaopen_bit },
    { NULL, NULL }
};

void preload_lua_modules(lua_State *L)
{
	// net
	luaopen_net(L);

	// game
	//luaopen_game(L);

	// foundation
	luaopen_foundation(L);

	// ecs
	luaopen_ecs(L);

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
}
