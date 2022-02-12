#pragma once

#include "mugen/base/GEntity.h"

NS_G_BEGIN

class GSystem
{
public:

	GSystem();

	~GSystem();

	void doFilter(const char* componentName);

protected:

	std::vector<GComponent*> m_cacheComponents;
};

NS_G_END
