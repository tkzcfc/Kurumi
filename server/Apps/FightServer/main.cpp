#include "GLibBase.h"
#include "GFightService.h"

int main(int argc, char** argv)
{
	GEnableHighPrecisionTimer enableHighPrecisionTimer(1);

	GApplication app(argc, argv);
	app.getServiceMgr()->addService<GConfigService>();
	app.getServiceMgr()->addService<GSlaveNodeService>();
	app.getServiceMgr()->addService<GMasterNodeService>();
	app.getServiceMgr()->addService<GNetService>();
	app.getServiceMgr()->addService<GFightService>();
	return app.run(1);
}
