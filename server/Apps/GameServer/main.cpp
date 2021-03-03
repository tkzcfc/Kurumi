#include "GLibBase.h"

INITIALIZE_EASYLOGGINGPP;

extern void initLog();

int main(int argc, char** argv)
{
	initLog();

	LOG(INFO) << "-----------application run-----------";
	
	GApplication app("GameServer");
	app.getServiceMgr()->addService<GConfigService>();
	app.getServiceMgr()->addService<GSlaveNodeService>();
	app.getServiceMgr()->addService<GMasterNodeService>();
	app.getServiceMgr()->addService<GNetService>();
	app.run();

	LOG(INFO) << "-----------application exit-----------";

	system("pause");

	return EXIT_SUCCESS;
}

void initLog()
{
	el::Configurations conf;
	conf.setGlobally(el::ConfigurationType::Format, "%datetime{%M-%d %H:%m:%s} [%level] %msg");
	conf.setGlobally(el::ConfigurationType::Enabled, "true");
	conf.setGlobally(el::ConfigurationType::ToFile, "true");
	conf.setGlobally(el::ConfigurationType::Filename, "log_game\\log_%datetime{%Y%M%d}.log");
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
