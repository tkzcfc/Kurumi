#include "GLibBase.h"
#include "GLoginService.h"
#include "GAccountMgrService.h"

int main(int argc, char** argv)
{
	GApplication app(argc, argv);
	app.getServiceMgr()->addService<GConfigService>();
	app.getServiceMgr()->addService<GLocalStorageService>();
	app.getServiceMgr()->addService<GMasterNodeService>();
	app.getServiceMgr()->addService<GHttpService>();
	app.getServiceMgr()->addService<GAccountMgrService>();
	app.getServiceMgr()->addService<GLoginService>();
	return app.run();
}
