#pragma once

#include "ecs/utils/animator/GActorStateMachine.h"

class DaoStateMachine : public GActorStateMachine
{
	typedef GActorStateMachine Super;
public:

	// 使用json初始化动画状态机
	virtual bool initWithJson(const std::string& content) override;

	// 状态进入
	virtual void onStateEnter(GAnimatorState* state) override;

	// 状态停留
	virtual void onStateStay(GAnimatorState* state) override;

	// 状态退出
	virtual void onStateExit(GAnimatorState* state) override;


private:

};
