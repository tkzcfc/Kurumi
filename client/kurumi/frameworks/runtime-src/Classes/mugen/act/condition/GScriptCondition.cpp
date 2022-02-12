#include "GScriptCondition.h"
#include "mugen/act/GChannel.h"
#include "mugen/act/GSkill.h"
#include "mugen/component/GActorComponent.h"
#include "mugen/component/GStaticDataComponent.h"
#if RUNTIME_IN_COOCS
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#endif

NS_G_BEGIN


#define KEY_CONDITION  "lua_condition"

#if RUNTIME_IN_COOCS
namespace {
	void adjustScriptFileName(std::string& scriptFileName)
	{
		assert(scriptFileName.size() > 4);

		auto fileUtils = FileUtils::getInstance();
		if (fileUtils->isFileExist(scriptFileName))
			return;

		const std::string luaSuffix(".lua");
		const std::string luacSuffix(".luac");

		// xxx.lua -> xxx.luac or
		// xxx.luac -> xxx.lua
		if (scriptFileName.compare(scriptFileName.size() - luaSuffix.size(), luaSuffix.size(), luaSuffix) == 0)
			scriptFileName.replace(scriptFileName.size() - luaSuffix.size(), luaSuffix.size(), luacSuffix);
		else
			scriptFileName.replace(scriptFileName.size() - luacSuffix.size(), luacSuffix.size(), luaSuffix);
	}
}
#endif

int GScriptCondition::_index = 0;


GScriptCondition::GScriptCondition()
{
	m_type = GConditionType::SCRIPT_CONDITION;
	m_isInitLuaTab = false;
	m_succeedLoadingScript = false;
	m_isScriptCode = false;

#if RUNTIME_IN_COOCS
	initClass();
#endif
}

GScriptCondition::~GScriptCondition()
{
#if RUNTIME_IN_COOCS
	if (m_succeedLoadingScript && getLuaFunction("destroy"))
	{
		getUserData();
		LuaEngine::getInstance()->getLuaStack()->executeFunction(1);
	}
	removeLuaTable();
#endif
}

void GScriptCondition::serialize(GByteBuffer& byteBuffer)
{
	GCondition::serialize(byteBuffer);

	byteBuffer.writeBool(m_isScriptCode);
	byteBuffer.writeString(m_argStr);
	byteBuffer.writeString(m_scriptFile);
}

bool GScriptCondition::deserialize(GByteBuffer& byteBuffer)
{
	do
	{
		G_BREAK_IF(!GCondition::deserialize(byteBuffer));

		G_BREAK_IF(!byteBuffer.getBool(m_isScriptCode));
		G_BREAK_IF(!byteBuffer.getString(m_argStr));
		G_BREAK_IF(!byteBuffer.getString(m_scriptFile));

		return true;
	} while (false);
	return false;
}

bool GScriptCondition::check()
{
#if RUNTIME_IN_COOCS
	if (false == m_isInitLuaTab)
	{
		m_isInitLuaTab = true;
		m_succeedLoadingScript = loadAndExecuteScript();

		if (m_succeedLoadingScript && getLuaFunction("ctor"))
		{
			getUserData();
			LuaEngine::getInstance()->getLuaStack()->pushString(m_argStr.c_str());
			LuaEngine::getInstance()->getLuaStack()->executeFunction(2);
		}
	}

	if (m_succeedLoadingScript && getLuaFunction("check"))
	{
		getUserData();
		return (bool)LuaEngine::getInstance()->getLuaStack()->executeFunction(1);
	}
#endif
	return false;
}

#if RUNTIME_IN_COOCS

void GScriptCondition::rest()
{
	if (m_succeedLoadingScript && getLuaFunction("rest"))
	{
		getUserData();
		LuaEngine::getInstance()->getLuaStack()->executeFunction(1);
	}
}

void GScriptCondition::getScriptObjectInternal() const
{
	lua_State *l = LuaEngine::getInstance()->getLuaStack()->getLuaState();
	lua_pushstring(l, KEY_CONDITION);      // stack: "component"
	lua_rawget(l, LUA_REGISTRYINDEX);      // stack: LUA_REGISTRYINDEX["component"]
	lua_pushstring(l, m_strIndex.c_str());  // stack: LUA_REGISTRYINDEX["component"] strIndex
	lua_rawget(l, -2);                     // stack: LUA_REGISTRYINDEX["component"]
}

void* GScriptCondition::getScriptObject() const
{
	getScriptObjectInternal();
	return nullptr;
}


