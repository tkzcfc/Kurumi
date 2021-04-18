#pragma once

#include "GIService.h"
#include "GNoticeCenter.h"

// http服务
class GHttpService final : public GIService
{
public:

	G_DEFINE_SERVICE(GHttpService);

	virtual uint32_t onInit() override;

	virtual void onStartService() override;

	virtual void onStopService() override;

	virtual void onUpdate(float) override;

	virtual void onDestroy() override;

	G_FORCEINLINE GNoticeCenter* noticeCenter();

	G_FORCEINLINE net_uv::HttpServer* httpSvr();

private:
	std::unique_ptr<net_uv::HttpServer> m_httpSvr;
	std::unique_ptr<GNoticeCenter>     m_noticeCenter;
};

GNoticeCenter* GHttpService::noticeCenter()
{
	return m_noticeCenter.get();
}

net_uv::HttpServer* GHttpService::httpSvr()
{
	return m_httpSvr.get();
}

