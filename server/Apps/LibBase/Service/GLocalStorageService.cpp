#include "GLocalStorageService.h"
#include "GConfigService.h"
#include "GServiceMgr.h"
#include "GApplication.h"
#include "GMasterNodeService.h"
#include "Utils/GStringUtils.h"


uint32_t GLocalStorageService::onInit()
{
	G_CHECK_SERVICE(GConfigService);

	auto cfgService = m_serviceMgr->getService<GConfigService>();
	auto& ini = cfgService->iniReader();
	auto appName = GApplication::getInstance()->getAppName();

	// 不需要此服务
	if (ini.GetBoolean(appName, "LocalStorageEnable", false) == false)
		return SCODE_START_FAIL_NO_ERR;

	auto dbName = ini.Get(appName, "LocalStorageDBName", "");
	if (dbName.empty())
	{
		LOG(ERROR) << "dbName is empty";
		return SCODE_START_FAIL_EXIT_APP;
	}

	m_csqliter = std::make_unique<csqliter>();

	if (m_csqliter->openexistingdb(dbName) != dbresulttype::successdb)
	{
		auto code = m_csqliter->createdb(dbName);
		if (code != dbresulttype::successdb)
		{
			LOG(ERROR) << ("createdb '") << dbName << "' fail, error code:" << int32_t(code);
			return SCODE_START_FAIL_EXIT_APP;
		}
	}

	return SCODE_START_SUCCESS;
}

void GLocalStorageService::onStopService()
{
	m_csqliter->closedb();
	this->stopServiceFinish();
}
