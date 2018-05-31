-- usage: (use instead of ant)
-- tolua++ "-L" "basic.lua" "-o" "../../scripting/lua/cocos2dx_support/LuaCocos2d.cpp" "Cocos2d.pkg"

_is_functions = _is_functions or {}
_to_functions = _to_functions or {}
_push_functions = _push_functions or {}


-- register LUA_FUNCTION, LUA_TABLE, LUA_HANDLE type
-- _to_functions["LUA_FUNCTION"] = "toluafix_ref_function"


_to_functions["LuaFunction"] = "LuaFunction"
_is_functions["LuaFunction"] = "toluafix_isfunction"

_to_functions["LUA_TABLE"] = "toluafix_totable"
_is_functions["LUA_TABLE"] = "toluafix_istable"

local toWrite = {}
local currentString = ''
local out
local WRITE, OUTPUT = write, output

function output(s)
    out = _OUTPUT
    output = OUTPUT -- restore
    output(s)
end

function write(a)
    if out == _OUTPUT then
        currentString = currentString .. a
        if string.sub(currentString,-1) == '\n'  then
            toWrite[#toWrite+1] = currentString
            currentString = ''
        end
    else
        WRITE(a)
    end
end

function post_output_hook(package)
    local result = table.concat(toWrite)
    local function replace(pattern, replacement)
        local k = 0
        local nxt, currentString = 1, ''
        repeat
            local s, e = string.find(result, pattern, nxt, true)
            if e then
                currentString = currentString .. string.sub(result, nxt, s-1) .. replacement
                nxt = e + 1
                k = k + 1
            end
        until not e
        result = currentString..string.sub(result, nxt)
        if k == 0 then print('Pattern not replaced', pattern) end
    end

    replace([[#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"]],
    [[
#include "tolua_fix.h"
#include "tolua++.h"
#include <string>
]])

      --replace([[*((LUA_FUNCTION*)]], [[(]])

      --replace([[tolua_usertype(tolua_S,"LUA_FUNCTION");]], [[]])

      replace([[tolua_usertype(tolua_S,"LuaFunction");]], [[]])

      replace([[*((LuaFunction*)]], [[(]])

      replace('\t', '    ')

    WRITE(result)
end

