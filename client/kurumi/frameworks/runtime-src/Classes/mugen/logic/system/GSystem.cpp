#include "GSystem.h"
#include "mugen/base/GEntityManager.h"

NS_G_BEGIN

GSystem::GSystem()
{
}

GSystem::~GSystem()
{}

void GSystem::doFilter(const char* componentName)
{
	GEntityManager::getInstance()->getAllComponent(componentName, m_cacheComponents);
}

NS_G_END
