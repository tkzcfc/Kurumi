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

	GNoticeCenter* noticeCenter(http_method method);

	G_FORCEINLINE GNoticeCenter* getPathNoticeCenter();

	G_FORCEINLINE net_uv::HttpServer* httpSvr();

	void delListener(void* tag);

private:
	std::unique_ptr<net_uv::HttpServer> m_httpSvr;
	std::unique_ptr<GNoticeCenter>     m_noticeCenter[HTTP_SOURCE + 1];
	std::unique_ptr<GNoticeCenter>     m_pathNoticeCenter;
};

net_uv::HttpServer* GHttpService::httpSvr()
{
	return m_httpSvr.get();
}
GNoticeCenter* GHttpService::getPathNoticeCenter()
{
	return m_pathNoticeCenter.get();
}

