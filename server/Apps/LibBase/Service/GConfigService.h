#pragma once

#include "GIService.h"
#include "GINIReader.h"

/// ≈‰÷√∑˛ŒÒ
class GConfigService final : public GIService
{
public:

	G_DEFINE_SERVICE(GConfigService);

	virtual uint32_t onInit() override;

	virtual void onStartService() override;

	virtual void onStopService() override;

	virtual void onUpdate(float) override;

	virtual void onDestroy() override;

	GINIReader& iniReader()
	{
		return *m_reader;
	}

private:
	std::unique_ptr<GINIReader> m_reader;
};
