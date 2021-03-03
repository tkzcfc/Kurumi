#include "GConfigService.h"
#include "GStringUtils.h"
#include "GApplication.h"


uint32_t GConfigService::onInit()
{
	auto cfgFile = StringUtils::format("cfg/%s.ini", "config");

	m_reader = std::make_unique<GINIReader>(cfgFile);
	auto err = m_reader->ParseError();
	if (err != 0)
	{
		LOG(ERROR) << "'" << cfgFile.c_str() << "' parse error code:" << err;
		return SCODE_START_FAIL_EXIT_APP;
	}

	return SCODE_START_SUCCESS;
}

void GConfigService::onStartService()
{}

void GConfigService::onStopService()
{}

void GConfigService::onUpdate(float)
{}

void GConfigService::onDestroy()
{}

