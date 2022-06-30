#include "GMasterNodeService.h"
#include "GApplication.h"
#include "GConfigService.h"
#include "Utils/GStringUtils.h"

namespace NSMsg {
	std::string MGS_KEY_REG_SLAVE_NODE = "MGS_KEY_REG_SLAVE_NODE";
}

GMasterNodeService::GMasterNodeService()
	: m_netType(GNetType::UNKNOWN)
	, m_groupID(-1)
{}

GMasterNodeService::~GMasterNodeService()
{}

uint32_t GMasterNodeService::onInit()
{
	G_CHECK_SERVICE(GConfigService);

	auto cfgService = m_serviceMgr->getService<GConfigService>();
	auto& ini = cfgService->iniReader();
	auto appName = GApplication::getInstance()->getAppName();

	//! 不需要此服务
	if (ini.GetBoolean(appName, "MasterNodeEnable", false) == false)
	{
		return SCODE_START_FAIL_NO_ERR;
	}

	auto ip = ini.Get(appName, "MasterNodeIP", "");
	auto port = ini.GetInteger(appName, "MasterNodePort", 0);
	auto group = ini.GetInteger(appName, "MasterNodeGroup", 0);
	auto isKcp = ini.GetBoolean(appName, "MasterNodeIsKcp", false);

	if (ip.empty() || port <= 0)
		return SCODE_START_FAIL_EXIT_APP;

	m_groupID = group;
	m_netType = isKcp ? GNetType::KCP : GNetType::TCP;

	if(isKcp)
		m_svr = std::make_unique<net_uv::KCPServer>();
	else
		m_svr = std::make_unique<net_uv::TCPServer>();

	m_svr->setNewConnectCallback(std::bind(&GMasterNodeService::onNewConnectCallback, this, std::placeholders::_1, std::placeholders::_2));
	m_svr->setRecvCallback(std::bind(&GMasterNodeService::onRecvCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_svr->setDisconnectCallback(std::bind(&GMasterNodeService::onDisconnectCallback, this, std::placeholders::_1, std::placeholders::_2));
	m_svr->setCloseCallback([](net_uv::Server*) {});

	if (false == m_svr->startServer(ip.c_str(), port, false, 0xffff))
		return SCODE_START_FAIL_EXIT_APP;

	m_msgMgr = std::make_unique<net_uv::NetMsgMgr>();
	m_msgMgr->setUserData(this);
	m_msgMgr->setSendCallback([](net_uv::NetMsgMgr* mgr, uint32_t sessionID, char* data, uint32_t len)
	{
		auto ins = reinterpret_cast<GMasterNodeService*>(mgr->getUserData());
		ins->m_svr->send(sessionID, data, len);
	});
	m_msgMgr->setCloseSctCallback([](net_uv::NetMsgMgr* mgr, uint32_t sessionID) 
	{
		auto ins = reinterpret_cast<GMasterNodeService*>(mgr->getUserData());
		ins->m_svr->disconnect(sessionID);
	});
	m_msgMgr->setOnMsgCallback([](net_uv::NetMsgMgr* mgr, uint32_t sessionID, uint32_t msgID, char* data, uint32_t len)
	{
		auto ins = reinterpret_cast<GMasterNodeService*>(mgr->getUserData());
		ins->onRecvMsg(sessionID, msgID, data, len);
	});
	m_msgMgr->setHeartBeatTime(3);
	m_msgMgr->setHeartBeatLoseMaxCount(3);

	m_noticeCenter = std::make_unique<GNoticeCenter>();

	return SCODE_START_SUCCESS;
}

void GMasterNodeService::onStartService()
{}

void GMasterNodeService::onStopService()
{
	m_svr->stopServer();
}

void GMasterNodeService::onUpdate(float)
{
	m_svr->updateFrame();
	m_msgMgr->updateFrame();
	switch (this->m_status)
	{
	case GServiceStatus::RUNNING:
	{}break;
	case GServiceStatus::STOP_ING:
	{
		if (m_svr->isCloseFinish())
		{
			stopServiceFinish();
		}
	}break;
	default:
		break;
	}
}

void GMasterNodeService::onDestroy()
{}

void GMasterNodeService::sendMsg(uint32_t slaveNodeID, uint32_t msgID, char* data, uint32_t len)
{
	m_msgMgr->sendMsg(slaveNodeID, msgID, data, len);
}

void GMasterNodeService::onNewConnectCallback(net_uv::Server* svr, net_uv::Session* session)
{
	m_msgMgr->onConnect(session->getSessionID());
}

void GMasterNodeService::onRecvCallback(net_uv::Server* svr, net_uv::Session* session, char* data, uint32_t len)
{
	m_msgMgr->onBuff(session->getSessionID(), data, len);
}

void GMasterNodeService::onDisconnectCallback(net_uv::Server* svr, net_uv::Session* session)
{
	m_msgMgr->onDisconnect(session->getSessionID());

	for (auto it = m_arrSlaveNodInfos.begin(); it != m_arrSlaveNodInfos.end();)
	{
		if (it->sessionID == session->getSessionID())
		{
			LOG(INFO) << "SlaveNode[" << session->getSessionID() << "] off-line, GroupID: " << m_groupID;
			it = m_arrSlaveNodInfos.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void GMasterNodeService::onRecvMsg(uint32_t sessionID, uint32_t msgID, char* data, uint32_t len)
{
	switch (msgID)
	{
	case NSMsg::MSG_REG_SERVER_NODE_REQ:
	{
		auto msg = reinterpret_cast<NSMsg::RegServerReq*>(data);
		if (msg->groupID == m_groupID)
		{
			NSMsg::RegServerAck ack;
			ack.code = 0;
			m_msgMgr->sendMsg(sessionID, NSMsg::MSG_REG_SERVER_NODE_ACK, (char*)&ack, sizeof(ack));

			bool find = false;
			for (auto& it : m_arrSlaveNodInfos)
			{
				if (it.sessionID == sessionID)
				{
					find = true;
					G_ASSERT(false);
				}
			}

			if (!find)
			{
				LOG(INFO) << "SlaveNode[" << sessionID << "] Login successful, GroupID: " << msg->groupID;
				
				m_arrSlaveNodInfos.push_back(SlaveNodeInfo());


				auto& node = m_arrSlaveNodInfos.back();
				node.sessionID = sessionID;
				node.info.assign(data + sizeof(NSMsg::RegServerReq), msg->infoLen);

				rapidjson::StringStream stream(node.info.c_str());
				node.infoJson.ParseStream<0>(stream);
				if (node.infoJson.HasParseError())
				{
					LOG(ERROR) << "[GMasterNodeService] json parse error : " << node.infoJson.GetParseError();
					G_ASSERT(0);
				}

				m_noticeCenter->emitEvent(NSMsg::MGS_KEY_REG_SLAVE_NODE, sessionID);
			}
		}
		else
		{
			NSMsg::RegServerAck ack;
			ack.code = 1;
			m_msgMgr->sendMsg(sessionID, NSMsg::MSG_REG_SERVER_NODE_ACK, (char*)&ack, sizeof(ack));
			m_svr->disconnect(sessionID);
			LOG(INFO) << "SlaveNode[" << sessionID << "] Login failed, GroupID: " << msg->groupID;
		}
	}break;
	default:
		for (auto& it : m_arrSlaveNodInfos)
		{
			if (it.sessionID == sessionID)
			{
				m_noticeCenter->emitEvent(StringUtils::msgKey(msgID), sessionID, data, len);
				return;
			}
		}
		m_svr->disconnect(sessionID);
		LOG(ERROR) << "Invalid message ID received, msgID: " << msgID;
		break;
	}
}

SlaveNodeInfo* GMasterNodeService::getSlaveNodeInfo(uint32_t slaveNodeID)
{
	for (auto & it : m_arrSlaveNodInfos)
	{
		if (it.sessionID == slaveNodeID)
			return &it;
	}
	return NULL;
}
