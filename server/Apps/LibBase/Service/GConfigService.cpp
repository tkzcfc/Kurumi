#include "GConfigService.h"
#include "Utils/GStringUtils.h"
#include "GApplication.h"
#include "Utils/cmd.h"

uint32_t GConfigService::onInit()
{
	auto cfgFile = cmd::try_get("config", "cfg/config.ini");

	m_reader = std::make_unique<GINIReader>(cfgFile);
	auto err = m_reader->ParseError();
	if (err != 0)
	{
		LOG(ERROR) << "'" << cfgFile.c_str() << "' parse error code:" << err;
		return SCODE_START_FAIL_EXIT_APP;
	}

	std::string appName = GApplication::getInstance()->getAppName();

	auto it = std::find(m_reader->Sections().begin(), m_reader->Sections().end(), appName);
	if (it == m_reader->Sections().end())
	{
		LOG(ERROR) << "Section '" << appName.c_str() << "' not found in '" << cfgFile.c_str() << "'";
		return SCODE_START_FAIL_EXIT_APP;
	}
	return SCODE_START_SUCCESS;
}

