
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
#include "gamecore/lua_gamecore.h"


static luaL_Reg modules[] = {
    { "cjson", luaopen_cjson_safe },
	{ "bit", luaopen_bit },
    { NULL, NULL }
};


void preload_lua_modules(lua_State *L)
{
	// load tolua...
	tolua_net_open(L);

	tolua_gamecore_open(L);

	//load pbc
	luaopen_protobuf_c(L);

	luaopen_lfs(L);

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
