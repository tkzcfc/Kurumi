#pragma once

#include "GIService.h"
#include "GNoticeCenter.h"
#include "GTypes.h"

/// 网络服务
class GNetService final : public GIService
{
public:

	static std::string MSG_KEY_NEW_CONNECT;
	static std::string MSG_KEY_DISCONNECT;

public:

	GNetService();

	virtual ~GNetService();

	G_DEFINE_SERVICE(GNetService);

	virtual uint32_t onInit() override;

	virtual void onStartService() override;

	virtual void onStopService() override;

	virtual void onUpdate(float) override;

	virtual void onDestroy() override;

public:

	G_SYNTHESIZE_READONLY(GNetType, m_netType, NetType);

public:

	void sendMsg(uint32_t sessionID, uint32_t msgID, char* data, uint32_t len);

	void disconnect(uint32_t sessionID);

	G_FORCEINLINE void setRecvMsgCallback(const std::function<void(uint32_t, uint32_t, char*, uint32_t)>& call);

	G_FORCEINLINE GNoticeCenter* noticeCenter();

protected:

	void onNewConnectCallback(net_uv::Server* svr, net_uv::Session* session);

	void onRecvCallback(net_uv::Server* svr, net_uv::Session* session, char* data, uint32_t len);

	void onDisconnectCallback(net_uv::Server* svr, net_uv::Session* session);

	void onRecvMsg(uint32_t sessionID, uint32_t msgID, char* data, uint32_t len);

private:

	std::unique_ptr<net_uv::Server>	   m_svr;
	std::unique_ptr<net_uv::NetMsgMgr> m_msgMgr;
	std::unique_ptr<GNoticeCenter>     m_noticeCenter;

	std::function<void(uint32_t, uint32_t, char*, uint32_t)> m_recvCall;
};

GNoticeCenter* GNetService::noticeCenter()
{
	return m_noticeCenter.get();
}

void GNetService::setRecvMsgCallback(const std::function<void(uint32_t, uint32_t, char*, uint32_t)>& call)
{
	m_recvCall = call;
}

