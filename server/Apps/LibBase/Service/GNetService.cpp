#include "GNetService.h"

GNetService::GNetService()
{}

GNetService::~GNetService()
{}

bool GNetService::onInit()
{
	return true;
}

void GNetService::onStartService()
{}

void GNetService::onStopService()
{
	m_status = GServiceStatus::STOP;
}

void GNetService::onUpdate(float)
{}

void GNetService::onDestroy()
{}

