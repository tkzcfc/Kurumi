#include "ServiceGate.h"
#include "pb/Msg_ID.pb.h"
#include "pb/Msg_Game.pb.h"

// 网关服务


ServiceGate::ServiceGate()
{}

ServiceGate::~ServiceGate()
{}

uint32_t ServiceGate::onInit()
{
	auto cfgService = m_serviceMgr->getService<GConfigService>();
	if (cfgService == NULL)
		return SCODE_START_FAIL_EXIT_APP;

	auto& ini = cfgService->iniReader();
	auto appName = GApplication::getInstance()->getAppName();

	// 不需要此服务
	if (ini.GetBoolean(appName, "GateServiceEnable", false) == false)
		return SCODE_START_FAIL_NO_ERR;

	auto ip = ini.Get(appName, "GateServiceIP", "");
	auto port = ini.GetInteger(appName, "GateServicePort", 0);
	auto isKcp = ini.GetBoolean(appName, "GateServiceIsKcp", false);

	if (ip.empty() || port <= 0)
		return SCODE_START_FAIL_EXIT_APP;

	// 判断 GNetService 服务是否存在
	m_pNetService = m_serviceMgr->getService<GNetService>();
	if (m_pNetService == NULL)
		return SCODE_START_FAIL_EXIT_APP;
	
	m_ip = ip;
	m_port = port;

	if (isKcp)
		m_client = std::make_unique<net_uv::KCPClient>();
	else
		m_client = std::make_unique<net_uv::TCPClient>();

	m_client->setConnectCallback(std::bind(&ServiceGate::onConnectCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	m_client->setDisconnectCallback(std::bind(&ServiceGate::onDisconnectCall, this, std::placeholders::_1, std::placeholders::_2));
	m_client->setRecvCallback(std::bind(&ServiceGate::onRecvCall, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_client->setClientCloseCallback(std::bind(&ServiceGate::onCloseCall, this, std::placeholders::_1));
	m_client->setRemoveSessionCallback(std::bind(&ServiceGate::onRemoveSessionCall, this, std::placeholders::_1, std::placeholders::_2));

	m_msgMgr = std::make_unique<net_uv::NetMsgMgr>();
	m_msgMgr->setUserData(this);
	m_msgMgr->setSendCallback([](net_uv::NetMsgMgr* mgr, uint32_t sessionID, char* data, uint32_t len)
	{
		auto ins = reinterpret_cast<ServiceGate*>(mgr->getUserData());
		ins->m_client->send(sessionID, data, len);
	});
	m_msgMgr->setCloseSctCallback([](net_uv::NetMsgMgr* mgr, uint32_t sessionID)
	{
		auto ins = reinterpret_cast<ServiceGate*>(mgr->getUserData());
		ins->m_client->disconnect(sessionID);
	});
	m_msgMgr->setOnMsgCallback([](net_uv::NetMsgMgr* mgr, uint32_t sessionID, uint32_t msgID, char* data, uint32_t len)
	{
		auto ins = reinterpret_cast<ServiceGate*>(mgr->getUserData());
		ins->onRecvMsg(sessionID, msgID, data, len);
	});
	m_msgMgr->setHeartBeatTime(2);
	m_msgMgr->setHeartBeatLoseMaxCount(3);

	// 转发GNetService服务接收的数据
	m_pNetService->setRecvMsgCallback([=](uint32_t sessionID, uint32_t msgID, char* data, uint32_t len)
	{
		m_msgMgr->sendMsg(sessionID, msgID, data, len);
	});
	m_pNetService->noticeCenter()->addListener(this, GNetService::MSG_KEY_NEW_CONNECT, [=](uint32_t sessionID)
	{
		m_client->connect(m_ip.c_str(), m_port, sessionID);
	});
	m_pNetService->noticeCenter()->addListener(this, GNetService::MSG_KEY_DISCONNECT, [=](uint32_t sessionID)
	{
		m_client->disconnect(sessionID);
	});


	return SCODE_START_SUCCESS;
}

void ServiceGate::onStartService()
{}

void ServiceGate::onStopService()
{}

void ServiceGate::onUpdate(float)
{}

void ServiceGate::onDestroy()
{}

void ServiceGate::onConnectCallback(net_uv::Client* client, net_uv::Session* session, int32_t status)
{
	// 0:failed 1:succeeded 2:timed out
	if (status == 1)
	{
		LoginGateAck ack;
		ack.set_code(0);
		SEND_PB_MSG(m_msgMgr, session->getSessionID(), MessageID::MSG_LOGIN_GATE_ACK, ack);
	}
	else
	{
		LoginGateAck ack;
		ack.set_code(1);
		SEND_PB_MSG(m_msgMgr, session->getSessionID(), MessageID::MSG_LOGIN_GATE_ACK, ack);

		m_client->disconnect(session->getSessionID());
	}
}

void ServiceGate::onDisconnectCall(net_uv::Client* client, net_uv::Session* session)
{
	m_msgMgr->onDisconnect(session->getSessionID());
	m_client->removeSession(session->getSessionID());
	m_pNetService->disconnect(session->getSessionID());
}

void ServiceGate::onRecvCall(net_uv::Client* client, net_uv::Session* session, char* data, uint32_t len)
{
	m_msgMgr->onBuff(session->getSessionID(), data, len);
}

void ServiceGate::onCloseCall(net_uv::Client* client)
{}

void ServiceGate::onRemoveSessionCall(net_uv::Client* client, net_uv::Session* session)
{}

void ServiceGate::onRecvMsg(uint32_t sessionID, uint32_t msgID, char* data, uint32_t len)
{
	m_pNetService->sendToMsg(sessionID, msgID, data, len);
}