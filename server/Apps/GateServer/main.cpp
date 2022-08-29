#include "GLibBase.h"
#include "GGateService.h"

int main(int argc, char** argv)
{
	GApplication app(argc, argv);
	app.getServiceMgr()->addService<GConfigService>();
	app.getServiceMgr()->addService<GSlaveNodeService>();
	app.getServiceMgr()->addService<GMasterNodeService>();
	app.getServiceMgr()->addService<GNetService>();
	app.getServiceMgr()->addService<GGateService>();
	return app.run();
}
