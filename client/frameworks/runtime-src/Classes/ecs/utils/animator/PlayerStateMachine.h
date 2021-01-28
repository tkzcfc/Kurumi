#pragma once

#include "foundation/fsm/GAnimatorStateMachine.h"
#include "ecs/anaxHelper.h"

class PlayerStateMachine : public GAnimatorStateMachine
{
public:

	void init(const anax::Entity& entity);
	
	// 播放动画接口
	virtual void playAnimation(const std::string& animName, bool loop)override;

	// 缩放动画播放速率
	virtual void scaleTime(float scale)override;

protected:
	anax::Entity m_entity;
};
