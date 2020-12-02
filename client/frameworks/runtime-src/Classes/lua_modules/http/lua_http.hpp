#pragma once
#ifndef __LUA_HTTP_HPP__
#define __LUA_HTTP_HPP__

#if __cplusplus
extern "C" {
#endif

#include "lua.h"
#include "lauxlib.h"


int luaopen_http(lua_State *L);

#if __cplusplus
}
#endif




#endif
