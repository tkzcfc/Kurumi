#pragma once

#include "ecs/anaxHelper.h"
#include "foundation/animator/GAnimData.h"

enum class kArmaturePlayMode
{
	ONCE = 0,
	LOOP,
	DEFAULT
};

enum class kArmatureRenderAction
{
	NONE,
	PAUSE,		// 暂停
	PURSUE,		// 追赶逻辑渲染帧
	AWAIT,		// 等待逻辑渲染帧
	RUN,		// 正常执行
};


// 骨骼动画组件
class ArmatureComponent : public BaseComponent
{
public:
	ArmatureComponent() 
	{
		curFrameIndex = 0;
		cmdIndex = 0;
		cmdCount = 0;
		mode = kArmaturePlayMode::DEFAULT;
		playing = false;
		onFinishCall = NULL;
		curTime = 0.0f;
		timeScale = 1.0f;
	}
	// 当前帧
	uint32_t curFrameIndex;
	// 当前动作动画名
	std::string curAniName;
	// 动画文件,用于获取动画文件数据
	//std::string aniFile;
	// 当前动画命令
	std::string curAniCMD;
	// 角色名,用于获取动画命令
	std::string roleName;

	int32_t cmdIndex;
	int32_t cmdCount;

	kArmaturePlayMode mode;
	bool playing;

	std::function<void()> onFinishCall;

	float32 curTime;
	float32 timeScale;
};

// 骨骼动画渲染组件
class ArmatureRenderComponent : public BaseComponent
{
public:
	ArmatureRenderComponent()
	{
		actionType = kArmatureRenderAction::NONE;
		render = NULL;
	}

	cocostudio::Armature* render;
	kArmatureRenderAction actionType;
	std::string m_cacheRoleName;
};


