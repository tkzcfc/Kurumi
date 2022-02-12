#include "GHttpService.h"
#include "GConfigService.h"
#include "GApplication.h"


uint32_t GHttpService::onInit()
{
	G_CHECK_SERVICE(GConfigService);

	auto cfgService = m_serviceMgr->getService<GConfigService>();

	auto& ini = cfgService->iniReader();
	auto appName = GApplication::getInstance()->getAppName();

	// 不需要此服务
	if (ini.GetBoolean(appName, "HttpServiceEnable", false) == false)
		return SCODE_START_FAIL_NO_ERR;

	auto ip = ini.Get(appName, "HttpServiceIP", "");
	auto port = ini.GetInteger(appName, "HttpServicePort", 0);
	auto isIPV6 = ini.GetBoolean(appName, "HttpServiceIPV6", false);
	auto maxCount = ini.GetInteger(appName, "HttpServiceMaxCount", 0xffff);

	if (ip.empty() || port <= 0)
		return SCODE_START_FAIL_EXIT_APP;

	m_httpSvr = std::make_unique<net_uv::HttpServer>();
	m_httpSvr->setCloseCallback([=]() 
	{
		this->stopServiceFinish();
	});
	m_httpSvr->setHttpCallback([=](const net_uv::HttpRequest& request, net_uv::HttpResponse* response)
	{
		int number1 = 0;
		auto center = noticeCenter(request.method());
		if (center)
		{
			number1 = center->emitEvent(request.path(), request, response);
		}

		auto number2 = m_pathNoticeCenter->emitEvent(request.path(), request, response);

		if (number1 == 0 && number2 == 0)
		{
			response->setStatusCode(net_uv::HttpResponse::HttpStatusCode::k404NotFound);
			response->setStatusMessage("Not Found");
			response->setCloseConnection(true);
		}
	});
	
	if (m_httpSvr->startServer(ip.c_str(), port, isIPV6, maxCount) == false)
		return SCODE_START_FAIL_EXIT_APP;

	m_pathNoticeCenter = std::make_unique<GNoticeCenter>();
	
	return SCODE_START_SUCCESS;
}

void GHttpService::onStartService()
{}

void GHttpService::onStopService()
{
	m_httpSvr->stopServer();
}

void GHttpService::onUpdate(float)
{
	m_httpSvr->updateFrame();
}

void GHttpService::onDestroy()
{}

GNoticeCenter* GHttpService::noticeCenter(http_method method)
{
	if (method < 0 || method > HTTP_SOURCE)
	{
		G_ASSERT(0);
		return NULL;
	}
	if (m_noticeCenter[method] == NULL)
	{
		m_noticeCenter[method] = std::make_unique<GNoticeCenter>();
	}
	return m_noticeCenter[method].get();
}

void GHttpService::delListener(void* tag)
{
	for (auto i = 0; i <= HTTP_SOURCE; ++i)
	{
		if (m_noticeCenter[i])
		{
			m_noticeCenter[i]->delListener(tag);
		}
	}
	m_pathNoticeCenter->delListener(tag);
}

