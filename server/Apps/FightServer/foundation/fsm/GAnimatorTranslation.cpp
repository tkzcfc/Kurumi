#include "GAnimatorTranslation.h"
#include "GAnimatorState.h"
#include "GAnimatorStateMachine.h"


GAnimatorTranslation::GAnimatorTranslation()
	: m_hasExitTime(false)
{}

GAnimatorTranslation::GAnimatorTranslation(const FStateKeyType& toState)
	: GTranslation(toState)
	, m_hasExitTime(false)
{}

bool GAnimatorTranslation::polling(GState* curState)
{
	assert(getToState() != FStateKeyInvalid);
	assert(getToState() != curState->getStateName());

	if (m_hasExitTime)
	{
		auto aniState = dynamic_cast<GAnimatorState*>(curState);
		assert(aniState != NULL);

		auto stateMachine = aniState->getStateMachine();

		if (!stateMachine->isAnimComplete() || stateMachine->getCompleteState() != aniState)
			return false;

		if (m_conditions.empty())
			return true;
	}	
	if (m_conditions.empty())
	{
		return false;
	}
	else
	{
		for (auto& it : m_conditions)
		{
			if (!it.check())
				return false;
		}
	}
	return true;
}

bool GAnimatorTranslation::progressEvent(GState* curState, const FEventNameType& evetName)
{
	return false;
}

void GAnimatorTranslation::addCondition(const GAnimatorCondition& condition)
{
	GAnimatorCondition temp;
	condition.clone(&temp);
	m_conditions.emplace_back(temp);
}

