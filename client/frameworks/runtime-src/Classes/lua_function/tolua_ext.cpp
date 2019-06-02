#include "tolua_ext.h"
#include "LuaFunction.h"


#define TOLUA_EXT_REFID_PTR_MAPPING "toluafix_refid_ptr_mapping"
#define TOLUA_EXT_REFID_TYPE_MAPPING "toluafix_refid_type_mapping"

static std::unordered_map<void*, std::string> g_refidTypeMap;

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


int tolua_ext_pushusertype_ccobject(lua_State* L,
	int refid,
	int* p_refid,
	void* ptr,
	const char* type)
{
	if (ptr == NULL || p_refid == NULL)
	{
		lua_pushnil(L);
		return -1;
	}

	if (*p_refid == 0)
	{
		*p_refid = refid;

		lua_pushstring(L, TOLUA_EXT_REFID_PTR_MAPPING);
		lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: refid_ptr */
		lua_pushinteger(L, refid);                                  /* stack: refid_ptr refid */
		lua_pushlightuserdata(L, ptr);                              /* stack: refid_ptr refid ptr */

		lua_rawset(L, -3);                  /* refid_ptr[refid] = ptr, stack: refid_ptr */
		lua_pop(L, 1);                                              /* stack: - */

		lua_pushstring(L, TOLUA_EXT_REFID_TYPE_MAPPING);
		lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: refid_type */
		lua_pushinteger(L, refid);                                  /* stack: refid_type refid */
		lua_pushstring(L, type);                                    /* stack: refid_type refid type */
		lua_rawset(L, -3);                /* refid_type[refid] = type, stack: refid_type */
		lua_pop(L, 1);                                              /* stack: - */

		//printf("[LUA] push CCObject OK - refid: %d, ptr: %x, type: %s\n", *p_refid, (int)ptr, type);
	}

	tolua_pushusertype_and_addtoroot(L, ptr, type);
	return 0;
}

int tolua_ext_remove_ccobject_by_refid(lua_State* L, int refid)
{
	void* ptr = NULL;
	const char* type = NULL;
	void** ud = NULL;
	if (refid == 0) return -1;

	// get ptr from tolua_refid_ptr_mapping
	lua_pushstring(L, TOLUA_EXT_REFID_PTR_MAPPING);
	lua_rawget(L, LUA_REGISTRYINDEX);                               /* stack: refid_ptr */
	lua_pushinteger(L, refid);                                      /* stack: refid_ptr refid */
	lua_rawget(L, -2);                                              /* stack: refid_ptr ptr */
	ptr = lua_touserdata(L, -1);
	lua_pop(L, 1);                                                  /* stack: refid_ptr */
	if (ptr == NULL)
	{
		lua_pop(L, 1);
		// Lua stack has closed, C++ object not in Lua.
		// printf("[LUA ERROR] remove CCObject with NULL ptr, refid: %d\n", refid);
		return -2;
	}

	// remove ptr from tolua_refid_ptr_mapping
	lua_pushinteger(L, refid);                                      /* stack: refid_ptr refid */
	lua_pushnil(L);                                                 /* stack: refid_ptr refid nil */
	lua_rawset(L, -3);                     /* delete refid_ptr[refid], stack: refid_ptr */
	lua_pop(L, 1);                                                  /* stack: - */


	// get type from tolua_refid_type_mapping
	lua_pushstring(L, TOLUA_EXT_REFID_TYPE_MAPPING);
	lua_rawget(L, LUA_REGISTRYINDEX);                               /* stack: refid_type */
	lua_pushinteger(L, refid);                                      /* stack: refid_type refid */
	lua_rawget(L, -2);                                              /* stack: refid_type type */
	if (lua_isnil(L, -1))
	{
		lua_pop(L, 2);
		printf("[LUA ERROR] remove CCObject with NULL type, refid: %d, ptr: %p\n", refid, ptr);
		return -1;
	}

	type = lua_tostring(L, -1);
	lua_pop(L, 1);                                                  /* stack: refid_type */

	// remove type from tolua_refid_type_mapping
	lua_pushinteger(L, refid);                                      /* stack: refid_type refid */
	lua_pushnil(L);                                                 /* stack: refid_type refid nil */
	lua_rawset(L, -3);                    /* delete refid_type[refid], stack: refid_type */
	lua_pop(L, 1);                                                  /* stack: - */

	// get ubox
	luaL_getmetatable(L, type);                                     /* stack: mt */
	lua_pushstring(L, "tolua_ubox");                                /* stack: mt key */
	lua_rawget(L, -2);                                              /* stack: mt ubox */
	if (lua_isnil(L, -1))
	{
		// use global ubox
		lua_pop(L, 1);                                              /* stack: mt */
		lua_pushstring(L, "tolua_ubox");                            /* stack: mt key */
		lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: mt ubox */
	};


	// cleanup root
	tolua_remove_value_from_root(L, ptr);

	lua_pushlightuserdata(L, ptr);                                  /* stack: mt ubox ptr */
	lua_rawget(L, -2);                                               /* stack: mt ubox ud */
	if (lua_isnil(L, -1))
	{
		// Lua object has released (GC), C++ object not in ubox.
		//printf("[LUA ERROR] remove CCObject with NULL ubox, refid: %d, ptr: %x, type: %s\n", refid, (int)ptr, type);
		lua_pop(L, 3);
		return -3;
	}

	// cleanup peertable
	lua_pushvalue(L, LUA_REGISTRYINDEX);
	lua_setfenv(L, -2);

	ud = (void**)lua_touserdata(L, -1);
	lua_pop(L, 1);                                                  /* stack: mt ubox */
	if (ud == NULL)
	{
		printf("[LUA ERROR] remove CCObject with NULL userdata, refid: %d, ptr: %p, type: %s\n", refid, ptr, type);
		lua_pop(L, 2);
		return -1;
	}

	// clean userdata
	*ud = NULL;

	lua_pushlightuserdata(L, ptr);                                  /* stack: mt ubox ptr */
	lua_pushnil(L);                                                 /* stack: mt ubox ptr nil */
	lua_rawset(L, -3);                             /* ubox[ptr] = nil, stack: mt ubox */

	lua_pop(L, 2);
	//printf("[LUA] remove CCObject, refid: %d, ptr: %x, type: %s\n", refid, (int)ptr, type);
	return 0;
}

