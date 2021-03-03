#pragma once

#include "GClassTypeId.h"
#include "GPlatformMacros.h"

// 服务启动成功
static const uint32_t SCODE_START_SUCCESS = 0;
// 服务启动失败,且此服务不影响系统正常运行,系统输出启动失败信息就行了
static const uint32_t SCODE_START_FAIL_RUN = 1;
// 服务启动失败,系统运行不需要此服务,不算错误
static const uint32_t SCODE_START_FAIL_NO_ERR = 2;
// 服务启动失败,且此服务为系统重要服务,即将推出APP
static const uint32_t SCODE_START_FAIL_EXIT_APP = 3;

class GIService
{
public:

	enum class GServiceStatus
	{
		RUNNING,
		STOP_ING,
		STOP,
	};

	GIService();

	virtual ~GIService();

public:

	virtual uint32_t onInit() = 0;

	virtual void onStartService() = 0;

	virtual void onStopService() = 0;

	virtual void onUpdate(float) = 0;

	virtual void onDestroy() = 0;

public:

	virtual void stopService(const std::function<void()>& call = NULL);

	G_FORCEINLINE bool isRunning();

	G_FORCEINLINE bool isStop();

	virtual const char* serviceName() const;
	
protected:
	friend class GServiceMgr;
	GServiceStatus m_status;
	GServiceMgr* m_serviceMgr;
	std::function<void()> m_stopCallback;
};


bool GIService::isRunning()
{
	return m_status == GServiceStatus::RUNNING;
}

bool GIService::isStop()
{
	return m_status == GServiceStatus::STOP;
}


/////////////////////////////////////////////////////////////////////////////////

template<class T>
detail::GTypeId GServiceTypeId()
{
	return detail::GClassTypeId<GIService>::GetTypeId<T>();
}

#define G_DEFINE_SERVICE(SNAME) const char* serviceName() const override { return #SNAME; }