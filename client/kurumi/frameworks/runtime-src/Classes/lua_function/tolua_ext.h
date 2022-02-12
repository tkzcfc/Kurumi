#pragma once

#define IS_IN_COCOS2D_X_LUA 1

#if IS_IN_COCOS2D_X_LUA
#include "cocos2d.h"
//#include "Box2D/Box2D.h"
#include "tolua_fix.h"
#endif

#include "tolua++.h"

#include <map>
#include <string.h>
#include <vector>
#include "mugen/geometry/GGeometry.h"



#if IS_IN_COCOS2D_X_LUA
using namespace cocos2d;

#define DEF_VEC_2_VALUE
#define DEF_VEC_3_VALUE
#define DEF_SIZE_VALUE
#define DEF_RECT_VALUE

#else
#if _DEBUG
#define COCOS2D_DEBUG 1
#else
#define COCOS2D_DEBUG 0
#endif
#endif

typedef int LUA_FUNCTION;


#ifndef DEF_VEC_2_VALUE
struct Vec2
{
	float x = 0.0f;
	float y = 0.0f;
};
#endif

#ifndef DEF_VEC_3_VALUE
struct Vec3
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};
#endif

#ifndef DEF_SIZE_VALUE
struct Size
{
	float width = 0.0f;
	float height = 0.0f;
};
#endif

#ifndef DEF_RECT_VALUE
struct Rect
{
	Vec2 origin;
	Size size;
};
#endif


void tolua_ext_open(lua_State* L);

// 
int tolua_ext_check_is_table(lua_State* L, int lo, const char* type, int def, tolua_Error* err);
int tolua_ext_check_isfunction(lua_State* L, int lo, const char* type, int def, tolua_Error* err);


// function
void tolua_ext_function_to_luaval(lua_State* L, void* funcPtr, const char* type);

void* tolua_ext_luaval_to_function(lua_State* L, int narg, void* def);

int tolua_ext_ref_function(lua_State* L, int lo, int def);

void tolua_ext_get_function_by_refid(lua_State* L, int refid);

void tolua_ext_remove_function_by_refid(lua_State* L, int refid);

// map
void tolua_ext_map_string_string_to_luaval(lua_State* L, const std::map<std::string, std::string>& v, const char*);
void tolua_ext_map_string_int_to_luaval(lua_State* L, const std::map<std::string, int>& v, const char*);
void tolua_ext_map_string_float_to_luaval(lua_State* L, const std::map<std::string, float>& v, const char*);
void tolua_ext_map_string_double_to_luaval(lua_State* L, const std::map<std::string, double>& v, const char*);

std::map<std::string, std::string>&	tolua_ext_luaval_to_map_string_string(lua_State* L, int lo, int);
std::map<std::string, int>&			tolua_ext_luaval_to_map_string_int(lua_State* L, int lo, int);
std::map<std::string, float>&			tolua_ext_luaval_to_map_string_float(lua_State* L, int lo, int);
std::map<std::string, double>&		tolua_ext_luaval_to_map_string_double(lua_State* L, int lo, int);

//vector
void tolua_ext_vector_string_to_luaval(lua_State* L, const std::vector<std::string>& v, const char*);
void tolua_ext_vector_int_to_luaval(lua_State* L, const std::vector<int>& v, const char*);
void tolua_ext_vector_float_to_luaval(lua_State* L, const std::vector<float>& v, const char*);
void tolua_ext_vector_double_to_luaval(lua_State* L, const std::vector<double>& v, const char*);
void tolua_ext_vector_vec2_to_luaval(lua_State* L, const std::vector<Vec2>& v, const char*);

std::vector<std::string>&		tolua_ext_luaval_to_vector_string(lua_State* L, int lo, int);
std::vector<int>&				tolua_ext_luaval_to_vector_int(lua_State* L, int lo, int);
std::vector<float>&			tolua_ext_luaval_to_vector_float(lua_State* L, int lo, int);
std::vector<double>&			tolua_ext_luaval_to_vector_double(lua_State* L, int lo, int);
std::vector<Vec2>&			tolua_ext_luaval_to_vector_vec2(lua_State* L, int lo, int);


// vec2、vec3、size、rect
void tolua_ext_vec2_value_to_luaval(lua_State* L, const Vec2& v, const char*);
void tolua_ext_vec3_value_to_luaval(lua_State* L, const Vec3& v, const char*);
void tolua_ext_fvec2_value_to_luaval(lua_State* L, const NS_G::GFixedVec2& v, const char*);
void tolua_ext_fvec3_value_to_luaval(lua_State* L, const NS_G::GFixedVec3& v, const char*);
void tolua_ext_size_value_to_luaval(lua_State* L, const Size& v, const char*);
void tolua_ext_rect_value_to_luaval(lua_State* L, const Rect& v, const char*);

Vec2			tolua_ext_luaval_to_vec2_value(lua_State* L, int lo, int);
Vec3			tolua_ext_luaval_to_vec3_value(lua_State* L, int lo, int);
NS_G::GFixedVec2			tolua_ext_luaval_to_fvec2_value(lua_State* L, int lo, int);
NS_G::GFixedVec3			tolua_ext_luaval_to_fvec3_value(lua_State* L, int lo, int);
Size			tolua_ext_luaval_to_size_value(lua_State* L, int lo, int);
Rect			tolua_ext_luaval_to_rect_value(lua_State* L, int lo, int);

