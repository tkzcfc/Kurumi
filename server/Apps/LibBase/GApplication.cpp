#include "GApplication.h"

GApplication* GApplication::uniqueInstance = NULL;

GApplication* GApplication::getInstance()
{
	return uniqueInstance;
}

GApplication::GApplication(const std::string& appName)
{
	uniqueInstance = this;
	m_scheduler = NULL;
	m_lastTime = 0;
	m_deltaTimeMilli = 0;
	m_deltaTime = 0.0f;
	m_loop = NULL;
	m_fps = 0;
	m_fpst = 0;
	m_appName = appName;

	init();
}

GApplication::~GApplication()
{
}

void GApplication::init()
{
	m_scheduler = GScheduler::getInstance();
	m_serviceMgr = std::make_unique<GServiceMgr>();
}

int32_t GApplication::run(uint32_t interval)
{
	m_lastTime = 0;

	m_loop = uv_loop_new();

	// timer
	uv_timer_init(m_loop, &m_updateTimer);
	m_updateTimer.data = this;
	uv_timer_start(&m_updateTimer, [](uv_timer_t* handle) {
		auto* self = static_cast<GApplication*>(handle->data);
		self->mainLoop();
	}, 0, interval);

	// fps timer
	uv_timer_init(m_loop, &m_fpsTimer);
	m_fpsTimer.data = this;
	uv_timer_start(&m_fpsTimer, [](uv_timer_t* handle) {
		auto* self = static_cast<GApplication*>(handle->data);
		self->updateFPS();
	}, 0, 1000);

	// loop
	uv_run(m_loop, UV_RUN_DEFAULT);

	m_serviceMgr->destroy();
	m_serviceMgr = NULL;
	m_scheduler->unScheduleAll();

	uv_loop_delete(m_loop);
	return 1;
}

void GApplication::end()
{
	if (m_serviceMgr)
	{
		m_serviceMgr->stopAllService([=]() 
		{
			uv_timer_stop(&m_updateTimer);
			uv_close((uv_handle_t*)&m_updateTimer, NULL);
			uv_timer_stop(&m_fpsTimer);
			uv_close((uv_handle_t*)&m_fpsTimer, NULL);			
			uv_stop(m_loop);
		});
	}
}

void GApplication::mainLoop()
{
	m_fpst++;
	if (m_lastTime <= 0)
	{
		m_lastTime = uv_now(m_loop);
		m_serviceMgr->start();
		return;
	}
	m_deltaTimeMilli = (uint32_t)(uv_now(m_loop) - m_lastTime);
	m_deltaTime = m_deltaTimeMilli / 1000.0f;
	m_lastTime = uv_now(m_loop);

	m_scheduler->update(m_deltaTime);
	m_serviceMgr->update(m_deltaTime);
}


void GApplication::updateFPS()
{
	m_fps = m_fpst;
	m_fpst = 0;
#if G_TARGET_PLATFORM == G_PLATFORM_WIN32
	char szTitle[64] = { 0 };
	sprintf(szTitle, "%s(fps:%d)", m_appName.c_str(), m_fps);
	::SetConsoleTitleA(szTitle);
#endif
}