bool GScriptCondition::loadAndExecuteScript()
{
	// register native functions
	auto engine = LuaEngine::getInstance();
	lua_State *l = engine->getLuaStack()->getLuaState();

	std::string chunkName;
	// load script
	int error = LUA_ERRFILE;
	if (m_isScriptCode)
	{
		auto pSkill = this->getChannel()->getSkill();
		auto pStaticDataComponent = G_GetComponent(pSkill->getActorComponent(), GStaticDataComponent);

		auto binaryFileName = pStaticDataComponent->binaryFileName.c_str();
		auto skillName = pSkill->getName().c_str();
		auto channelIndex = pSkill->getChannelIndex(this->getChannel());
		auto conditionIndex = this->getChannel()->getConditionIndex(this);

		chunkName = StringUtils::format("%s.%s.channel_%d.%d", binaryFileName, skillName, channelIndex, conditionIndex);

		if (m_scriptFile.size() > 0)
			error = engine->getLuaStack()->luaLoadBuffer(l, (const char*)m_scriptFile.c_str(), (int)m_scriptFile.size(), chunkName.c_str());
	}
	else
	{
		auto scriptFile = "mugen/condition/" + m_scriptFile + ".lua";
		adjustScriptFileName(scriptFile);
		chunkName = scriptFile;

		auto fileUtils = FileUtils::getInstance();
		std::string fullPathOfScript = fileUtils->fullPathForFilename(scriptFile);
		Data data = fileUtils->getDataFromFile(fullPathOfScript);
		if (data.getSize() > 0)
			error = engine->getLuaStack()->luaLoadBuffer(l, (const char*)data.getBytes(), (int)data.getSize(), fullPathOfScript.c_str());
	}
	if (error)
	{
		G_LOG("GScriptCondition::loadAndExecuteScript: %s", lua_tostring(l, -1));
		lua_pop(l, 1);
		return false;
	}

	// execute script
	error = lua_pcall(l, 0, 1, 0);
	if (error)
	{
		G_LOG("GScriptCondition::loadAndExecuteScript: %s", lua_tostring(l, -1));
		lua_pop(l, 1);
		return false;
	}

	// check the return value from lua script is a table
	int type = lua_type(l, -1);
	if (type != LUA_TTABLE)
	{
		G_LOG("%s should return a table, or the script component can not work currectly", chunkName.c_str());
		return false;
	}

	storeLuaTable();
	return true;
}

void GScriptCondition::storeLuaTable()
{
	lua_State *l = LuaEngine::getInstance()->getLuaStack()->getLuaState();

	_index++;
	m_strIndex.append(StringUtils::toString(_index));

	// LUA_REGISTRYINDEX["component"][strIndex] = table return from lua
	lua_pushstring(l, KEY_CONDITION);          // stack: table_return_from_lua "component"
	lua_rawget(l, LUA_REGISTRYINDEX);          // stack: table_return_from_lua table_of_component
	lua_pushstring(l, m_strIndex.c_str());      // stack: table_return_from_lua table_of_component strIndex
	lua_pushvalue(l, -3);                      // stack: table_return_from_lua table_of_component strIndex table_return_from_lua
	lua_rawset(l, -3);                         // stack: table_return_from_lua table_of_component
	lua_pop(l, 1);                             // stack: table_return_from_lua

	// add table's elements to userdata's metatable
	object_to_luaval<GScriptCondition>(l, "GScriptCondition", this);  // stack: table_return_from_lua userdata
	lua_getmetatable(l, -1);                   // stack: table_return_from_lua userdata mt
	lua_remove(l, -2);                         // stack: table_return_from_lua mt
	lua_pushnil(l);                            // stack: table_return_from_lua mt nil
	while (lua_next(l, -3))                    // stack: table_return_from_lua mt key value
	{
		lua_pushvalue(l, -2);                  // stack: table_return_from_lua mt key value key
		lua_insert(l, -2);                     // stack: table_return_from_lua mt key key value
		lua_rawset(l, -4);                     // stack: table_return_from_lua mt key
	}
	lua_pop(l, 2);
}

void GScriptCondition::getUserData()
{
	lua_State *l = LuaEngine::getInstance()->getLuaStack()->getLuaState();
	object_to_luaval<GScriptCondition>(l, "GScriptCondition", this);
}

bool GScriptCondition::getLuaFunction(const std::string& functionName)
{
	lua_State *l = LuaEngine::getInstance()->getLuaStack()->getLuaState();

	lua_pushstring(l, KEY_CONDITION);                // stack: "component"
	lua_rawget(l, LUA_REGISTRYINDEX);                // stack: table_of_component
	lua_pushstring(l, m_strIndex.c_str());            // stack: table_of_component strIndex
	lua_rawget(l, -2);                               // stack: table_of_component table_of_this
	lua_pushstring(l, functionName.c_str());         // stack: table_of_component table_of_this "update"
	lua_rawget(l, -2);                               // stack: table_of_component table_of_this table_of_this["update"]
	lua_remove(l, -2);                               // stack: table_of_component table_of_this["update"]
	lua_remove(l, -2);                               // stack: table_of_this["update"]

	int type = lua_type(l, -1);
	//    if (type != LUA_TFUNCTION)
	//    {
	//        G_LOG("can not get %s function from %s", functionName.c_str(), _scriptFileName.c_str());
	//    }

	return type == LUA_TFUNCTION;
}


void GScriptCondition::removeLuaTable()
{
	if (m_succeedLoadingScript)
	{
		// LUA_REGISTRYINDEX["component"][strIndex] = nil

		lua_State *l = LuaEngine::getInstance()->getLuaStack()->getLuaState();

		lua_pushstring(l, KEY_CONDITION);      // stack: "component"
		lua_rawget(l, LUA_REGISTRYINDEX);      // stack: LUA_REGISTRYINDEX["component"]
		lua_pushstring(l, m_strIndex.c_str());  // stack: LUA_REGISTRYINDEX["component"] strIndex
		lua_pushnil(l);                        // stack: LUA_REGISTRYINDEX["component"] strIndex nil
		lua_rawset(l, -3);                     // stack: LUA_REGISTRYINDEX["component"]
	}
}

void GScriptCondition::initClass()
{
	static bool run = true;
	if (run)
	{
		// LUA_REGISTRYINDEX["component"] = new table

		LuaEngine* engine = LuaEngine::getInstance();
		lua_State* l = engine->getLuaStack()->getLuaState();

		lua_pushstring(l, KEY_CONDITION);              // stack: "component"
		lua_newtable(l);                               // stack: "component" table
		lua_rawset(l, LUA_REGISTRYINDEX);              // stack: -

		run = false;
	}


}

#endif


NS_G_END