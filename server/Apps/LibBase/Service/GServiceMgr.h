#pragma once

#include "GIService.h"
#include <vector>
#include <map>

/// 服务管理
class GServiceMgr
{
public:

	GServiceMgr();

	virtual ~GServiceMgr();

	void start();

	void stopAllService(const std::function<void()>& call);

	void update(float dt);

	void destroy();

	template <class TService, class... Types>
	TService* addService(Types&&... args);

	template <class TService>
	bool removeService();

	template <class TService>
	bool doesServiceExist() const;

	bool doesServiceExist(detail::GTypeId typeId) const;

	template <class TService>
	TService* getService() const;

	int32_t getRunningCount();

private:

	void setStartFail();

private:
	std::vector<GIService*> m_arrService;
	std::map<detail::GTypeId, GIService*> m_serviceMap;
	std::function<void()> m_onStopFinishCall;
	std::vector<GIService*> m_destroyService;
	bool m_startFail;
};


template <class TService, class... Types>
TService* GServiceMgr::addService(Types&&... args)
{
	if (m_startFail)
		return NULL;

	static_assert(std::is_base_of<GIService, TService>(), "Template argument does not inherit from GIService");

	G_ASSERT(!doesServiceExist<TService>());

	TService* service = new TService(std::forward<Types>(args)...);
	G_ASSERT(strcmp(service->serviceName(), "GIService") != 0);

	service->m_serviceMgr = this;

	auto code = service->onInit();
	if (SCODE_START_SUCCESS != code)
	{
		switch (code)
		{
		case SCODE_START_SUCCESS:
		{}break;

		case SCODE_START_FAIL_EXIT_APP:
		{
			LOG(ERROR) << "Failed to start service [" << service->serviceName() << "], about to exit";
			this->setStartFail();
		}break;

		case SCODE_START_FAIL_NO_ERR:
		{
			LOG(WARNING) << "Failed to start service [" << service->serviceName() << "], Service configuration not enabled";
		}break;

		case SCODE_START_FAIL_RUN:
		{
			LOG(WARNING) << "Failed to start service [" << service->serviceName() << "]";
		}break;

		default:
			// unknown code
			G_ASSERT(false);
			break;
		}

		service->onDestroy();
		delete service;
		return NULL;
	}
	m_serviceMap[GServiceTypeId<TService>()] = service;
	m_arrService.push_back(service);
	return service;
}

template <class TService>
bool GServiceMgr::removeService()
{
	auto pService = getService<TService>();
	if (pService == NULL)
	{
		return false;
	}

	pService->stopService([=]() {
		m_destroyService.push_back(pService);
	});

	return true;
}

template <class TService>
bool GServiceMgr::doesServiceExist() const
{
	static_assert(std::is_base_of<GIService, TService>(), "Template argument does not inherit from GIService");
	return doesServiceExist(GServiceTypeId<TService>());
}

template <class TService>
TService* GServiceMgr::getService() const
{
	auto it = m_serviceMap.find(GServiceTypeId<TService>());
	if (it != m_serviceMap.end())
	{
		return dynamic_cast<TService*>(it->second);
	}
	return NULL;
}

