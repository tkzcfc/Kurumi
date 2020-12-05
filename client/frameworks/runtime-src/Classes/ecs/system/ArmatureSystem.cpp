#include "ArmatureSystem.h"
#include "foundation/animator/GAnimData.h"
#include "foundation/animator/GAnimCMD.h"

const static float32 ANI_FPS = 1 / 60.0f;

ArmatureSystem::ArmatureSystem()
{
	curTime = 0.0f;
}

ArmatureSystem::~ArmatureSystem()
{}

void ArmatureSystem::update(float32 delta)
{
	curTime += delta;
	while (curTime > ANI_FPS)
	{
		this->step();
		curTime -= ANI_FPS;
	}
}

void ArmatureSystem::step()
{
	const auto& entities = this->getEntities();
	for (auto it : entities)
	{
		stepAni(it.getComponent<ArmatureComponent>());
	}
}

void ArmatureSystem::stepAni(ArmatureComponent& component)
{
	if (false == component.playing)
		return;

	auto tmp = GAnimDataCache::getInstance()->getOrCreate(component.aniFile);
	if (tmp == NULL)
		return;

	auto aniData = tmp->getAniData(component.curAniName);
	if (aniData == NULL)
		return;

	this->runAction(component, aniData);
	component.curFrameIndex++;

	if (component.curFrameIndex >= aniData->duration)
	{
		auto cmd = GAnimCMDCache::getInstance()->getOrCreate(component.roleName);
		if (cmd == NULL)
		{
			// 循环动画
			if (aniData->isLoop)
			{
				component.curFrameIndex = 0;
			}
			else
			{
				// 只播放一次,播放完毕定格到最后一帧
				if (component.mode == kArmaturePlayMode::ONCE)
					component.playing = false;
				else// 循环播放则开始新一轮的播放
					component.curFrameIndex = 0;
			}
		}
		else
		{
			auto cmdData = cmd->get(component.curAniCMD);
			// 找不到对应的动作命令
			if (cmdData == NULL)
			{
				G_LOG_F("Play invalid animation command, '%s'", component.curAniCMD.c_str());
				G_ASSERT(false);
				component.curFrameIndex = 0;
				component.playing = false;
				return;
			}
			
			auto index = cmdData->seekIndex(component.curAniName);
			// 动作命令执行完毕
			if (index >= cmdData->actions.size())
			{
				if (component.mode == kArmaturePlayMode::ONCE)
				{
					if (aniData->isLoop)
						component.curFrameIndex = 0;
					else
						component.playing = false;
				}
				else
				{
					component.curFrameIndex = 0;
					component.curAniName = cmdData->actions[0];
				}
			}
			else
			{
				// 执行下一个动作
				component.curFrameIndex = 0;
				component.curAniName = cmdData->actions[index + 1];
				playAudio(cmdData->audios[index + 1]);
			}
		}
	}
}

void ArmatureSystem::runAction(ArmatureComponent& component, struct GAnimationData* aniData)
{
	// 事件触发
#if G_DEBUG
	auto event = aniData->events[component.curFrameIndex];
	if (event)
	{
		for (auto& it : event->names)
		{
			G_LOG_I("event %s", it.c_str());
		}
	}
#endif

	// 执行的第一帧并且是执行的动作命令则播放第一个动作的音效
	if (component.curFrameIndex == 0)
	{
		auto cmd = GAnimCMDCache::getInstance()->getOrCreate(component.roleName);
		if (cmd)
		{
			auto cmdData = cmd->get(component.curAniCMD);
			if (cmdData->seekIndex(component.curAniName) == 0)
			{
				playAudio(cmdData->audios[0]);
			}
		}
	}
}

void ArmatureSystem::playAudio(const std::string& audioName)
{

}

