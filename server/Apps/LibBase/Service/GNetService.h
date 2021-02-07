#pragma once

#include "GIService.h"

/// ÍøÂç·þÎñ
class GNetService : public GIService
{
public:

	GNetService();

	virtual ~GNetService();

	G_DEFINE_SERVICE(GNetService);

	virtual bool onInit() override;

	virtual void onStartService() override;

	virtual void onStopService() override;

	virtual void onUpdate(float) override;

	virtual void onDestroy() override;
};
