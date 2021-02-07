#pragma once

#include "GIService.h"
#include <vector>
#include <map>

/// �������
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
	bool doesServiceExist() const;

	bool doesServiceExist(detail::GTypeId typeId) const;

	template <class TService>
	TService* getService() const;

	int32_t getRunningCount();

private:
	std::vector<GIService*> m_arrService;
	std::map<detail::GTypeId, GIService*> m_serviceMap;
	std::function<void()> m_onStopFinishCall;
};


template <class TService, class... Types>
TService* GServiceMgr::addService(Types&&... args)
{
	static_assert(std::is_base_of<GIService, TService>(), "Template argument does not inherit from GIService");

	G_ASSERT(!doesServiceExist<TService>());

	TService* service = new TService(std::forward<Types>(args)...);
	service->m_serviceMgr = this;
	if (!service->onInit())
	{
		LOG(ERROR) << "Failed to start service [" << service->serviceName() << "]";
		service->onDestroy();
		delete service;
		return NULL;
	}
	m_serviceMap[GServiceTypeId<TService>()] = service;
	m_arrService.push_back(service);
	return service;
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

