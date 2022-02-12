#pragma once

#include "GIService.h"
#include "sqliter.h"

/// 本地化储存服务
class GLocalStorageService final : public GIService
{
public:
	G_DEFINE_SERVICE(GLocalStorageService);
	
	virtual uint32_t onInit() override;

	virtual void onStopService() override;

	G_FORCEINLINE csqliter* getsqliter();

private:
	std::unique_ptr<csqliter> m_csqliter;
};

csqliter* GLocalStorageService::getsqliter()
{
	return m_csqliter.get();
}

