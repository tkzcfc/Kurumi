#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#include "tolua++.h"

#include <map>
#include <string.h>
#include <vector>


using namespace cocos2d;

#define DEF_VEC_2_VALUE
#define DEF_VEC_3_VALUE
#define DEF_SIZE_VALUE
#define DEF_RECT_VALUE


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




// 
bool tolua_ext_check_is_table(lua_State* L, int lo, const char* type, int def, tolua_Error* err);

// map
void tolua_ext_map_string_string_to_luaval(lua_State* L, const std::map<std::string, std::string>& v);
void tolua_ext_map_string_int_to_luaval(lua_State* L, const std::map<std::string, int>& v);
void tolua_ext_map_string_float_to_luaval(lua_State* L, const std::map<std::string, float>& v);
void tolua_ext_map_string_double_to_luaval(lua_State* L, const std::map<std::string, double>& v);

const std::map<std::string, std::string>&	tolua_ext_luaval_to_map_string_string(lua_State* L, int lo, int);
const std::map<std::string, int>&			tolua_ext_luaval_to_map_string_int(lua_State* L, int lo, int);
const std::map<std::string, float>&			tolua_ext_luaval_to_map_string_float(lua_State* L, int lo, int);
const std::map<std::string, double>&		tolua_ext_luaval_to_map_string_double(lua_State* L, int lo, int);

//vector
void tolua_ext_vector_string_to_luaval(lua_State* L, const std::vector<std::string>& v);
void tolua_ext_vector_int_to_luaval(lua_State* L, const std::vector<int>& v);
void tolua_ext_vector_float_to_luaval(lua_State* L, const std::vector<float>& v);
void tolua_ext_vector_double_to_luaval(lua_State* L, const std::vector<double>& v);

const std::vector<std::string>&		tolua_ext_luaval_to_vector_string(lua_State* L, int lo, int);
const std::vector<int>&				tolua_ext_luaval_to_vector_int(lua_State* L, int lo, int);
const std::vector<float>&			tolua_ext_luaval_to_vector_float(lua_State* L, int lo, int);
const std::vector<double>&			tolua_ext_luaval_to_vector_double(lua_State* L, int lo, int);

// vec2¡¢vec3¡¢size¡¢rect
void tolua_ext_vec2_value_to_luaval(lua_State* L, const Vec2& v);
void tolua_ext_vec3_value_to_luaval(lua_State* L, const Vec3& v);
void tolua_ext_size_value_to_luaval(lua_State* L, const Size& v);
void tolua_ext_rect_value_to_luaval(lua_State* L, const Rect& v);

void tolua_ext_b2vec2_to_luaval(lua_State* L, const b2Vec2& v);

Vec2			tolua_ext_luaval_to_vec2_value(lua_State* L, int lo, int);
Vec3			tolua_ext_luaval_to_vec3_value(lua_State* L, int lo, int);
Size			tolua_ext_luaval_to_size_value(lua_State* L, int lo, int);
Rect			tolua_ext_luaval_to_rect_value(lua_State* L, int lo, int);

b2Vec2			tolua_ext_luaval_to_b2vec2(lua_State* L, int lo, int);


typedef std::map<std::string, std::string>	MAP_STRING_STRING;
typedef std::map<std::string, int>			MAP_STRING_INT;
typedef std::map<std::string, float>		MAP_STRING_FLOAT;
typedef std::map<std::string, double>		MAP_STRING_DOUBLE;
typedef std::vector<std::string>			VECTOR_STRING;
typedef std::vector<int>					VECTOR_INT;
typedef std::vector<float>					VECTOR_FLOAT;
typedef std::vector<double>					VECTOR_DOUBLE;
typedef Vec2								VEC2_VALUE;
typedef Vec3								VEC3_VALUE;
typedef Size								SIZE_VALUE;
typedef Rect								RECT_VALUE;




