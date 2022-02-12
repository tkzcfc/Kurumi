#include "GIService.h"
#include "GScheduler.h"

GIService::GIService()
	: m_status(GServiceStatus::STOP)
	, m_serviceMgr(NULL)
	, m_stopCallback(NULL)
	, m_enableUpdate(true)
{
}

GIService::~GIService()
{
	GScheduler::getInstance()->unScheduleTarget(this);
}

void GIService::stopService(const std::function<void()>& call)
{
	if (m_status == GServiceStatus::RUNNING)
	{
		LOG(INFO) << "Stopping service [" << this->serviceName() << "].";
		m_stopCallback = call;
		m_status = GServiceStatus::STOP_ING;
		this->onStopService();

		GScheduler::getInstance()->schedule([=](float)
		{
			if (this->isStop())
			{
				LOG(INFO) << "Service [" << this->serviceName() << "] stopped.";
				GScheduler::getInstance()->unSchedule(this, "check");
				if (m_stopCallback)
				{
					m_stopCallback();
					m_stopCallback = NULL;
				}
			}
		}, this, 0.0f, false, "check");
	}
}

void GIService::onStartService()
{}

void GIService::onStopService()
{
	stopServiceFinish();
}

void GIService::onUpdate(float)
{
	setEnableUpdate(false);
}

void GIService::onDestroy()
{}

const char* GIService::serviceName() const
{
	return "GIService";
}

void GIService::stopServiceFinish()
{
	m_status = GServiceStatus::STOP;
}
