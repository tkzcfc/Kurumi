#pragma once

#include "net_uv.h"
#include "GScheduler.h"
#include "Service/GServiceMgr.h"

class GApplication
{
public:

	GApplication(const std::string& appName);

	virtual ~GApplication();

	static GApplication* getInstance();

	int32_t run(uint32_t interval = 1000U / 100U);
	
	void end();

public:

	void updateFPS();

public:

	G_FORCEINLINE float getDeltaTime() const;

	G_FORCEINLINE uint32_t getDeltaTimeMillisecond() const;

	G_FORCEINLINE GScheduler* getScheduler() const;

	G_FORCEINLINE GServiceMgr* getServiceMgr() const;

	G_FORCEINLINE int32_t getFPS() const;

	G_FORCEINLINE const std::string& getAppName() const;

private:

	void init();

	void mainLoop();

private:
	GScheduler* m_scheduler;
	std::unique_ptr<GServiceMgr> m_serviceMgr;

	uint64_t m_lastTime;
	uint32_t m_deltaTimeMilli;
	float m_deltaTime;

	int32_t m_fps;
	int32_t m_fpst;

	uv_loop_t* m_loop;
	uv_timer_t m_updateTimer;
	uv_timer_t m_fpsTimer;

	std::string m_appName;

	static GApplication* uniqueInstance;
};


float GApplication::getDeltaTime() const
{
	return m_deltaTime;
}

uint32_t GApplication::getDeltaTimeMillisecond() const
{
	return m_deltaTimeMilli;
}

GScheduler* GApplication::getScheduler() const
{
	return m_scheduler;
}

GServiceMgr* GApplication::getServiceMgr() const
{
	return m_serviceMgr.get();
}

int32_t GApplication::getFPS() const
{
	return m_fps;
}

const std::string& GApplication::getAppName() const
{
	return m_appName;
}
