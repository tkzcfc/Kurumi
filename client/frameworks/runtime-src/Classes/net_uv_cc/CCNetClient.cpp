#include "CCNetClient.h"

CCNetClient* CCNetClient::create(bool useKcp)
{
	CCNetClient* client = new CCNetClient(useKcp);
	client->autorelease();
	return client;
}

CCNetClient::CCNetClient(bool useKcp)
{
	//////////////////////////////////////////////////////////////////////////
	if (useKcp)
		m_client = std::make_unique<net_uv::KCPClient>();
	else
		m_client = std::make_unique<net_uv::TCPClient>();

	m_client->setClientCloseCallback([=](net_uv::Client* client)
	{
		auto pHandle = this->getLuaHandle("onClientCloseCallback");
		if (pHandle && pHandle->isvalid())
		{
			pHandle->ppush();
			pHandle->pcall();
		}
	});

	m_client->setConnectCallback([=](net_uv::Client* client, net_uv::Session* session, int32_t status)
	{
		auto pHandle = this->getLuaHandle("onConnectCallback");
		if (pHandle && pHandle->isvalid())
		{
			pHandle->ppush();
			pHandle->pushusertype<net_uv::Session>(session, "net_uv::Session");
			pHandle->pusharg(status);
			pHandle->pcall();
		}
		if (status == 1)
		{
			m_msgMgr->onConnect(session->getSessionID());
		}
	});

	m_client->setDisconnectCallback([=](net_uv::Client* client, net_uv::Session* session)
	{
		auto pHandle = this->getLuaHandle("onDisconnectCallback");
		if (pHandle && pHandle->isvalid())
		{
			pHandle->ppush();
			pHandle->pushusertype<net_uv::Session>(session, "net_uv::Session");
			pHandle->pcall();
		}
		m_msgMgr->onDisconnect(session->getSessionID());
	});

	m_client->setRecvCallback([=](net_uv::Client* client, net_uv::Session* session, char* data, uint32_t len)
	{
		m_msgMgr->onBuff(session->getSessionID(), data, len);
	});
	m_client->setRemoveSessionCallback([=](net_uv::Client* client, net_uv::Session* session)
	{
		auto pHandle = this->getLuaHandle("onRemoveSessionCallback");
		if (pHandle && pHandle->isvalid())
		{
			pHandle->ppush();
			pHandle->pushusertype<net_uv::Session>(session, "net_uv::Session");
			pHandle->pcall();
		}
	});

	//////////////////////////////////////////////////////////////////////////
	///
	m_msgMgr = std::make_unique<net_uv::NetMsgMgr>();
	m_msgMgr->setUserData(this);
	m_msgMgr->setSendCallback([](net_uv::NetMsgMgr* mgr, uint32_t sessionID, char* data, uint32_t len) 
	{
		auto self = reinterpret_cast<CCNetClient*>(mgr->getUserData());
		self->m_client->send(sessionID, data, len);
	});

	m_msgMgr->setOnMsgCallback([](net_uv::NetMsgMgr* mgr, uint32_t sessionID, uint32_t msgID, char* data, uint32_t len)
	{
		auto self = reinterpret_cast<CCNetClient*>(mgr->getUserData());
		auto pHandle = self->getLuaHandle("onMsgCallback");
		if (pHandle && pHandle->isvalid())
		{
			pHandle->ppush();
			pHandle->pusharg(sessionID);
			pHandle->pusharg(msgID);
			pHandle->pushlstring(data, len);
			pHandle->pcall();
		}
	});

	m_msgMgr->setCloseSctCallback([](net_uv::NetMsgMgr* mgr, uint32_t sessionID)
	{
		auto self = reinterpret_cast<CCNetClient*>(mgr->getUserData());
		self->m_client->disconnect(sessionID);
	});

	Director::getInstance()->getScheduler()->schedule(schedule_selector(CCNetClient::update), this, 0.0f, false);
}

CCNetClient::~CCNetClient()
{
	Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
}

void CCNetClient::connect(const char* ip, uint32_t port, uint32_t sessionId)
{
	m_client->connect(ip, port, sessionId);
}

void CCNetClient::removeSession(uint32_t sessionId)
{
	m_client->removeSession(sessionId);
}

void CCNetClient::disconnect(uint32_t sessionId)
{
	m_client->disconnect(sessionId);
}

void CCNetClient::sendMsg(uint32_t sessionID, uint32_t msgID, char* data, uint32_t len)
{
	m_msgMgr->sendMsg(sessionID, msgID, data, len);
}

void CCNetClient::setHeartBeatTime(uint32_t value)
{
	m_msgMgr->setHeartBeatTime(value);
}

void CCNetClient::setHeartBeatLoseMaxCount(uint32_t value)
{
	m_msgMgr->setHeartBeatLoseMaxCount(value);
}

void CCNetClient::update(float)
{
	m_client->updateFrame();
	m_msgMgr->updateFrame();
}

void CCNetClient::closeClient()
{
	m_client->closeClient();
}
