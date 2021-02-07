#include "DaoStateMachine.h"
#include "ecs/utils/ArmatureUtils.h"
#include "ecs/components/SIMPhysComponent.h"
#include "ecs/components/PropertyComponent.h"
#include "ecs/system/SIMPhysSystem.h"


// 使用json初始化动画状态机
bool DaoStateMachine::initWithJson(const std::string& content)
{
	if (!Super::initWithJson(content))
		return false;


	return true;
}

// 状态进入
void DaoStateMachine::onStateEnter(GAnimatorState* state)
{
	Super::onStateEnter(state);
}

// 状态停留
void DaoStateMachine::onStateStay(GAnimatorState* state)
{
	Super::onStateStay(state);
}

// 状态退出
void DaoStateMachine::onStateExit(GAnimatorState* state)
{
	Super::onStateExit(state);
}

