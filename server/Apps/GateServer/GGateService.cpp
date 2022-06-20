#include "GGateService.h"

// 网关服务


GGateService::GGateService()
{}

GGateService::~GGateService()
{}

uint32_t GGateService::onInit()
{
	G_CHECK_SERVICE(GConfigService);

	auto& ini = m_serviceMgr->getService<GConfigService>()->iniReader();
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
	G_CHECK_SERVICE(GNetService);

	m_pNetService = m_serviceMgr->getService<GNetService>();	
	m_ip = ip;
	m_port = port;

	if (isKcp)
		m_client = std::make_unique<net_uv::KCPClient>();
	else
		m_client = std::make_unique<net_uv::TCPClient>();

	m_client->setConnectCallback(std::bind(&GGateService::onConnectCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	m_client->setDisconnectCallback(std::bind(&GGateService::onDisconnectCall, this, std::placeholders::_1, std::placeholders::_2));
	m_client->setRecvCallback(std::bind(&GGateService::onRecvCall, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_client->setClientCloseCallback(std::bind(&GGateService::onCloseCall, this, std::placeholders::_1));
	m_client->setRemoveSessionCallback(std::bind(&GGateService::onRemoveSessionCall, this, std::placeholders::_1, std::placeholders::_2));

	m_msgMgr = std::make_unique<net_uv::NetMsgMgr>();
	m_msgMgr->setUserData(this);
	m_msgMgr->setSendCallback([](net_uv::NetMsgMgr* mgr, uint32_t sessionID, char* data, uint32_t len)
	{
		auto ins = reinterpret_cast<GGateService*>(mgr->getUserData());
		ins->m_client->send(sessionID, data, len);
	});
	m_msgMgr->setCloseSctCallback([](net_uv::NetMsgMgr* mgr, uint32_t sessionID)
	{
		auto ins = reinterpret_cast<GGateService*>(mgr->getUserData());
		ins->m_client->disconnect(sessionID);
	});
	m_msgMgr->setOnMsgCallback([](net_uv::NetMsgMgr* mgr, uint32_t sessionID, uint32_t msgID, char* data, uint32_t len)
	{
		auto ins = reinterpret_cast<GGateService*>(mgr->getUserData());
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
		LOG(INFO) << "gate new connect:" << sessionID;
		m_msgMgr->onConnect(sessionID);
		m_client->connect(m_ip.c_str(), m_port, sessionID);
	});
	m_pNetService->noticeCenter()->addListener(this, GNetService::MSG_KEY_DISCONNECT, [=](uint32_t sessionID)
	{
		m_msgMgr->onDisconnect(sessionID);
		m_client->disconnect(sessionID);
	});


	return SCODE_START_SUCCESS;
}

void GGateService::onUpdate(float)
{
	m_client->updateFrame();
	m_msgMgr->updateFrame();
}

void GGateService::onConnectCallback(net_uv::Client* client, net_uv::Session* session, int32_t status)
{
	LOG(INFO) << "connect to:" << m_ip << ", status:" << status << ", session: " << session->getSessionID();
	// 0:failed 1:succeeded 2:timed out
	if (status == 1)
	{
		msg::LoginGateAck ack;
		ack.set_code(err::Code::SUCCESS);

		std::string data;
		if (ack.SerializeToString(&data))
		{
			printf("%s", data.c_str());
		}

		SEND_PB_MSG(m_pNetService, session->getSessionID(), ack);
	}
	else
	{
		msg::LoginGateAck ack;
		ack.set_code(err::Code::GATE_CONNECT_FAIL);
		SEND_PB_MSG(m_pNetService, session->getSessionID(), ack);

		m_client->disconnect(session->getSessionID());
	}
}

void GGateService::onDisconnectCall(net_uv::Client* client, net_uv::Session* session)
{
	m_msgMgr->onDisconnect(session->getSessionID());
	m_client->removeSession(session->getSessionID());
	m_pNetService->disconnect(session->getSessionID());
}

void GGateService::onRecvCall(net_uv::Client* client, net_uv::Session* session, char* data, uint32_t len)
{
	m_msgMgr->onBuff(session->getSessionID(), data, len);
}

void GGateService::onCloseCall(net_uv::Client* client)
{}

void GGateService::onRemoveSessionCall(net_uv::Client* client, net_uv::Session* session)
{}

void GGateService::onRecvMsg(uint32_t sessionID, uint32_t msgID, char* data, uint32_t len)
{
	m_pNetService->sendMsg(sessionID, msgID, data, len);
}