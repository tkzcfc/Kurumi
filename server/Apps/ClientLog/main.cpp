#include "GLibBase.h"
#include "GLogService.h"

int main(int argc, char** argv)
{
	GApplication app(argc, argv);
	app.getServiceMgr()->addService<GConfigService>();
	app.getServiceMgr()->addService<GHttpService>();
	app.getServiceMgr()->addService<GLogService>();
	return app.run();
}

