
#include "lua_modules.h"



#if __cplusplus
extern "C" {
#endif

#include "lfs.h"

#if __cplusplus
}
#endif

#include "tolua_fix.h"
//#include "lua_net.h"
#include "lua_dubase.h"
#include "lua_glog.h"

#ifdef __cplusplus
extern "C" {
#endif
	extern int luaopen_protobuf_c(lua_State *L);
#ifdef __cplusplus
}
#endif





void preload_lua_modules(lua_State *L)
{
	toluafix_open(L);
	//tolua_net_open(L);
	tolua_dubase_open(L);
	tolua_glog_open(L);
	// load pbc
	luaopen_protobuf_c(L);
	// lfs
	luaopen_lfs(L);
}
