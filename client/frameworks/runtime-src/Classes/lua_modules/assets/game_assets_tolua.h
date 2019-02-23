#include "tolua++.h"

/* Exported function */
#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
TOLUA_API int luaopen_game_assets(lua_State* tolua_S);
#endif