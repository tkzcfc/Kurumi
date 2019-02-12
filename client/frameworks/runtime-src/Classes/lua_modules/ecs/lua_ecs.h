#pragma once

/*
** Lua binding: Client
** Generated automatically by tolua++-1.0.92 on Tue Apr 24 09:51:34 2018.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
TOLUA_API int luaopen_ecs(lua_State* tolua_S);
#endif