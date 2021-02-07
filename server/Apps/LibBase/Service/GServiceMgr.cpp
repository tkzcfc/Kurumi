#include "GServiceMgr.h"
#include "GScheduler.h"

GServiceMgr::GServiceMgr()
	: m_onStopFinishCall(NULL)
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
		LOG(WARNING) << "Service [" << it->serviceName() << "] started.";
		it->onStartService();
	}
}

void GServiceMgr::stopAllService(const std::function<void()>& call)
{
	for (auto it : m_arrService)
	{
		LOG(WARNING) << "Stopping service [" << it->serviceName() << "].";
		it->stopService([=]() {
			LOG(WARNING) << "Service [" << it->serviceName() << "] stopped.";
		});
	}

	m_onStopFinishCall = call;

	GScheduler::getInstance()->scheduleSelector([=](float)
	{
		if (getRunningCount() <= 0)
		{
			LOG(WARNING) << "All services stopped.";
			GScheduler::getInstance()->unScheduleSeletorByObject(this);
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
		if(!it->isStop())
			it->onUpdate(dt);
	}
}

void GServiceMgr::destroy()
{
	for (auto& it : m_arrService)
	{
		it->onDestroy();
	}

	for (auto& it : m_arrService)
	{
		delete it;
	}
	m_arrService.clear();
	m_serviceMap.clear();
	GScheduler::getInstance()->unScheduleSeletorByObject(this);
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
			count++;
	}
	return count;
}