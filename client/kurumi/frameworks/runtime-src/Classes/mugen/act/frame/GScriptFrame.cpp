#include "GScriptFrame.h"
#include "mugen/component/GActorComponent.h"
#include "mugen/component/GStaticDataComponent.h"

#if RUNTIME_IN_COOCS
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#endif

NS_G_BEGIN

#define KEY_SCRIPT_FRAME  "lua_frame"

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
int GScriptFrame::_index = 0;

GScriptFrame::GScriptFrame()
{
	m_type = GFrameType::SCRIPT_FRAME;
	m_isInitLuaTab = false;
	m_succeedLoadingScript = false;
	m_isScriptCode = false;
#if RUNTIME_IN_COOCS
	initClass();
#endif
}

GScriptFrame::~GScriptFrame()
{
#if RUNTIME_IN_COOCS
	removeLuaTable();
#endif
}

void GScriptFrame::serialize(GByteBuffer& byteBuffer)
{
	GEventFrame::serialize(byteBuffer);

	byteBuffer.writeBool(m_isScriptCode);
	byteBuffer.writeString(m_argStr);
	byteBuffer.writeString(m_scriptFile);
}

bool GScriptFrame::deserialize(GByteBuffer& byteBuffer)
{
	do
	{
		G_BREAK_IF(!GEventFrame::deserialize(byteBuffer));

		G_BREAK_IF(!byteBuffer.getBool(m_isScriptCode));
		G_BREAK_IF(!byteBuffer.getString(m_argStr));
		G_BREAK_IF(!byteBuffer.getString(m_scriptFile));

		return true;
	} while (0);
	return false;
}


void GScriptFrame::onEmit()
{
#if RUNTIME_IN_COOCS
	initLuaTable();
	if (m_succeedLoadingScript && getLuaFunction("emit"))
	{
		getUserData();
		LuaEngine::getInstance()->getLuaStack()->executeFunction(1);
	}
#endif
}

void GScriptFrame::onEnter(int32_t currentFrameIndex)
{
#if RUNTIME_IN_COOCS
	GEventFrame::onEnter(currentFrameIndex);

	initLuaTable();
	if (m_succeedLoadingScript && getLuaFunction("onEnter"))
	{
		getUserData();
		LuaEngine::getInstance()->getLuaStack()->pushInt(currentFrameIndex);
		LuaEngine::getInstance()->getLuaStack()->executeFunction(2);
	}
#endif
}

void GScriptFrame::onExit(int32_t currentFrameIndex)
{
#if RUNTIME_IN_COOCS
	GEventFrame::onExit(currentFrameIndex);

	initLuaTable();
	if (m_succeedLoadingScript && getLuaFunction("onExit"))
	{
		getUserData();
		LuaEngine::getInstance()->getLuaStack()->pushInt(currentFrameIndex);
		LuaEngine::getInstance()->getLuaStack()->executeFunction(2);
	}
#endif
}

#if RUNTIME_IN_COOCS


void GScriptFrame::initLuaTable()
{
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
}

void GScriptFrame::getScriptObjectInternal() const
{
	lua_State *l = LuaEngine::getInstance()->getLuaStack()->getLuaState();
	lua_pushstring(l, KEY_SCRIPT_FRAME);      // stack: "component"
	lua_rawget(l, LUA_REGISTRYINDEX);      // stack: LUA_REGISTRYINDEX["component"]
	lua_pushstring(l, m_strIndex.c_str());  // stack: LUA_REGISTRYINDEX["component"] strIndex
	lua_rawget(l, -2);                     // stack: LUA_REGISTRYINDEX["component"]
}

void* GScriptFrame::getScriptObject() const
{
	getScriptObjectInternal();
	return nullptr;
}


