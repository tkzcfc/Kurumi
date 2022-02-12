#include "GLibBase.h"
#include "GPlayerMngService.h"
#include "GLoginService.h"
#include "GRoleMngService.h"
#include "GFightService.h"

INITIALIZE_EASYLOGGINGPP;

extern void initLog(const char* logName);

int main(int argc, char** argv)
{
	auto params = cmd::get_cmd_params(argc, argv);
	auto argName = cmd::try_get(params, "name", "GameServer");

	// init log
	initLog(argName.c_str());
	
	LOG(INFO) << "-----------application run-----------";

	GApplication app(argName);
	app.getServiceMgr()->addService<GConfigService>();
	app.getServiceMgr()->addService<GSlaveNodeService>();
	app.getServiceMgr()->addService<GMasterNodeService>();
	app.getServiceMgr()->addService<GNetService>();
	app.getServiceMgr()->addService<GLocalStorageService>();
	app.getServiceMgr()->addService<GRoleMngService>();
	app.getServiceMgr()->addService<GPlayerMngService>();
	app.getServiceMgr()->addService<GLoginService>();
	app.getServiceMgr()->addService<GFightService>();
	app.run();

	LOG(INFO) << "-----------application exit-----------";
	
	return EXIT_SUCCESS;
}

void initLog(const char* logName)
{
	auto logDir = StringUtils::format("log\\%s\\", logName);

	el::Configurations conf;
	conf.setGlobally(el::ConfigurationType::Format, "%datetime{%M-%d %H:%m:%s} [%level] %msg");
	conf.setGlobally(el::ConfigurationType::Enabled, "true");
	conf.setGlobally(el::ConfigurationType::ToFile, "true");
	conf.setGlobally(el::ConfigurationType::Filename, logDir + "log_%datetime{%Y%M%d}.log");
	conf.setGlobally(el::ConfigurationType::MillisecondsWidth, "3");
	// 10MB
	conf.setGlobally(el::ConfigurationType::MaxLogFileSize, "10485760");
	// 选择划分级别的日志	
	el::Loggers::addFlag(el::LoggingFlag::HierarchicalLogging);
	// 设置级别门阀值，修改参数可以控制日志输出
	el::Loggers::setLoggingLevel(el::Level::Error);
	// 重新设置配置  
	el::Loggers::reconfigureAllLoggers(conf);
}