int tolua_ext_pushusertype_cclass(lua_State* L, void* value, const char* type)
{
	g_refidTypeMap[value] = type;
	tolua_pushusertype_and_addtoroot(L, value, type);
	return 0;
}

int tolua_ext_remove_cclass_by_refid(lua_State* L, void* ptr)
{
	auto it = g_refidTypeMap.find(ptr);
	if (it == g_refidTypeMap.end())
	{
		CC_ASSERT(0);
		return 0;
	}

	// get ubox
	luaL_getmetatable(L, it->second.c_str());                                     /* stack: mt */
	lua_pushstring(L, "tolua_ubox");                                /* stack: mt key */
	lua_rawget(L, -2);                                              /* stack: mt ubox */

	g_refidTypeMap.erase(it);

	if (lua_isnil(L, -1))
	{
		// use global ubox
		lua_pop(L, 1);                                              /* stack: mt */
		lua_pushstring(L, "tolua_ubox");                            /* stack: mt key */
		lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: mt ubox */
	};


	// cleanup root
	tolua_remove_value_from_root(L, ptr);

	lua_pushlightuserdata(L, ptr);                                  /* stack: mt ubox ptr */
	lua_rawget(L, -2);                                               /* stack: mt ubox ud */
	if (lua_isnil(L, -1))
	{
		// Lua object has released (GC), C++ object not in ubox.
		//printf("[LUA ERROR] remove CCObject with NULL ubox, refid: %d, ptr: %x, type: %s\n", refid, (int)ptr, type);
		lua_pop(L, 3);
		return -3;
	}

	// cleanup peertable
	lua_pushvalue(L, LUA_REGISTRYINDEX);
	lua_setfenv(L, -2);

	void** ud = (void**)lua_touserdata(L, -1);
	lua_pop(L, 1);                                                  /* stack: mt ubox */
	if (ud == NULL)
	{
		//printf("[LUA ERROR] remove CCObject with NULL userdata, refid: %d, ptr: %p, type: %s\n", refid, ptr, type);
		lua_pop(L, 2);
		return -1;
	}

	// clean userdata
	*ud = NULL;

	lua_pushlightuserdata(L, ptr);                                  /* stack: mt ubox ptr */
	lua_pushnil(L);                                                 /* stack: mt ubox ptr nil */
	lua_rawset(L, -3);                             /* ubox[ptr] = nil, stack: mt ubox */

	lua_pop(L, 2);
	//printf("[LUA] remove CCObject, refid: %d, ptr: %x, type: %s\n", refid, (int)ptr, type);
	return 0;
}

//////////////////////////////////////////////////////////////////////////

int tolua_ext_check_is_table(lua_State* L, int lo, const char* type, int def, tolua_Error* err)
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

int tolua_ext_check_isfunction(lua_State* L, int lo, const char* type, int def, tolua_Error* err)
{
	if (lua_gettop(L) >= abs(lo) && lua_isfunction(L, lo))
	{
		return 1;
	}
	err->index = lo;
	err->array = 0;
	err->type = "[not function]";
	return 0;
}

//////////////////////////////////////////////////////////////////////////
/// function
void tolua_ext_function_to_luaval(lua_State* L, LuaFunction& func, const char* type)
{
	if (func.isvalid() == false)
		return;
	func.ppush();
}

void tolua_ext_function_to_luaval(lua_State* L, void* funcPtr, const char* type)
{
	LuaFunction* handle = (LuaFunction*)funcPtr;
	if (handle == NULL || handle->isvalid() == false)
	{
		lua_pushnil(L);
		return;
	}
	handle->push();
}

