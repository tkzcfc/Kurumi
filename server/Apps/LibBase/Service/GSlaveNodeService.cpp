#include "GSlaveNodeService.h"



bool GSlaveNodeService::onInit()
{
	m_client = std::make_unique<net_uv::TCPClient>();
	return true;
}

void GSlaveNodeService::onStartService()
{}

void GSlaveNodeService::onStopService()
{
	m_client->closeClient();
}

void GSlaveNodeService::onUpdate(float)
{
	switch (this->m_status)
	{
	case GServiceStatus::RUNNING:
	{}break;
	case GServiceStatus::STOP_ING:
	{
		if (m_client == NULL || m_client->isCloseFinish())
			m_status = GServiceStatus::STOP;
	}break;
	default:
		break;
	}
}

void GSlaveNodeService::onDestroy()
{}

