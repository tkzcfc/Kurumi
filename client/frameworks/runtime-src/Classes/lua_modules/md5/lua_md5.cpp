#include "lua_md5.hpp"

#include "md5.h"

static int sum(lua_State* L)
{
    size_t sz;
    const char* str = luaL_checklstring(L, 1, &sz);
    MD5 md5;
    std::string v = md5(str, sz);
    lua_pushlstring(L, v.data(), v.size());
    return 1;
}

int luaopen_md5(lua_State *L)
{
    lua_newtable(L);
    lua_pushliteral(L, "sum");
    lua_pushcfunction(L, sum);
    lua_settable(L, -3);
    return 1;
}
