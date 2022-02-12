
#include "custom_lua_modules.h"
#include "LuaBasicConversions.h"
#include "lua_function/LuaFunction.h"
#include "game/lua_game.h"
#include "foundation/GTools.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "lua_video_auto.hpp"
#include "VideoCommon.h"

static int tolua_Cocos2d_Function_decompressZipAsync(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S, 1, 0, &tolua_err) ||
		!tolua_isstring(tolua_S, 2, 0, &tolua_err) ||
		!tolua_isboolean(tolua_S, 3, 0, &tolua_err) ||
		!toluafix_isfunction(tolua_S, 4, "LUA_FUNCTION", 0, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char *zip = luaL_checkstring(tolua_S, 1);
		const char *outDir = luaL_checkstring(tolua_S, 2);
		bool removeFile = (bool)tolua_toboolean(tolua_S, 3, 0);
		int result = toluafix_ref_function(tolua_S, 4, 0);

		int percent = LUA_NOREF;
		if (toluafix_isfunction(tolua_S, 5, "LUA_FUNCTION", 0, &tolua_err))
		{
			percent = toluafix_ref_function(tolua_S, 5, 0);
		}

		auto result_lamda = [=](bool ok, std::string err)
		{
			cocos2d::LuaStack *stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
			stack->pushBoolean(ok);
			stack->pushString(err.c_str(), err.size());
			stack->executeFunctionByHandler(result, 2);

			stack->removeScriptHandler(result);
			if (percent != LUA_NOREF)
			{
				stack->removeScriptHandler(percent);
			}
		};

		if (percent == LUA_NOREF)
		{
			GTools::decompressZipAsync(zip, outDir, removeFile, result_lamda);
		}
		else
		{
			GTools::decompressZipAsync(zip, outDir, removeFile, result_lamda, [=](int now, int total) 
			{
				cocos2d::LuaStack *stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
				stack->pushInt(now);
				stack->pushInt(total);
				stack->executeFunctionByHandler(percent, 2);
			});
		}
	}
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
				tolua_error(tolua_S, "#ferror in function 'decompressZipAsync'.", &tolua_err);
				return 0;
#endif
}


void custom_lua_modules(lua_State *L)
{
	LuaFunction::setGlobalLuaState(L);

	// game
	luaopen_game(L);
	// video
	register_all_cc_video(L);
	video::setLoggingFunction([](const std::string& log) {
		CCLOG("%s", log.c_str());
	});

	tolua_module(L, "cc", 0);
	tolua_beginmodule(L, "cc");
	tolua_function(L, "decompressZipAsync", tolua_Cocos2d_Function_decompressZipAsync);
	tolua_endmodule(L);
}
