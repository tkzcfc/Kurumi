#pragma once

#include "Utils/GClassTypeId.h"
#include "GPlatformMacros.h"

// 服务启动成功
static const uint32_t SCODE_START_SUCCESS = 0;
// 服务启动失败,且此服务不影响系统正常运行,系统输出启动失败信息就行了
static const uint32_t SCODE_START_FAIL_RUN = 1;
// 服务启动失败,系统运行不需要此服务,不算错误
static const uint32_t SCODE_START_FAIL_NO_ERR = 2;
// 服务启动失败,且此服务为系统重要服务,即将退出APP
static const uint32_t SCODE_START_FAIL_EXIT_APP = 3;

class GServiceMgr;
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

	virtual void onStartService();

	virtual void onStopService();

	virtual void onUpdate(float);

	virtual void onDestroy();

public:

	virtual void stopService(const std::function<void()>& call = NULL);

	G_FORCEINLINE void setEnableUpdate(bool value);

	G_FORCEINLINE bool isRunning();

	G_FORCEINLINE bool isStop();

	G_FORCEINLINE bool isEnableUpdate();

	virtual const char* serviceName() const;

protected:

	void stopServiceFinish();
	
protected:
	friend class GServiceMgr;
	GServiceStatus m_status;
	GServiceMgr* m_serviceMgr;
	std::function<void()> m_stopCallback;
	bool m_enableUpdate;
};


bool GIService::isRunning()
{
	return m_status == GServiceStatus::RUNNING;
}

bool GIService::isStop()
{
	return m_status == GServiceStatus::STOP;
}

bool GIService::isEnableUpdate()
{
	return m_enableUpdate;
}

void GIService::setEnableUpdate(bool value)
{
	m_enableUpdate = value;
}


/////////////////////////////////////////////////////////////////////////////////

template<class T>
detail::GTypeId GServiceTypeId()
{
	return detail::GClassTypeId<GIService>::GetTypeId<T>();
}

#define G_DEFINE_SERVICE(SNAME) const char* serviceName() const override { return #SNAME; }
#define G_ERROR_MISS_SERVICE(service) LOG(ERROR) << "[" << this->serviceName() << "]" << " Missing dependent service [" << #service << "]";
#define G_CHECK_SERVICE(service) if(m_serviceMgr->getService<service>() == NULL) { G_ERROR_MISS_SERVICE(service); return SCODE_START_FAIL_EXIT_APP; }
