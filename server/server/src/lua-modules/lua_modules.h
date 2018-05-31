#pragma once

#ifndef __LUA_MODULES_H__
#define __LUA_MODULES_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "lua.h"
#ifdef __cplusplus
}
#endif

extern void preload_lua_modules(lua_State *L);


#endif /* __LUA_MODULES_H__ */
