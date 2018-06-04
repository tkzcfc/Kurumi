#pragma once

#include "DUScheduler.h"
#include "windows.h"
#include "DULuaprint.h"

class DUGame
{
	static DUGame* instance;
	DUGame();
	~DUGame();
public:
	static DUGame* getInstance();
	static void destroy();

	void setInterval(float interval);
	
	void run();

	bool isFileExist(const char* filename);

	inline lua_State* luaState() { return m_luaState; }

protected:

	void initGLog();
	
	void mainLoop();

	void calculateDeltaTime();
protected:

	lua_State* m_luaState;

	LARGE_INTEGER m_animationInterval;

	DUScheduler* m_scheduler;

	bool m_nextDeltaTimeZero;
	float m_deltaTime;
	std::chrono::steady_clock::time_point m_lastUpdate;
};


