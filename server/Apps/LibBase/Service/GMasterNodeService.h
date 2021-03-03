#pragma once

#include "GIService.h"
#include "GNoticeCenter.h"

namespace NSMsg{
	enum
	{
		MSG_BEGIN = 0,
		MSG_REG_SERVER_NODE_REQ,
		MSG_REG_SERVER_NODE_ACK,
		MSG_END
	};

	extern std::string MGS_KEY_REG_SLAVE_NODE;

	struct RegServerReq
	{
		int32_t groupID;
	};

	struct RegServerAck
	{
		int32_t code;
	};
}

/// 服务器同步-主节点服务
class GMasterNodeService final : public GIService
{
public:
	G_DEFINE_SERVICE(GMasterNodeService);

	virtual uint32_t onInit() override;

	virtual void onStartService() override;

	virtual void onStopService() override;

	virtual void onUpdate(float) override;

	virtual void onDestroy() override;

	G_FORCEINLINE GNoticeCenter* noticeCenter();

	G_FORCEINLINE const std::vector<uint32_t>& arrSlaveNodeIds();

	void sendToMsg(uint32_t slaveNodeID, uint32_t msgID, char* data, uint32_t len);

protected:

	void onNewConnectCallback(net_uv::Server* svr, net_uv::Session* session);

	void onRecvCallback(net_uv::Server* svr, net_uv::Session* session, char* data, uint32_t len);

	void onDisconnectCallback(net_uv::Server* svr, net_uv::Session* session);

	void onRecvMsg(uint32_t sessionID, uint32_t msgID, char* data, uint32_t len);

private:

	std::unique_ptr<net_uv::Server> m_svr;
	std::unique_ptr<net_uv::NetMsgMgr> m_msgMgr;
	std::unique_ptr<GNoticeCenter>     m_noticeCenter;
	int32_t m_groupID;
	std::vector<uint32_t>			   m_arrSlaveNodeIds;
};

GNoticeCenter* GMasterNodeService::noticeCenter()
{
	return m_noticeCenter.get();
}

const std::vector<uint32_t>& GMasterNodeService::arrSlaveNodeIds()
{
	return m_arrSlaveNodeIds;
}
