#pragma once

#include "GLibBase.h"
#include "GameProto.h"

// 网关服务
class GGateService final : public GIService
{
public:

	G_DEFINE_SERVICE(GGateService);

	GGateService();

	virtual ~GGateService();

	virtual uint32_t onInit() override;

	virtual void onUpdate(float) override;

protected:

	void onConnectCallback(net_uv::Client* client, net_uv::Session* session, int32_t status);

	void onDisconnectCall(net_uv::Client* client, net_uv::Session* session);

	void onRecvCall(net_uv::Client* client, net_uv::Session* session, char* data, uint32_t len);

	void onCloseCall(net_uv::Client* client);

	void onRemoveSessionCall(net_uv::Client* client, net_uv::Session* session);

	void onRecvMsg(uint32_t sessionID, uint32_t msgID, char* data, uint32_t len);

private:

	std::unique_ptr<net_uv::Client>	   m_client;
	std::unique_ptr<net_uv::NetMsgMgr> m_msgMgr;
	std::string m_ip;
	uint32_t m_port;
	GNetService* m_pNetService;
};

