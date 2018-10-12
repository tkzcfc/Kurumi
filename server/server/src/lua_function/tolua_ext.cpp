#include "tolua_ext.h"


static void stackDump(lua_State* L) {
	printf("\n\nbegin dump lua stack------------------->\n");
	int i = 0;
	int top = lua_gettop(L);

	for (i = 1; i <= top; ++i) {
		int t = lua_type(L, i);
		switch (t) {
		case LUA_TSTRING:
		{
			printf("'%s' \n", lua_tostring(L, i));
		}
		break;
		case LUA_TBOOLEAN:
		{
			printf(lua_toboolean(L, i) ? "true " : "false ");
		}break;
		case LUA_TNUMBER:
		{
			printf("%g \n", lua_tonumber(L, i));
		}
		break;
		default:
		{
			printf("%s \n", lua_typename(L, t));
		}
		break;

		}
	}
	printf("end dump lua stack------------------->\n\n");
}

//////////////////////////////////////////////////////////////////////////

bool tolua_ext_check_is_table(lua_State* L, int lo, const char* type, int def, tolua_Error* err)
{
	if (def && lua_gettop(L) < abs(lo))
		return 1;
	if (lua_istable(L, lo))
		return 1;
	if (err == NULL)
		return 0;
	err->index = lo;
	err->array = 0;
	err->type = type;
	return 0;
}


//////////////////////////////////////////////////////////////////////////
///map
void tolua_ext_map_string_string_to_luaval(lua_State* L, const std::map<std::string, std::string>& v)
{
	if (nullptr == L)
		return;

	lua_newtable(L);

	for (auto iter = v.begin(); iter != v.end(); ++iter)
	{
		lua_pushstring(L, iter->first.c_str());
		lua_pushstring(L, iter->second.c_str());
		lua_rawset(L, -3);
	}
}

void tolua_ext_map_string_int_to_luaval(lua_State* L, const std::map<std::string, int>& v)
{
	if (nullptr == L)
		return;

	lua_newtable(L);

	for (auto iter = v.begin(); iter != v.end(); ++iter)
	{
		lua_pushstring(L, iter->first.c_str());
		lua_pushnumber(L, (lua_Number)iter->second);
		lua_rawset(L, -3);
	}
}

void tolua_ext_map_string_float_to_luaval(lua_State* L, const std::map<std::string, float>& v)
{
	if (nullptr == L)
		return;

	lua_newtable(L);

	for (auto iter = v.begin(); iter != v.end(); ++iter)
	{
		lua_pushstring(L, iter->first.c_str());
		lua_pushnumber(L, (lua_Number)iter->second);
		lua_rawset(L, -3);
	}
}

void tolua_ext_map_string_double_to_luaval(lua_State* L, const std::map<std::string, double>& v)
{
	if (nullptr == L)
		return;

	lua_newtable(L);

	for (auto iter = v.begin(); iter != v.end(); ++iter)
	{
		lua_pushstring(L, iter->first.c_str());
		lua_pushnumber(L, (lua_Number)iter->second);
		lua_rawset(L, -3);
	}
}

