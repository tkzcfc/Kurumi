#pragma once

#include "GIService.h"
#include "GINIReader.h"

/// 配置服务
class GConfigService final : public GIService
{
public:

	G_DEFINE_SERVICE(GConfigService);

	virtual uint32_t onInit() override;

	GINIReader& iniReader()
	{
		return *m_reader;
	}

private:
	std::unique_ptr<GINIReader> m_reader;
};
