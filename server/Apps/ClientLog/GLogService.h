#pragma once

#include "GLibBase.h"


// 日志服务
class GLogService : public GIService
{
public:

	G_DEFINE_SERVICE(GLogService);

	virtual uint32_t onInit() override;

	virtual void onStopService() override;

private:

	void init_Http();
protected:
	
	void onHttpRequest_LUA_TRACKBACK(const net_uv::HttpRequest& request, net_uv::HttpResponse* response);

private:

	std::string m_logRoot;
};