bool GScriptFrame::loadAndExecuteScript()
{
	// register native functions
	auto engine = LuaEngine::getInstance();
	lua_State *l = engine->getLuaStack()->getLuaState();

	std::string chunkName;
	// load script
	int error = LUA_ERRFILE;
	if (m_isScriptCode)
	{
		auto pSkill = this->getSkill();
		auto pStaticDataComponent = G_GetComponent(pSkill->getActorComponent(), GStaticDataComponent);

		auto binaryFileName = pStaticDataComponent->binaryFileName.c_str();
		auto skillName = pSkill->getName().c_str();
		auto timelineIndex = pSkill->getTrack()->getTimelineIndex(this->getTimeline());
		auto frameIndex = this->getTimeline()->getFrameIndex(this);

		chunkName = StringUtils::format("%s.%s.timeline_%d.%d", binaryFileName, skillName, timelineIndex, frameIndex);

		if (m_scriptFile.size() > 0)
			error = engine->getLuaStack()->luaLoadBuffer(l, (const char*)m_scriptFile.c_str(), (int)m_scriptFile.size(), chunkName.c_str());
	}
	else
	{
		auto scriptFile = "mugen/frame/" + m_scriptFile + ".lua";
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
		G_LOG("GScriptFrame::loadAndExecuteScript: %s", lua_tostring(l, -1));
		lua_pop(l, 1);
		return false;
	}

	// execute script
	error = lua_pcall(l, 0, 1, 0);
	if (error)
	{
		G_LOG("GScriptFrame::loadAndExecuteScript: %s", lua_tostring(l, -1));
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

void GScriptFrame::storeLuaTable()
{
	lua_State *l = LuaEngine::getInstance()->getLuaStack()->getLuaState();

	_index++;
	m_strIndex.append(StringUtils::toString(_index));

	// LUA_REGISTRYINDEX["component"][strIndex] = table return from lua
	lua_pushstring(l, KEY_SCRIPT_FRAME);          // stack: table_return_from_lua "component"
	lua_rawget(l, LUA_REGISTRYINDEX);          // stack: table_return_from_lua table_of_component
	lua_pushstring(l, m_strIndex.c_str());      // stack: table_return_from_lua table_of_component strIndex
	lua_pushvalue(l, -3);                      // stack: table_return_from_lua table_of_component strIndex table_return_from_lua
	lua_rawset(l, -3);                         // stack: table_return_from_lua table_of_component
	lua_pop(l, 1);                             // stack: table_return_from_lua

	// add table's elements to userdata's metatable
	object_to_luaval<GScriptFrame>(l, "GScriptFrame", this);  // stack: table_return_from_lua userdata
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

void GScriptFrame::getUserData()
{
	lua_State *l = LuaEngine::getInstance()->getLuaStack()->getLuaState();
	object_to_luaval<GScriptFrame>(l, "GScriptFrame", this);
}

bool GScriptFrame::getLuaFunction(const std::string& functionName)
{
	lua_State *l = LuaEngine::getInstance()->getLuaStack()->getLuaState();

	lua_pushstring(l, KEY_SCRIPT_FRAME);                // stack: "component"
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


void GScriptFrame::removeLuaTable()
{
	if (m_succeedLoadingScript)
	{
		// LUA_REGISTRYINDEX["component"][strIndex] = nil

		lua_State *l = LuaEngine::getInstance()->getLuaStack()->getLuaState();

		lua_pushstring(l, KEY_SCRIPT_FRAME);      // stack: "component"
		lua_rawget(l, LUA_REGISTRYINDEX);      // stack: LUA_REGISTRYINDEX["component"]
		lua_pushstring(l, m_strIndex.c_str());  // stack: LUA_REGISTRYINDEX["component"] strIndex
		lua_pushnil(l);                        // stack: LUA_REGISTRYINDEX["component"] strIndex nil
		lua_rawset(l, -3);                     // stack: LUA_REGISTRYINDEX["component"]
	}
}

void GScriptFrame::initClass()
{
	static bool run = true;
	if (run)
	{
		// LUA_REGISTRYINDEX["component"] = new table

		LuaEngine* engine = LuaEngine::getInstance();
		lua_State* l = engine->getLuaStack()->getLuaState();

		lua_pushstring(l, KEY_SCRIPT_FRAME);              // stack: "component"
		lua_newtable(l);                               // stack: "component" table
		lua_rawset(l, LUA_REGISTRYINDEX);              // stack: -

		run = false;
	}
}

#endif


NS_G_END
