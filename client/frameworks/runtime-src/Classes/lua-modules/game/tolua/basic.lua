-- usage: (use instead of ant)
-- tolua++ "-L" "basic.lua" "-o" "ctest_tolua.cpp"  "CTest.pkg"

_is_functions = _is_functions or {}
_to_functions = _to_functions or {}
_push_functions = _push_functions or {}


-- register LUA_FUNCTION, LUA_TABLE, LUA_HANDLE type
-- _to_functions["LUA_FUNCTION"] = "toluafix_ref_function"



--[[
特殊类型
MAP_STRING_STRING : std::map<std::string,std::string>
]]


_to_functions["LuaFunction"] = "LuaFunction"
_is_functions["LuaFunction"] = "toluafix_isfunction"
_to_functions["const LuaFunction"] = "LuaFunction"
_is_functions["const LuaFunction"] = "toluafix_isfunction"


---------------------------------------------------------------------------
local checkMap = {}
checkMap["std::map<std::string,std::string>"]       = { checkfunc = "tolua_ext_check_is_table", typedef = "MAP_STRING_STRING" }
checkMap["std::map<std::string,int>"]               = { checkfunc = "tolua_ext_check_is_table", typedef = "MAP_STRING_INT" }
checkMap["std::map<std::string,float>"]             = { checkfunc = "tolua_ext_check_is_table", typedef = "MAP_STRING_FLOAT" }
checkMap["std::map<std::string,double>"]            = { checkfunc = "tolua_ext_check_is_table", typedef = "MAP_STRING_DOUBLE" }
checkMap["std::vector<std::string>"]                = { checkfunc = "tolua_ext_check_is_table", typedef = "VECTOR_STRING" }
checkMap["std::vector<int>"]                        = { checkfunc = "tolua_ext_check_is_table", typedef = "VECTOR_INT" }
checkMap["std::vector<float>"]                      = { checkfunc = "tolua_ext_check_is_table", typedef = "VECTOR_FLOAT" }
checkMap["std::vector<double>"]                     = { checkfunc = "tolua_ext_check_is_table", typedef = "VECTOR_DOUBLE" }
checkMap["Vec2"]                                    = { checkfunc = "tolua_ext_check_is_table", typedef = "VEC2_VALUE" }
checkMap["Vec3"]                                    = { checkfunc = "tolua_ext_check_is_table", typedef = "VEC3_VALUE" }
checkMap["Size"]                                    = { checkfunc = "tolua_ext_check_is_table", typedef = "SIZE_VALUE" }
checkMap["Rect"]                                    = { checkfunc = "tolua_ext_check_is_table", typedef = "RECT_VALUE" }

checkMap["b2Vec2"]                                  = { checkfunc = "tolua_ext_check_is_table" }


local typedefcheckMap = {}
for k,v in pairs(checkMap) do
    if v.typedef ~= nil and v.typedef ~= "" then
        typedefcheckMap[v.typedef] = { checkfunc = v.checkfunc }
    end
end

for k,v in pairs(typedefcheckMap) do
    checkMap[k] = v
end

local const_checkMap = {}

local toluaValMap = {}
for k, v in pairs(checkMap) do
    local typedef = v.typedef
    if typedef == nil or typedef == "" then
        typedef = k
    end

	local lowerstr = string.lower(typedef)
	local tolua_ext_to_luaval = "tolua_ext_"..lowerstr.."_to_luaval"
	local tolua_ext_luaval_tol = "tolua_ext_luaval_to_"..lowerstr
	
	toluaValMap[k] = tolua_ext_to_luaval
	_to_functions[k] = tolua_ext_luaval_tol
	_is_functions[k] = v.checkfunc
	
	local const_key = "const "..k
	const_checkMap[const_key] = v
	toluaValMap[const_key] = tolua_ext_to_luaval
	_to_functions[const_key] = tolua_ext_luaval_tol
	_is_functions[const_key] = v.checkfunc
end

for k, v in pairs(const_checkMap) do
	checkMap[k] = v
end


---------------------------------------------------------------------------

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
        --if k == 0 then print('Pattern not replaced', pattern) end
    end

      replace([[tolua_usertype(tolua_S,"LuaFunction");]], [[]])
      replace([[*((LuaFunction*)]], [[(]])
	  replace([[tolua_usertype(tolua_S,"const LuaFunction");]], [[]])
      replace([[*((const LuaFunction*)]], [[(]])
	  
	  replace([[#ifndef TOLUA_RELEASE]], [[#if (COCOS2D_DEBUG == 1)]])
      replace([[cc.Node*]], [[Node*]])
      replace([[ccs.Armature*]], [[Armature*]])
	  
	  for k, v in pairs(checkMap) do
			replace(string.format("*((%s*)", k), "(")
		
			local oldstr = string.format([[
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((%s)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"%s");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(%s));
     tolua_pushusertype(tolua_S,tolua_obj,"%s");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
]], k, k, k, k)
			local newstr = string.format("\t%s(tolua_S, tolua_ret);\n", toluaValMap[k])
			replace(oldstr, newstr)
		
			oldstr = string.format([[
tolua_usertype(tolua_S,"%s");
]], k)
			replace(oldstr, "")
			
		end
	  
	  
	  
      replace('\t', '    ')
	  
	  
	  
	  
	  replace([[
#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"]], 
[[#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"
#include "tolua++.h"
#include "lua_function/tolua_ext.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
]])

    WRITE(result)
end

