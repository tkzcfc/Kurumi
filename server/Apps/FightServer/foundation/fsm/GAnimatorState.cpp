#include "GAnimatorState.h"
#include "GAnimatorStateMachine.h"


GAnimatorState::GAnimatorState(GAnimatorStateMachine* stateMachine, const FStateKeyType& stateName)
	: GState(stateName)
	, m_stateMachine(stateMachine)
	, m_loop(false)
	, m_motion(stateName)
	, m_speed(1.0f)
{
}

void GAnimatorState::onEnter()
{
	m_stateMachine->playAnimation(this->getMotion(), isLoop());
	m_stateMachine->resetAnimComplete();
	m_stateMachine->params().resetAllTrigger();
	m_stateMachine->onStateEnter(this);
}

void GAnimatorState::onExit()
{
	m_stateMachine->resetAnimComplete();
	m_stateMachine->params().resetAllTrigger();
	m_stateMachine->onStateExit(this);
}

void GAnimatorState::onStay()
{
	m_stateMachine->onStateStay(this);
}

