#include "LuaFunction.h"
#include <assert.h>


lua_State* LuaFunction::G_L = NULL;

void LuaFunction::setGlobalLuaState(lua_State* L)
{
	G_L = L;
}

lua_State* LuaFunction::getGlobalLuaState()
{
	return G_L;
}

////////////////////////////////////////////////////////////////////////////////////////////

LuaRetValue::LuaRetValue()
	: m_type(LUA_TNONE)
{
	memset(&m_value, 0, sizeof(union Value));
}

LuaRetValue::~LuaRetValue()
{
	reset();
}

void LuaRetValue::reset()
{
	if (m_type == LUA_TSTRING && m_value.svalue != NULL)
	{
		delete m_value.svalue;
		memset(&m_value, 0, sizeof(union Value));
	}
	m_type = LUA_TNONE;
}

void LuaRetValue::setString(const char* value)
{
	reset();
	m_value.svalue = new std::string(value);
	m_type = LUA_TSTRING;
}

void LuaRetValue::setNumber(lua_Number value)
{
	reset();
	m_value.nvalue = value;
	m_type = LUA_TNUMBER;
}

void LuaRetValue::setBool(bool value)
{
	reset();
	m_value.bvalue = value;
	m_type = LUA_TBOOLEAN;
}

void LuaRetValue::setUserdata(void* value)
{
	reset();
	m_value.userdata = value;
	m_type = LUA_TUSERDATA;
}

void LuaRetValue::setNil()
{
	reset();
	m_type = LUA_TNIL;
}


std::string LuaRetValue::getString()
{
	if (m_type == LUA_TSTRING)
	{
		return *m_value.svalue;
	}
	else
	{
		assert(m_type == LUA_TNIL);
		return "";
	}
}

int LuaRetValue::getInt()
{
	if (m_type == LUA_TNUMBER)
	{
		return (int)m_value.nvalue;
	}
	else
	{
		assert(m_type == LUA_TNIL);
		return 0;
	}
}

float LuaRetValue::getFloat()
{
	if (m_type == LUA_TNUMBER)
	{
		return (float)m_value.nvalue;
	}
	else
	{
		assert(m_type == LUA_TNIL);
		return 0.0f;
	}
}

double LuaRetValue::getDouble()
{
	if (m_type == LUA_TNUMBER)
	{
		return (double)m_value.nvalue;
	}
	else
	{
		assert(m_type == LUA_TNIL);
		return 0.0;
	}
}

void* LuaRetValue::getUserdata()
{
	if (m_type == LUA_TUSERDATA)
	{
		return m_value.userdata;
	}
	else
	{
		assert(m_type == LUA_TNIL);
		return 0;
	}
}

bool LuaRetValue::isNil()
{
	if (m_type == LUA_TNIL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LuaRetValue::getBool()
{
	if (m_type == LUA_TBOOLEAN)
	{
		return m_value.bvalue;
	}
	else
	{
		assert(m_type == LUA_TNIL);
		return false;
	}
}







////////////////////////////////////////////////////////////////////////////////////////////

LuaFunction::LuaFunction()
	: m_trackback(0)
	, m_ref(0)
{}

LuaFunction::LuaFunction(lua_State* aL, int index, int def)
	: m_trackback(0)
{
	assert(index > 0);
	m_ref = tolua_ext_ref_function(aL, index, def);
}

LuaFunction::LuaFunction(int ref)
	: m_trackback(0)
	, m_ref(ref)
{
}

LuaFunction::LuaFunction(const LuaFunction& other)
	: m_trackback(0)
	, m_ref(0)
{
	*this = other;
}

LuaFunction& LuaFunction::operator=(const LuaFunction& rhs)
{
	if (this != &rhs)
	{
		if (rhs.m_ref > 0)
		{
			auto top = lua_gettop(G_L);
			rhs.push();
			this->ref(tolua_ext_ref_function(G_L, lua_gettop(G_L), 0));
			lua_settop(G_L, top);
		}
		else
		{
			this->unref();
		}
	}
	return *this;
}

LuaFunction::LuaFunction(LuaFunction&& other)
	: m_trackback(0)
	, m_ref(0)
{
	*this = std::move(other);
}

LuaFunction& LuaFunction::operator=(LuaFunction&& rhs)
{
	if (this != &rhs)
	{
		this->ref(rhs.m_ref);
		rhs.m_ref = 0;
	}
	return *this;
}

LuaFunction::~LuaFunction()
{
	unref();
}

void LuaFunction::operator()()
{
	ppush();
	pcall();
}

void LuaFunction::ref(int handle)
{
	unref();
	m_ref = handle;
}

void LuaFunction::unref()
{
	if (m_ref > 0)
	{
		tolua_ext_remove_function_by_refid(G_L, m_ref);
		m_ref = 0;
	}
}

void LuaFunction::push() const
{
	tolua_ext_get_function_by_refid(G_L, m_ref);
}

void LuaFunction::ppush()
{
	assert(m_ref > 0);

	lua_getglobal(G_L, "__G__TRACKBACK__");
	m_trackback = lua_gettop(G_L);
	
	this->push();
	luaL_checktype(G_L, -1, LUA_TFUNCTION);
}

bool LuaFunction::pcall(LuaRetValue* retarr/* = NULL*/, int nresults/* = 0*/)
{
	int argc = lua_gettop(G_L) - m_trackback - 1;
	int error = lua_pcall(G_L, argc, nresults, m_trackback);

	if (error)
	{
		lua_settop(G_L, m_trackback - 1);
		return false;
	}

	if (retarr != 0 && nresults > 0)
	{
		int index = 0;
		for (int i = -nresults; i < 0; ++i)
		{
			int type = lua_type(G_L, i);
			switch (type)
			{
			case LUA_TNIL: 
			{
				retarr[index].setNil();
			}break;
			case LUA_TBOOLEAN: 
			{
				retarr[index].setBool((bool)lua_toboolean(G_L, i));
			}break;
			case LUA_TLIGHTUSERDATA:
			{
				retarr[index].setUserdata(*((void**)lua_touserdata(G_L, i)));
			}break;
			case LUA_TNUMBER: 
			{
				retarr[index].setNumber(lua_tonumber(G_L, i));
			}break;
			case LUA_TSTRING: 
			{
				retarr[index].setString(lua_tostring(G_L, i));
			}break;
			case LUA_TUSERDATA:
			{
				retarr[index].setUserdata(*((void**)lua_touserdata(G_L, i)));
			}break;
			default:
				assert(0);
				break;
			}
			index++;
		}
	}

	// remove trackback and any thing above it.
	lua_settop(G_L, m_trackback - 1);
	
	return true;
}

void LuaFunction::pusharg(bool v)
{
	lua_pushboolean(G_L, v);
}

void LuaFunction::pusharg(float v)
{
	lua_pushnumber(G_L, v);
}

void LuaFunction::pusharg(double v)
{
	lua_pushnumber(G_L, v);
}

void LuaFunction::pusharg(int v)
{
	lua_pushinteger(G_L, v);
}

void LuaFunction::pusharg(unsigned int v)
{
	lua_pushinteger(G_L, v);
}

void LuaFunction::pusharg(const std::string& v)
{
	lua_pushlstring(G_L, v.data(), v.size());
}

void LuaFunction::pusharg(const char* v)
{
	lua_pushstring(G_L, v);
}

void LuaFunction::pushlstring(const char* v, unsigned int len)
{
	lua_pushlstring(G_L, v, len);
}
