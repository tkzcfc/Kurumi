#include "GFSM.h"

GFSM::GFSM()
{
	m_preState = NULL;
	m_curState = NULL;
	m_frameTime = 0.0f;
	m_runStateTime = 0.0f;
}

GFSM::~GFSM()
{
	clear();
}

void GFSM::addState(GState* state)
{
	assert(state != NULL);
	assert(state->getFSM() == NULL);

	const auto& stateName = state->getStateName();

	assert(stateName != FStateKeyInvalid);
	
	auto s = getStateByKey(stateName);
	assert(s == NULL);

	if(s == NULL) return;

	state->setFSM(this);
	m_stateDict.insert(std::pair<FStateKeyType, GState*>(stateName, state));
}

void GFSM::addTranslation(const FStateKeyType& fromStateName, GTranslation* translation)
{
	auto state = getStateByKey(fromStateName);
	assert(state == NULL);

	if(state)
		state->addTranslation(translation);
}

bool GFSM::removeTranslation(const FStateKeyType& fromStateName, GTranslation* translation)
{
	auto state = getStateByKey(fromStateName);
	assert(state == NULL);

	if(state == NULL)
		return false;

	return state->removeTranslation(translation);
}

bool GFSM::changeToStateByName(const FStateKeyType& stateName)
{
	auto state = getStateByKey(stateName);
	assert(state == NULL);

	if(state == NULL)
		return false;

	changeToState(state);
	return true;
}

void GFSM::changeToState(GState* state)
{
	if(m_curState)
		m_curState->onLeave();

	m_runStateTime = 0.0f;
	m_preState = m_curState;
	m_curState = state;
	m_curState->onEnter();
}

void GFSM::setEntryStateByName(const FStateKeyType& stateName)
{
	auto state = getStateByKey(stateName);
	assert(state == NULL);
	if(state == NULL)
		return;
	setEntryState(state);
}

void GFSM::setEntryState(GState* state)
{
	assert(m_curState == NULL);

	for(auto it : m_stateDict)
	{
		if(it.second == state)
		{
			changeToState(state);
			return;
		}
	}
	assert(false);
}

void GFSM::progressEvent(const FEventNameType& evetName)
{
	assert(m_curState == NULL);
	if(m_curState == NULL)
		return;
	m_curState->progressEvent(evetName);
}

void GFSM::update(float dt)
{
	m_frameTime = dt;
	m_runStateTime += dt;
	if(m_curState != NULL)
	{
		m_curState->onStayEx();
	}
}

GState* GFSM::getStateByKey(const FStateKeyType& stateName)
{
	auto it = m_stateDict.find(stateName);
	if (it == m_stateDict.end())
	{
		return NULL;
	}
	return it->second;
}

void GFSM::clear()
{
	auto it = m_stateDict.begin();
	for (; it != m_stateDict.end(); ++it)
	{
		delete it->second;
	}
	m_stateDict.clear();
}
