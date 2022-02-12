#include "GServiceMgr.h"
#include "GScheduler.h"
#include "GApplication.h"

GServiceMgr::GServiceMgr()
	: m_onStopFinishCall(NULL)
	, m_startFail(false)
{
}

GServiceMgr::~GServiceMgr()
{
	destroy();
}

void GServiceMgr::start()
{
	for (auto& it : m_arrService)
	{
		it->m_status = GIService::GServiceStatus::RUNNING;
		LOG(INFO) << "Service [" << it->serviceName() << "] started.";
		it->onStartService();
	}

	if (m_startFail)
	{
		GApplication::getInstance()->end();
	}
}

void GServiceMgr::stopAllService(const std::function<void()>& call)
{
	for (int32_t i = m_arrService.size() - 1; i >= 0; --i)
	{
		m_arrService[i]->stopService();
	}

	m_onStopFinishCall = call;

	GScheduler::getInstance()->schedule([=](float)
	{
		if (getRunningCount() <= 0)
		{
			LOG(INFO) << "All services stopped.";
			GScheduler::getInstance()->unSchedule(this, "check");
			if (m_onStopFinishCall)
			{
				m_onStopFinishCall();
				m_onStopFinishCall = NULL;
			}
		}
	}, this, 0.0f, false, "check");
}

void GServiceMgr::update(float dt)
{
	for (auto& it : m_arrService)
	{
		if(it->isEnableUpdate() && false == it->isStop())
			it->onUpdate(dt);
	}

	while (false == m_destroyService.empty())
	{
		auto pService = m_destroyService.back();

		for (auto it = m_arrService.begin(); it != m_arrService.end(); ++it)
		{
			if (*it == pService)
			{
				pService->onDestroy();
				delete pService;
				m_arrService.erase(it);
				break;
			}
		}

		for (auto it = m_serviceMap.begin(); it != m_serviceMap.end(); ++it)
		{
			if (it->second == pService)
			{
				m_serviceMap.erase(it);
				break;
			}
		}

		m_destroyService.pop_back();
	}
}

void GServiceMgr::destroy()
{
	if (m_arrService.empty() == false)
	{
		for (int32_t i = m_arrService.size() - 1; i >= 0; --i)
		{
			m_arrService[i]->onDestroy();
		}
		for (int32_t i = m_arrService.size() - 1; i >= 0; --i)
		{
			delete m_arrService[i];
		}
	}
	m_arrService.clear();
	m_serviceMap.clear();
	GScheduler::getInstance()->unScheduleTarget(this);
}

bool GServiceMgr::doesServiceExist(detail::GTypeId typeId) const
{
	return m_serviceMap.find(typeId) != m_serviceMap.end();
}

int32_t GServiceMgr::getRunningCount()
{
	int32_t count = 0;
	for (const auto& it : m_arrService)
	{
		if (!it->isStop())
		{
			count++;
		}
	}
	return count;
}

void GServiceMgr::setStartFail()
{
	if (m_startFail)
		return;

	m_startFail = true;
}