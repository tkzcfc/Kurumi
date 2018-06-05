#include "lua-modules/lua_modules.h"
#include "DUGame.h"

void lua_pre_register_all(lua_State* L)
{
	luaL_openlibs(L);
	preload_lua_modules(L);

	const luaL_reg global_functions[] =
	{
		{ "print", lua_print },
		{ "release_print",lua_release_print },
		{ nullptr, nullptr }
	};
	luaL_register(L, "_G", global_functions);
}

void main()
{
	// 控制台显示乱码纠正  
	system("chcp 65001"); //设置字符集 （使用SetConsoleCP(65001)设置无效，原因未知）  

	CONSOLE_FONT_INFOEX info = { 0 }; // 以下设置字体  
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = 16; // leave X as zero  
	info.FontWeight = FW_NORMAL;
	wcscpy(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);

	const char* startlua = "lua_code/main.lua";

	auto instance = DUGame::getInstance();

	if (!instance->isFileExist(startlua))
	{
		return;
	}

	lua_State* L = instance->luaState();
	
	lua_pre_register_all(L);

	luaL_dofile(L, startlua);

	instance->setInterval(1 / 40.0f);
	instance->run();

	DUGame::destroy();
}

