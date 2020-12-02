#pragma once
#ifndef __LUA_MD5_HPP__
#define __LUA_MD5_HPP__

#if __cplusplus
extern "C" {
#endif

#include "lua.h"
#include "lauxlib.h"


int luaopen_md5(lua_State *L);

#if __cplusplus
}
#endif




#endif
