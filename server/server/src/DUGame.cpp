#include "DUGame.h"


DUGame* DUGame::instance = NULL;

DUGame::DUGame()
{
	m_lastUpdate = std::chrono::steady_clock::now();
	m_nextDeltaTimeZero = true;
	m_deltaTime = 0.0f;

	m_animationInterval.QuadPart = 0;
	setInterval(1 / 40.0f);
	m_scheduler = DUScheduler::getInstance();
}

DUGame::~DUGame()
{
}

DUGame* DUGame::getInstance()
{
	if (instance == NULL)
	{
		instance = new DUGame();
	}
	return instance;
}

void DUGame::destroy()
{
	if (instance)
	{
		delete instance;
		instance = NULL;
	}
}

void DUGame::setInterval(float interval)
{
	LARGE_INTEGER nFreq;
	QueryPerformanceFrequency(&nFreq);
	m_animationInterval.QuadPart = (LONGLONG)(interval * nFreq.QuadPart);
}

void DUGame::run()
{
	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;

	QueryPerformanceCounter(&nLast);
	
	while (true)
	{
		QueryPerformanceCounter(&nNow);
		if (nNow.QuadPart - nLast.QuadPart > m_animationInterval.QuadPart)
		{
			nLast.QuadPart = nNow.QuadPart - (nNow.QuadPart % m_animationInterval.QuadPart);
			this->mainLoop();
		}
		else
		{
			Sleep(1);
		}
	}
}

void DUGame::mainLoop()
{
	calculateDeltaTime();
	m_scheduler->update(m_deltaTime);
}

void DUGame::calculateDeltaTime()
{
	auto now = std::chrono::steady_clock::now();

	if (m_nextDeltaTimeZero)
	{
		m_deltaTime = 0;
		m_nextDeltaTimeZero = false;
	}
	else
	{
		m_deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - m_lastUpdate).count() / 1000000.0f;
		m_deltaTime = DU_MAX(0, m_deltaTime);
	}

	m_lastUpdate = now;
}