template <class T>
void tolua_ext_object_to_luaval(lua_State* L, void* ret, const char* type)
{
	if (nullptr != ret)
	{
#if IS_IN_COCOS2D_X_LUA
		if (std::is_base_of<cocos2d::Ref, T>::value)
		{
			// use c style cast, T may not polymorphic
			cocos2d::Ref* dynObject = (cocos2d::Ref*)(ret);
			int ID = (int)(dynObject->_ID);
			int* luaID = &(dynObject->_luaID);
			toluafix_pushusertype_ccobject(L, ID, luaID, (void*)ret, type);
		}
		else
#endif
		{
			tolua_pushusertype(L, (void*)ret, type);
		}
	}
	else
	{
		lua_pushnil(L);
	}
}

// std::vector<Object*>
template <class T>
void tolua_ext_object_arr_to_luaval(lua_State* L, std::vector<T*>& inValue, const char* type)
{
	lua_newtable(L);

	if (nullptr == L)
		return;


	std::string strType = type;
	auto xpos = strType.find("<");
	auto dpos = strType.find(">");

	if (xpos == std::string::npos || dpos == std::string::npos)
	{
		return;
	}

	strType = strType.substr(xpos + 1, dpos - xpos - 1);

	std::string classType;
	for (auto i = 0; i < strType.size(); ++i)
	{
		if (strType[i] != ' ' && strType[i] != '*')
		{
			classType.push_back(strType[i]);
		}
	}

	int indexTable = 1;
	for (const auto& obj : inValue)
	{
		if (nullptr == obj)
			continue;

		lua_pushnumber(L, (lua_Number)indexTable);

#if IS_IN_COCOS2D_X_LUA
		if (std::is_base_of<cocos2d::Ref, T>::value)
		{
			cocos2d::Ref* dynObject = (cocos2d::Ref*)(obj);
			int ID = (dynObject) ? (int)dynObject->_ID : -1;
			int* luaID = (dynObject) ? &dynObject->_luaID : NULL;
			toluafix_pushusertype_ccobject(L, ID, luaID, (void*)dynObject, classType.c_str());
		}
		else
#endif
		{
			tolua_pushusertype(L, (void*)obj, classType.c_str());
		}
		lua_rawset(L, -3);
		++indexTable;
	}
}

// std::map<std::string, Object*>
template <class T>
void tolua_ext_map_string_object_to_luaval(lua_State* L, std::map<std::string, T*>& inValue, const char* type)
{
	lua_newtable(L);

	if (nullptr == L)
		return;


	std::string strType = type;
	auto xpos = strType.find(",");
	auto dpos = strType.find(">");

	if (xpos == std::string::npos || dpos == std::string::npos)
	{
		return;
	}

	strType = strType.substr(xpos + 1, dpos - xpos - 1);

	std::string classType;
	for (auto i = 0; i < strType.size(); ++i)
	{
		if (strType[i] != ' ' && strType[i] != '*')
		{
			classType.push_back(strType[i]);
		}
	}

	for (const auto& obj : inValue)
	{
		if (nullptr == obj.second)
			continue;

		lua_pushstring(L, obj.first.c_str());

#if IS_IN_COCOS2D_X_LUA
		if (std::is_base_of<cocos2d::Ref, T>::value)
		{
			cocos2d::Ref* dynObject = (cocos2d::Ref*)(obj.second);
			int ID = (dynObject) ? (int)dynObject->_ID : -1;
			int* luaID = (dynObject) ? &dynObject->_luaID : NULL;
			toluafix_pushusertype_ccobject(L, ID, luaID, (void*)dynObject, classType.c_str());
		}
		else
#endif
		{
			tolua_pushusertype(L, (void*)obj.second, classType.c_str());
		}
		lua_rawset(L, -3);
	}
}


template <class T>
std::vector<T*> tolua_ext_luaval_to_ccvector(lua_State* L, int lo, int)
{
	std::vector<T*> outValue;

	if (nullptr == L)
	{
		return outValue;
	}

	tolua_Error tolua_err;
	if (!tolua_istable(L, lo, 0, &tolua_err))
	{
		return outValue;
	}

	lua_pushvalue(L, lo);
	int len = lua_objlen(L, -1);
	outValue.reserve(len);
	for (int i = 1; i <= len; i++)
	{
		lua_pushinteger(L, i);
		lua_gettable(L, -2);
		/* 此时栈顶即为 t[i] 元素 */
		if (lua_isuserdata(L, -1))
		{
			T* cobj = static_cast<T*>(tolua_tousertype(L, -1, NULL));
			outValue.emplace_back(cobj);
		}
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
	return outValue;
}


template <class T>
std::map<std::string, T*> tolua_ext_luaval_to_ccmap_string_key(lua_State* L, int lo, int)
{
	std::map<std::string, T*> outValue;

	if (nullptr == L || lua_gettop(L) < lo)
	{
		return outValue;
	}

	tolua_Error tolua_err;
	if (!tolua_istable(L, lo, 0, &tolua_err))
	{
		return outValue;
	}

	lua_pushvalue(L, lo);
	lua_pushnil(L);
	// stack: 
	//	-1	=> nil
	//	-2	=> table
	while (lua_next(L, -2))
	{
		// stack: 
		//  -1	=> value; 
		//  -2	=> key; 
		//  -3	=> table
		lua_pushvalue(L, -2);
		// stack：
		//  -1 => key; 
		//  -2 => value; 
		//  -3 => key; 
		//  -4 => table
		if (lua_type(L, -1) == LUA_TSTRING && lua_isuserdata(L, -2))
		{
			const char* key = lua_tostring(L, -1);
			T* obj = static_cast<T*>(tolua_tousertype(L, -2, NULL));
			outValue.emplace(std::string(key), obj);
		}

		// 弹出 value 和拷贝的 key，留下原始的 key 作为下一次 lua_next 的参数
		lua_pop(L, 2);
		// stack：
		//  -1 => key; 
		//  -2 => table
	}
	lua_pop(L, 1);
	return outValue;
}
