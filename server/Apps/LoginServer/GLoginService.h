#pragma once

#include "GLibBase.h"
#include "GameProto.h"
#include "Algorithm/GRandom.h"

// 登录服务
class GLoginService : public GIService
{
public:

	G_DEFINE_SERVICE(GLoginService);

	virtual uint32_t onInit() override;

	virtual void onStopService() override;

public:

	err::Code checkToken(const std::string& playerId, const std::string token);

private:

	void init_Http();

	void init_MasterNode();

	void clearInvalidToken();

protected:
	
	void onHttpRequest_Login(const net_uv::HttpRequest& request, net_uv::HttpResponse* response);

	void onHttpRequest_Register(const net_uv::HttpRequest& request, net_uv::HttpResponse* response);

	void onHttpRequest_ServerList(const net_uv::HttpRequest& request, net_uv::HttpResponse* response);

	void onMsg_CheckTokenReq(uint32_t sessionID, const svr_msg::CheckTokenReq& msg);

private:

	struct TokenInfo
	{
		std::string token;
		uint32_t time;
	};
	std::map<std::string, TokenInfo> m_tokenMap;

	GMasterNodeService* m_pMasterNodeService;

	std::unique_ptr<GRandom> m_random;
};