void* tolua_ext_luaval_to_function(lua_State* L, int narg, void* def)
{
	static LuaFunction* pHandle = NULL;

	if (pHandle == NULL)
	{
		pHandle = new LuaFunction(L, narg, 0);
	}
	else
	{
		*pHandle = std::move(LuaFunction(L, narg, 0));
	}
	return pHandle;
}

//////////////////////////////////////////////////////////////////////////
///map
void tolua_ext_map_string_string_to_luaval(lua_State* L, const std::map<std::string, std::string>& v, const char*)
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

void tolua_ext_map_string_int_to_luaval(lua_State* L, const std::map<std::string, int>& v, const char*)
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

void tolua_ext_map_string_float_to_luaval(lua_State* L, const std::map<std::string, float>& v, const char*)
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

void tolua_ext_map_string_double_to_luaval(lua_State* L, const std::map<std::string, double>& v, const char*)
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

std::map<std::string, std::string>& tolua_ext_luaval_to_map_string_string(lua_State* L, int lo, int)
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

std::map<std::string, int>& tolua_ext_luaval_to_map_string_int(lua_State* L, int lo, int)
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
		//printf("%s = %s\n", lua_tostring(L, -1), lua_typename(L, lua_type(L, -2)));
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

std::map<std::string, float>& tolua_ext_luaval_to_map_string_float(lua_State* L, int lo, int)
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

std::map<std::string, double>& tolua_ext_luaval_to_map_string_double(lua_State* L, int lo, int)
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
void tolua_ext_vector_string_to_luaval(lua_State* L, const std::vector<std::string>& v, const char*)
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

void tolua_ext_vector_int_to_luaval(lua_State* L, const std::vector<int>& v, const char*)
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

void tolua_ext_vector_float_to_luaval(lua_State* L, const std::vector<float>& v, const char*)
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

void tolua_ext_vector_double_to_luaval(lua_State* L, const std::vector<double>& v, const char*)
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


void tolua_ext_vector_vec2_to_luaval(lua_State* L, const std::vector<Vec2>& v, const char*)
{
	if (NULL == L)
		return;
	lua_newtable(L);
	for (int i = 1; i <= v.size(); ++i)
	{
		lua_pushnumber(L, i);
		tolua_ext_vec2_value_to_luaval(L, v[i - 1], "");
		lua_rawset(L, -3);
	}
}

std::vector<std::string>& tolua_ext_luaval_to_vector_string(lua_State* L, int lo, int)
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

std::vector<int>& tolua_ext_luaval_to_vector_int(lua_State* L, int lo, int)
{
	static std::vector<int> outValue;
	outValue.clear();

	if (NULL == L || tolua_ext_check_is_table(L, lo, NULL, 0, NULL) == 0)
		return outValue;

	lua_pushvalue(L, lo);
	int len = lua_objlen(L, -1);
	outValue.reserve(len);
	//stackDump(L);
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

std::vector<float>& tolua_ext_luaval_to_vector_float(lua_State* L, int lo, int)
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

std::vector<double>& tolua_ext_luaval_to_vector_double(lua_State* L, int lo, int)
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

std::vector<Vec2>& tolua_ext_luaval_to_vector_vec2(lua_State* L, int lo, int)
{
	static std::vector<Vec2> outValue;
	outValue.clear();

	if (nullptr == L || lua_gettop(L) < lo)
		return outValue;

	if (tolua_ext_check_is_table(L, lo, NULL, 0, NULL) == 0)
	{
		return outValue;
	}

	size_t len = lua_objlen(L, lo);
	Vec2 value;
	for (size_t i = 1; i <= len; i++)
	{
		lua_pushnumber(L, i);
		lua_gettable(L, lo);
		if (lua_istable(L, lua_gettop(L)))
		{
			value = tolua_ext_luaval_to_vec2_value(L, lua_gettop(L), 0);
			outValue.push_back(value);
		}
		lua_pop(L, 1);
	}

	return outValue;
}

void tolua_ext_vec2_value_to_luaval(lua_State* L, const Vec2& v, const char*)
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

void tolua_ext_vec3_value_to_luaval(lua_State* L, const Vec3& v, const char*)
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

void tolua_ext_size_value_to_luaval(lua_State* L, const Size& v, const char*)
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

void tolua_ext_rect_value_to_luaval(lua_State* L, const Rect& v, const char*)
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

void tolua_ext_b2vec2_to_luaval(lua_State* L, const b2Vec2& v, const char*)
{
	if (NULL == L)
		return;
	lua_newtable(L);                                    /* L: table */
	lua_pushstring(L, "x");                             /* L: table key */
	lua_pushnumber(L, (lua_Number)v.x);					/* L: table key value*/
	lua_rawset(L, -3);                                  /* table[key] = value, L: table */
	lua_pushstring(L, "y");                             /* L: table key */
	lua_pushnumber(L, (lua_Number)v.y);					/* L: table key value*/
	lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

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
//
b2Vec2 tolua_ext_luaval_to_b2vec2(lua_State* L, int lo, int)
{
	b2Vec2 outValue;

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
