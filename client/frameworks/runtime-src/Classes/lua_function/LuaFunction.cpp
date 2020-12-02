#include "LuaFunction.h"
#include <assert.h>

LuaFunction::LuaFunction()
	: m_luaHandle(0)
	, m_argCount(0)
	, m_stack(NULL)
{
}

LuaFunction::LuaFunction(int handle)
	: m_luaHandle(handle)
	, m_argCount(0)
	, m_stack(NULL)
{
}

LuaFunction::LuaFunction(LuaFunction&& other)
{
	*this = std::move(other);
}

LuaFunction::~LuaFunction()
{
	unref();
}

LuaFunction& LuaFunction::operator=(LuaFunction&& rhs)
{
	if (this->m_luaHandle != rhs.m_luaHandle)
	{
		this->ref(rhs.m_luaHandle);
		rhs.m_luaHandle = 0;
	}

	return *this;
}

LuaFunction& LuaFunction::operator=(int handle)
{
	this->ref(handle);
	return *this;
}

void LuaFunction::ref(int handle)
{
	this->unref();
	this->m_luaHandle = handle;
}

void LuaFunction::unref()
{
	if (m_luaHandle != 0)
	{
		ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(m_luaHandle);
		m_luaHandle = 0;
	}
}

void LuaFunction::operator()()
{
	ppush();
	pcall();
}

void LuaFunction::ppush()
{
	if (this->isvalid())
	{
		m_stack = LuaEngine::getInstance()->getLuaStack();
	}
	else
	{
		m_stack = NULL;
	}
	m_argCount = 0;
}

int LuaFunction::pcall()
{
	CC_ASSERT(m_luaHandle != 0);
	CC_ASSERT(m_stack != 0);

	if (m_stack == NULL)
		return 0;

	int ret = 0;
	if (m_luaHandle != 0)
	{
		ret = m_stack->executeFunctionByHandler(m_luaHandle, m_argCount);
		m_stack->clean();
	}
	return ret;
}

int LuaFunction::pcallEx(int argc)
{
	CC_ASSERT(m_luaHandle != 0);
	CC_ASSERT(m_stack != 0);

	if (m_stack == NULL)
		return 0;

	int ret = 0;
	if (m_luaHandle != 0)
	{
		ret = m_stack->executeFunctionByHandler(m_luaHandle, argc);
		m_stack->clean();
		m_stack = NULL;
	}
	return ret;
}

bool LuaFunction::isvalid()
{
	return m_luaHandle != 0;
}

void LuaFunction::pusharg(bool v)
{
	if (m_stack != NULL)
	{
		m_stack->pushBoolean(v);
		m_argCount++;
	}
}

void LuaFunction::pusharg(float v)
{
	if (m_stack != NULL)
	{
		m_stack->pushFloat(v);
		m_argCount++;
	}
}

void LuaFunction::pusharg(double v)
{
	if (m_stack != NULL)
	{
		m_stack->pushFloat((float)v);
		m_argCount++;
	}
}

void LuaFunction::pusharg(int v)
{
	if (m_stack != NULL)
	{
		m_stack->pushInt(v);
		m_argCount++;
	}
}

void LuaFunction::pusharg(unsigned int v)
{
	if (m_stack != NULL)
	{
		m_stack->pushInt(v);
		m_argCount++;
	}
}

void LuaFunction::pusharg(const std::string& v)
{
	if (m_stack != NULL)
	{
		m_stack->pushString(v.data(), v.size());
		m_argCount++;
	}
}

void LuaFunction::pusharg(const char* v)
{
	if (m_stack != NULL)
	{
		m_stack->pushString(v);
		m_argCount++;
	}
}

void LuaFunction::pushlstring(const char* v, unsigned int len)
{
	if (m_stack != NULL)
	{
		m_stack->pushString(v, len);
		m_argCount++;
	}
}

void LuaFunction::pushfunction(int handle)
{
	if (m_stack != NULL)
	{
		m_stack->pushFunctionByHandler(handle);
		m_argCount++;
	}
}

void LuaFunction::pushnil()
{
	if (m_stack != NULL)
	{
		m_stack->pushNil();
		m_argCount++;
	}
}

void LuaFunction::pushobject(cocos2d::Ref* objectValue, const char* typeName)
{
	if (m_stack != NULL)
	{
		m_stack->pushObject(objectValue, typeName);
		m_argCount++;
	}
}

void LuaFunction::pushLuaValue(const LuaValue& value)
{
	if (m_stack != NULL)
	{
		m_stack->pushLuaValue(value);
		m_argCount++;
	}
}

void LuaFunction::pushLuaValueDict(const LuaValueDict& dict)
{
	if (m_stack != NULL)
	{
		m_stack->pushLuaValueDict(dict);
		m_argCount++;
	}
}

void LuaFunction::pushLuaValueArray(const LuaValueArray& array)
{
	if (m_stack != NULL)
	{
		m_stack->pushLuaValueArray(array);
		m_argCount++;
	}
}
