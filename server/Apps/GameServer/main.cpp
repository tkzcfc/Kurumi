#include "GLibBase.h"
#include "GPlayerMngService.h"
#include "GLoginService.h"
#include "GRoleMngService.h"
#include "GFightService.h"

int main(int argc, char** argv)
{
	GApplication app(argc, argv);
	app.getServiceMgr()->addService<GConfigService>();
	app.getServiceMgr()->addService<GSlaveNodeService>();
	app.getServiceMgr()->addService<GMasterNodeService>();
	app.getServiceMgr()->addService<GNetService>();
	app.getServiceMgr()->addService<GLocalStorageService>();
	app.getServiceMgr()->addService<GRoleMngService>();
	app.getServiceMgr()->addService<GPlayerMngService>();
	app.getServiceMgr()->addService<GLoginService>();
	app.getServiceMgr()->addService<GFightService>();
	return app.run();
}