const std::map<std::string, std::string>& tolua_ext_luaval_to_map_string_string(lua_State* L, int lo, int)
{
	static std::map<std::string, std::string> outValue;
	outValue.clear();

	if (NULL == L || tolua_ext_check_is_table(L, lo, NULL, 0, NULL) == 0)
		return outValue;

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
		if (lua_type(L, -1) == LUA_TSTRING && lua_type(L, -2) == LUA_TSTRING)
		{
			const char* key = lua_tostring(L, -1);
			const char* value = lua_tostring(L, -2);
			outValue.emplace(std::string(key), std::string(value));
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

const std::map<std::string, int>& tolua_ext_luaval_to_map_string_int(lua_State* L, int lo, int)
{
	static std::map<std::string, int> outValue;
	outValue.clear();

	if (NULL == L || tolua_ext_check_is_table(L, lo, NULL, 0, NULL) == 0)
		return outValue;

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
		printf("%s = %s\n", lua_tostring(L, -1), lua_typename(L, lua_type(L, -2)));
		if (lua_type(L, -1) == LUA_TSTRING && lua_type(L, -2) == LUA_TNUMBER)
		{
			const char* key = lua_tostring(L, -1);
			int value = lua_tointeger(L, -2);
			outValue.emplace(std::string(key), value);
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

const std::map<std::string, float>& tolua_ext_luaval_to_map_string_float(lua_State* L, int lo, int)
{
	static std::map<std::string, float> outValue;
	outValue.clear();

	if (NULL == L || tolua_ext_check_is_table(L, lo, NULL, 0, NULL) == 0)
		return outValue;

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
		if (lua_type(L, -1) == LUA_TSTRING && lua_type(L, -2) == LUA_TNUMBER)
		{
			const char* key = lua_tostring(L, -1);
			float value = lua_tonumber(L, -2);
			outValue.emplace(std::string(key), value);
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

const std::map<std::string, double>& tolua_ext_luaval_to_map_string_double(lua_State* L, int lo, int)
{
	static std::map<std::string, double> outValue;
	outValue.clear();

	if (NULL == L || tolua_ext_check_is_table(L, lo, NULL, 0, NULL) == 0)
		return outValue;

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
		if (lua_type(L, -1) == LUA_TSTRING && lua_type(L, -2) == LUA_TNUMBER)
		{
			const char* key = lua_tostring(L, -1);
			float value = lua_tonumber(L, -2);
			outValue.emplace(std::string(key), value);
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










//////////////////////////////////////////////////////////////////////////
///vector
void tolua_ext_vector_string_to_luaval(lua_State* L, const std::vector<std::string>& v)
{
	if (nullptr == L)
		return;

	lua_newtable(L);

	int index = 1;

	for (const std::string& value : v)
	{
		lua_pushnumber(L, (lua_Number)index);
		lua_pushstring(L, value.c_str());
		lua_rawset(L, -3);
		++index;
	}
}

void tolua_ext_vector_int_to_luaval(lua_State* L, const std::vector<int>& v)
{
	if (nullptr == L)
		return;

	lua_newtable(L);

	int index = 1;

	for (const int& value : v)
	{
		lua_pushnumber(L, (lua_Number)index);
		lua_pushnumber(L, (lua_Number)value);
		lua_rawset(L, -3);
		++index;
	}
}

void tolua_ext_vector_float_to_luaval(lua_State* L, const std::vector<float>& v)
{
	if (nullptr == L)
		return;

	lua_newtable(L);

	int index = 1;

	for (const float& value : v)
	{
		lua_pushnumber(L, (lua_Number)index);
		lua_pushnumber(L, (lua_Number)value);
		lua_rawset(L, -3);
		++index;
	}
}

void tolua_ext_vector_double_to_luaval(lua_State* L, const std::vector<double>& v)
{
	if (nullptr == L)
		return;

	lua_newtable(L);

	int index = 1;

	for (const double& value : v)
	{
		lua_pushnumber(L, (lua_Number)index);
		lua_pushnumber(L, (lua_Number)value);
		lua_rawset(L, -3);
		++index;
	}
}

const std::vector<std::string>& tolua_ext_luaval_to_vector_string(lua_State* L, int lo, int)
{
	static std::vector<std::string> outValue;
	outValue.clear();

	if (NULL == L || tolua_ext_check_is_table(L, lo, NULL, 0, NULL) == 0)
		return outValue;

	lua_pushvalue(L, lo);
	int len = lua_objlen(L, -1);
	outValue.reserve(len);
	for (int i = 1; i <= len; i++) 
	{
		lua_pushinteger(L, i);
		lua_gettable(L, -2);
		/* 此时栈顶即为 t[i] 元素 */
		if (lua_type(L, -1) == LUA_TSTRING)
		{
			std::string value = lua_tostring(L, -1);
			outValue.emplace_back(value);
		}
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
	return outValue;
}

const std::vector<int>& tolua_ext_luaval_to_vector_int(lua_State* L, int lo, int)
{
	static std::vector<int> outValue;
	outValue.clear();

	if (NULL == L || tolua_ext_check_is_table(L, lo, NULL, 0, NULL) == 0)
		return outValue;

	lua_pushvalue(L, lo);
	int len = lua_objlen(L, -1);
	outValue.reserve(len);
	stackDump(L);
	for (int i = 1; i <= len; i++)
	{
		lua_pushinteger(L, i);
		lua_gettable(L, -2);
		/* 此时栈顶即为 t[i] 元素 */
		if (lua_type(L, -1) == LUA_TNUMBER)
		{
			int value = lua_tointeger(L, -1);
			outValue.emplace_back(value);
		}
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
	return outValue;
}

const std::vector<float>& tolua_ext_luaval_to_vector_float(lua_State* L, int lo, int)
{
	static std::vector<float> outValue;
	outValue.clear();

	if (NULL == L || tolua_ext_check_is_table(L, lo, NULL, 0, NULL) == 0)
		return outValue;

	lua_pushvalue(L, lo);
	int len = lua_objlen(L, -1);
	outValue.reserve(len);
	for (int i = 1; i <= len; i++)
	{
		lua_pushinteger(L, i);
		lua_gettable(L, -2);
		/* 此时栈顶即为 t[i] 元素 */
		if (lua_type(L, -1) == LUA_TNUMBER)
		{
			float value = lua_tonumber(L, -1);
			outValue.emplace_back(value);
		}
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
	return outValue;
}

const std::vector<double>& tolua_ext_luaval_to_vector_double(lua_State* L, int lo, int)
{
	static std::vector<double> outValue;
	outValue.clear();

	if (NULL == L || tolua_ext_check_is_table(L, lo, NULL, 0, NULL) == 0)
		return outValue;

	lua_pushvalue(L, lo);
	int len = lua_objlen(L, -1);
	outValue.reserve(len);
	for (int i = 1; i <= len; i++)
	{
		lua_pushinteger(L, i);
		lua_gettable(L, -2);
		/* 此时栈顶即为 t[i] 元素 */
		if (lua_type(L, -1) == LUA_TNUMBER)
		{
			double value = lua_tonumber(L, -1);
			outValue.emplace_back(value);
		}
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
	return outValue;
}

void tolua_ext_vec2_value_to_luaval(lua_State* L, const Vec2& v)
{
	if (NULL == L)
		return;
	lua_newtable(L);									/* L: table */
	lua_pushstring(L, "x");								/* L: table key */
	lua_pushnumber(L, (lua_Number)v.x);					/* L: table key value*/
	lua_rawset(L, -3);									/* table[key] = value, L: table */
	lua_pushstring(L, "y");								/* L: table key */
	lua_pushnumber(L, (lua_Number)v.y);					/* L: table key value*/
	lua_rawset(L, -3);									/* table[key] = value, L: table */
}

void tolua_ext_vec3_value_to_luaval(lua_State* L, const Vec3& v)
{
	if (NULL == L)
		return;
	lua_newtable(L);									 /* L: table */
	lua_pushstring(L, "x");								 /* L: table key */
	lua_pushnumber(L, (lua_Number)v.x);					 /* L: table key value*/
	lua_rawset(L, -3);									 /* table[key] = value, L: table */
	lua_pushstring(L, "y");								 /* L: table key */
	lua_pushnumber(L, (lua_Number)v.y);					 /* L: table key value*/
	lua_rawset(L, -3);									 /* table[key] = value, L: table */
	lua_pushstring(L, "z");								 /* L: table key */
	lua_pushnumber(L, (lua_Number)v.z);					 /* L: table key value*/
	lua_rawset(L, -3);									 /* table[key] = value, L: table */
}

void tolua_ext_size_value_to_luaval(lua_State* L, const Size& v)
{
	if (NULL == L)
		return;
	lua_newtable(L);									/* L: table */
	lua_pushstring(L, "width");							/* L: table key */
	lua_pushnumber(L, (lua_Number)v.width);        		/* L: table key value*/
	lua_rawset(L, -3);									/* table[key] = value, L: table */
	lua_pushstring(L, "height");						/* L: table key */
	lua_pushnumber(L, (lua_Number)v.height);       		/* L: table key value*/
	lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

void tolua_ext_rect_value_to_luaval(lua_State* L, const Rect& v)
{
	if (NULL == L)
		return;
	lua_newtable(L);                                    /* L: table */
	lua_pushstring(L, "x");                             /* L: table key */
	lua_pushnumber(L, (lua_Number)v.origin.x);          /* L: table key value*/
	lua_rawset(L, -3);                                  /* table[key] = value, L: table */
	lua_pushstring(L, "y");                             /* L: table key */
	lua_pushnumber(L, (lua_Number)v.origin.y);          /* L: table key value*/
	lua_rawset(L, -3);                                  /* table[key] = value, L: table */
	lua_pushstring(L, "width");							/* L: table key */
	lua_pushnumber(L, (lua_Number)v.size.width);        /* L: table key value*/
	lua_rawset(L, -3);                                  /* table[key] = value, L: table */
	lua_pushstring(L, "height");						/* L: table key */
	lua_pushnumber(L, (lua_Number)v.size.height);       /* L: table key value*/
	lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

//void tolua_ext_b2vec2_to_luaval(lua_State* L, const b2Vec2& v)
//{
//	if (NULL == L)
//		return;
//	lua_newtable(L);                                    /* L: table */
//	lua_pushstring(L, "x");                             /* L: table key */
//	lua_pushnumber(L, (lua_Number)v.x);					/* L: table key value*/
//	lua_rawset(L, -3);                                  /* table[key] = value, L: table */
//	lua_pushstring(L, "y");                             /* L: table key */
//	lua_pushnumber(L, (lua_Number)v.y);					/* L: table key value*/
//	lua_rawset(L, -3);                                  /* table[key] = value, L: table */
//}

Vec2 tolua_ext_luaval_to_vec2_value(lua_State* L, int lo, int)
{
	Vec2 outValue;

	if (NULL == L || tolua_ext_check_is_table(L, lo, NULL, 0, NULL) == 0)
		return outValue;

	lua_pushstring(L, "x");
	lua_gettable(L, lo);
	outValue.x = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "y");
	lua_gettable(L, lo);
	outValue.y = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
	lua_pop(L, 1);

	return outValue;
}

Vec3 tolua_ext_luaval_to_vec3_value(lua_State* L, int lo, int)
{
	Vec3 outValue;

	if (NULL == L || tolua_ext_check_is_table(L, lo, NULL, 0, NULL) == 0)
		return outValue;

	lua_pushstring(L, "x");
	lua_gettable(L, lo);
	outValue.x = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "y");
	lua_gettable(L, lo);
	outValue.y = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "z");
	lua_gettable(L, lo);
	outValue.z = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
	lua_pop(L, 1);

	return outValue;
}


Size tolua_ext_luaval_to_size_value(lua_State* L, int lo, int)
{
	Size outValue;

	if (NULL == L || tolua_ext_check_is_table(L, lo, NULL, 0, NULL) == 0)
		return outValue;

	lua_pushstring(L, "width");
	lua_gettable(L, lo);
	outValue.width = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "height");
	lua_gettable(L, lo);
	outValue.height = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
	lua_pop(L, 1);

	return outValue;
}

Rect tolua_ext_luaval_to_rect_value(lua_State* L, int lo, int)
{
	Rect outValue;

	if (NULL == L || tolua_ext_check_is_table(L, lo, NULL, 0, NULL) == 0)
		return outValue;

	lua_pushstring(L, "x");
	lua_gettable(L, lo);
	outValue.origin.x = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "y");
	lua_gettable(L, lo);
	outValue.origin.y = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "width");
	lua_gettable(L, lo);
	outValue.size.width = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "height");
	lua_gettable(L, lo);
	outValue.size.height = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
	lua_pop(L, 1);

	return outValue;
}

//b2Vec2 tolua_ext_luaval_to_b2vec2(lua_State* L, int lo, int)
//{
//	b2Vec2 outValue;
//
//	if (NULL == L || tolua_ext_check_is_table(L, lo, NULL, 0, NULL) == 0)
//		return outValue;
//
//	lua_pushstring(L, "x");
//	lua_gettable(L, lo);
//	outValue.x = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
//	lua_pop(L, 1);
//
//	lua_pushstring(L, "y");
//	lua_gettable(L, lo);
//	outValue.y = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
//	lua_pop(L, 1);
//
//	return outValue;
//}


