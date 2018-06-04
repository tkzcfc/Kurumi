#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#ifdef __cplusplus
}
#endif

extern int lua_print(lua_State * luastate);
extern int lua_release_print(lua_State * L);