#include "GMasterNodeService.h"


bool GMasterNodeService::onInit()
{
	m_svr = std::make_unique<net_uv::TCPServer>();
	return true;
}

void GMasterNodeService::onStartService()
{}

void GMasterNodeService::onStopService()
{
	m_svr->stopServer();
}

void GMasterNodeService::onUpdate(float)
{
	switch (this->m_status)
	{
	case GServiceStatus::RUNNING:
	{}break;
	case GServiceStatus::STOP_ING:
	{
		if (m_svr == NULL || m_svr->isCloseFinish())
			m_status = GServiceStatus::STOP;
	}break;
	default:
		break;
	}
}

void GMasterNodeService::onDestroy()
{}

