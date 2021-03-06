#include "GNetService.h"
#include "GServiceMgr.h"
#include "GConfigService.h"
#include "GApplication.h"
#include "GStringUtils.h"

std::string GNetService::MSG_KEY_NEW_CONNECT = "new_connect";
std::string GNetService::MSG_KEY_DISCONNECT = "disc";

GNetService::GNetService()
{}

GNetService::~GNetService()
{}

uint32_t GNetService::onInit()
{
	m_recvCall = NULL;

	auto cfgService = m_serviceMgr->getService<GConfigService>();
	if (cfgService == NULL)
		return SCODE_START_FAIL_EXIT_APP;

	auto& ini = cfgService->iniReader();
	auto appName = GApplication::getInstance()->getAppName();

	//! 不需要此服务
	if (ini.GetBoolean(appName, "NetServiceEnable", false) == true)
	{
		return SCODE_START_FAIL_NO_ERR;
	}

	auto ip		= ini.Get(appName, "NetServiceIP", "");
	auto port	= ini.GetInteger(appName, "NetServicePort", 0);
	auto isKcp = ini.GetBoolean(appName, "NetServiceIsKcp", false);

	if (ip.empty() || port <= 0)
		return SCODE_START_FAIL_EXIT_APP;
	
	if(isKcp)
		m_svr = std::make_unique<net_uv::KCPServer>();
	else
		m_svr = std::make_unique<net_uv::TCPServer>();

	m_svr->setNewConnectCallback(std::bind(&GNetService::onNewConnectCallback, this, std::placeholders::_1, std::placeholders::_2));
	m_svr->setRecvCallback(std::bind(&GNetService::onRecvCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_svr->setDisconnectCallback(std::bind(&GNetService::onDisconnectCallback, this, std::placeholders::_1, std::placeholders::_2));
	m_svr->setCloseCallback([](net_uv::Server*) {});

	if (false == m_svr->startServer(ip.c_str(), port, false, 0xffff))
		return SCODE_START_FAIL_EXIT_APP;

	m_msgMgr = std::make_unique<net_uv::NetMsgMgr>();
	m_msgMgr->setUserData(this);
	m_msgMgr->setSendCallback([](net_uv::NetMsgMgr* mgr, uint32_t sessionID, char* data, uint32_t len)
	{
		auto ins = reinterpret_cast<GNetService*>(mgr->getUserData());
		ins->m_svr->send(sessionID, data, len);
	});
	m_msgMgr->setCloseSctCallback([](net_uv::NetMsgMgr* mgr, uint32_t sessionID)
	{
		auto ins = reinterpret_cast<GNetService*>(mgr->getUserData());
		ins->m_svr->disconnect(sessionID);
	});
	m_msgMgr->setOnMsgCallback([](net_uv::NetMsgMgr* mgr, uint32_t sessionID, uint32_t msgID, char* data, uint32_t len)
	{
		auto ins = reinterpret_cast<GNetService*>(mgr->getUserData());
		if (ins->m_recvCall)
			ins->m_recvCall(sessionID, msgID, data, len);
		else
			ins->onRecvMsg(sessionID, msgID, data, len);
	});
	m_msgMgr->setHeartBeatTime(3);
	m_msgMgr->setHeartBeatLoseMaxCount(3);

	m_noticeCenter = std::make_unique<GNoticeCenter>();

	return SCODE_START_SUCCESS;
}

void GNetService::onStartService()
{}

void GNetService::onStopService()
{
	m_svr->stopServer();
}

void GNetService::onUpdate(float)
{
	m_svr->updateFrame();
	m_msgMgr->updateFrame();
	switch (this->m_status)
	{
	case GServiceStatus::STOP_ING:
	{
		if (m_svr->isCloseFinish())
			m_status = GServiceStatus::STOP;
	}break;
	default:
		break;
	}
}

void GNetService::onDestroy()
{}

void GNetService::sendMsg(uint32_t sessionID, uint32_t msgID, char* data, uint32_t len)
{
	m_msgMgr->sendMsg(sessionID, msgID, data, len);
}

void GNetService::disconnect(uint32_t sessionID)
{
	m_svr->disconnect(sessionID);
}

void GNetService::onNewConnectCallback(net_uv::Server* svr, net_uv::Session* session)
{
	m_msgMgr->onConnect(session->getSessionID());
	m_noticeCenter->emitEvent(MSG_KEY_NEW_CONNECT, session->getSessionID());
}

void GNetService::onRecvCallback(net_uv::Server* svr, net_uv::Session* session, char* data, uint32_t len)
{
	m_msgMgr->onBuff(session->getSessionID(), data, len);
}

void GNetService::onDisconnectCallback(net_uv::Server* svr, net_uv::Session* session)
{
	m_msgMgr->onDisconnect(session->getSessionID());
	m_noticeCenter->emitEvent(MSG_KEY_DISCONNECT, session->getSessionID());
}

void GNetService::onRecvMsg(uint32_t sessionID, uint32_t msgID, char* data, uint32_t len)
{
	m_noticeCenter->emitEvent(StringUtils::msgKey(msgID), sessionID, data, len);
}
