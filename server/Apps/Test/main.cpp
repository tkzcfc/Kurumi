#include "GLibBase.h"

INITIALIZE_EASYLOGGINGPP;

class ServiceA : public GIService
{
public:
	ServiceA(const char* name, int32_t age)
	{
		LOG(INFO) << "ServiceA name = " << name << "age = " << age;
	}

	G_DEFINE_SERVICE(ServiceA);


	uint32_t onInit()
	{
		GApplication::getInstance()->getScheduler()->scheduleGlobalOnce([](float dt) {
			LOG(INFO) << "scheduleGlobalOnce time:" << dt;
		}, 2.0f, "xx");

		m_time = 0.0f;
		return SCODE_START_SUCCESS;
	}

	void onStartService()
	{
		LOG(INFO) << "onStartService";
	}

	void onStopService()
	{
		LOG(INFO) << "onStopService : " << m_time;
	}

	void onUpdate(float dt)
	{
		//switch (this->m_status)
		//{
		//case GServiceStatus::RUNNING:
		//{}break;
		//case GServiceStatus::STOP_ING:
		//{
		//	//printf("m_time:%f\n", m_time);
		//	m_time += dt;
		//	if (m_time > 5.0f)
		//	{
		//		LOG(INFO) << "stop finish--->" << m_time;
		//		m_status = GServiceStatus::STOP;
		//	}
		//}break;
		//default:
		//	break;
		//}
	}

	void onDestroy()
	{
		LOG(INFO) << "onDestroy";
	}
	float m_time;
};


int main(int argc, char** argv)
{
	//el::Configurations conf;
	//conf.setGlobally(el::ConfigurationType::Format, "%datetime{%M-%d %H:%m:%s} [%level] %msg");
	//conf.setGlobally(el::ConfigurationType::Enabled, "true");
	//conf.setGlobally(el::ConfigurationType::ToFile, "true");
	//conf.setGlobally(el::ConfigurationType::Filename, "log_test\\log_%datetime{%Y%M%d}.log");
	//conf.setGlobally(el::ConfigurationType::MillisecondsWidth, "3");
	//// 10MB
	//conf.setGlobally(el::ConfigurationType::MaxLogFileSize, "10485760");
	//// 选择划分级别的日志	
	//el::Loggers::addFlag(el::LoggingFlag::HierarchicalLogging);
	//// 设置级别门阀值，修改参数可以控制日志输出
	//el::Loggers::setLoggingLevel(el::Level::Error);
	//// 重新设置配置  
	//el::Loggers::reconfigureAllLoggers(conf);
	//
	//LOG(INFO) << "-----------application run-----------";

	//// (const duSchedulerFunc& callback, float interval, unsigned int repeat, float delay, bool paused, const std::string& key, bool infinite = false);
	//GScheduler::getInstance()->scheduleSelector([](float) 
	//{
	//	GApplication::getInstance()->end();
	//}, 3.0f, 1, 0.0f, false, "end");

	//GApplication app("Test");

	//auto serviceMgr = app.getServiceMgr();
	//serviceMgr->addService<ServiceA>("NameArg", 100);

	//app.run();
	
	//LOG(INFO) << "-----------application exit-----------";
	system("pause");
	return EXIT_SUCCESS;
}
