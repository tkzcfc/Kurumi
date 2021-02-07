#include "GLibBase.h"
#include "ServiceFight.h"
#include "foundation/fsm/GAnimatorStateMachine.h"

static bool isChange = false;
class TestStateMachine : public GAnimatorStateMachine
{
public:
	// 状态进入
	void onStateEnter(GAnimatorState* state)
	{
		GAnimatorStateMachine::onStateEnter(state);
	}

	void onStateStay(GAnimatorState* state)
	{
		if (state->getStateName() == "StateC")
		{
			params().setFloat("fValue", params().getFloat("fValue") + fsm().getFrameTime());
			params().setInteger("iValue", params().getInteger("iValue") + 1);
			//printf("fvalue %f\n", params().getFloat("fValue"));
		}

		if (state->getFSM()->getCurStateStayTime() > 2.0f)
		{
			if (state->getStateName() == "StateB")
			{
				if (!isChange)
				{
					params().setTrigger("trigger", 1);
					isChange = true;
				}
			}
			this->onAnimFinished();
		}
	}

	// 状态退出
	void onStateExit(GAnimatorState* state)
	{
		GAnimatorStateMachine::onStateExit(state);
	}

	// 播放动画接口
	void playAnimation(const std::string& animName, bool loop) 
	{
		LOG(INFO) << "playAnimation : " << animName << ", loop" << loop;
	}

	// 缩放动画播放速率
	void scaleTime(float scale) 
	{

	}
};


class GAnimatorStateB : public GAnimatorState
{
public:

	GAnimatorStateB(GAnimatorStateMachine* machine, const FStateKeyType& name)
		: GAnimatorState(machine, name)
	{}

	virtual void onEnter()
	{
		GAnimatorState::onEnter();
		LOG(INFO) << "GAnimatorStateB --------------- > onEnter";
	}
};



INITIALIZE_EASYLOGGINGPP;

extern void initLog();

const char* tobool(bool value)
{
	return value ? "true" : "false";
}

int main(int argc, char** argv)
{
	initLog();

	LOG(INFO) << "-----------application run-----------";
	GApplication app("FightServer");

	TestStateMachine* machine = new TestStateMachine();
	machine->registerStateGenLogic("StateB", [](GAnimatorStateMachine* machine, const FStateKeyType& name) -> GAnimatorState*
	{
		return new GAnimatorStateB(machine, name);
	});
	machine->initWithJson(GFileSystem::readStringFromFile("runtimeData.json"));

	app.getScheduler()->scheduleSelector([=](float dt) 
	{
		machine->update(dt);
	}, 0.0f, false, "update");

	app.getServiceMgr()->addService<ServiceFight>();

	app.run();
	LOG(INFO) << "-----------application exit-----------";

	return EXIT_SUCCESS;
}

void initLog()
{
	el::Configurations conf;
	conf.setGlobally(el::ConfigurationType::Format, "%datetime{%M-%d %H:%m:%s} [%level] %msg");
	conf.setGlobally(el::ConfigurationType::Enabled, "true");
	conf.setGlobally(el::ConfigurationType::ToFile, "true");
	conf.setGlobally(el::ConfigurationType::Filename, "log_fight\\log_%datetime{%Y%M%d}.log");
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
