#include "PlayerStateMachine.h"
#include "ecs/utils/ArmatureUtils.h"


void PlayerStateMachine::init(const anax::Entity& entity)
{
	m_entity = entity;
	m_entity.getComponent<ArmatureComponent>().onFinishCall = [=]()
	{
		this->onAnimFinished();
	};
}

// 播放动画接口
void PlayerStateMachine::playAnimation(const std::string& animName, bool loop)
{
	ArmatureUtils::playAnimationCMD(m_entity, animName, loop ? kArmaturePlayMode::LOOP : kArmaturePlayMode::DEFAULT);
}

// 缩放动画播放速率
void PlayerStateMachine::scaleTime(float scale)
{
	m_entity.getComponent<ArmatureComponent>().timeScale = scale;
}

