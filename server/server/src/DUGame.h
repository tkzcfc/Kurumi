#pragma once

#include "DUScheduler.h"
#include "windows.h"

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

protected:
	void mainLoop();
	void calculateDeltaTime();
protected:
	LARGE_INTEGER m_animationInterval;

	DUScheduler* m_scheduler;

	bool m_nextDeltaTimeZero;
	float m_deltaTime;
	std::chrono::steady_clock::time_point m_lastUpdate;
};

