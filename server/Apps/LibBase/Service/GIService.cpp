#include "GIService.h"
#include "GScheduler.h"

GIService::GIService()
	: m_status(GServiceStatus::STOP)
	, m_serviceMgr(NULL)
	, m_stopCallback(NULL)
{
}

GIService::~GIService()
{
	GScheduler::getInstance()->unScheduleSeletorByObject(this);
}

void GIService::stopService(const std::function<void()>& call)
{
	if (m_status == GServiceStatus::RUNNING)
	{
		m_stopCallback = call;
		m_status = GServiceStatus::STOP_ING;
		this->onStopService();

		if (m_stopCallback)
		{
			GScheduler::getInstance()->scheduleSelector([=](float)
			{
				if (this->isStop())
				{
					GScheduler::getInstance()->unScheduleSeletorByObject(this);
					m_stopCallback();
					m_stopCallback = NULL;
				}
			}, this, 0.0f, false, "check");
		}
	}
}

const char* GIService::serviceName() const
{
	return "GIService";
}
