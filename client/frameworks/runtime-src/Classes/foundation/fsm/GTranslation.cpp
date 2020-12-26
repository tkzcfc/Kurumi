#include "GTranslation.h"
#include "GState.h"
#include "GFSM.h"


GTranslation::GTranslation()
{
	m_toState = FStateKeyInvalid;
	m_userData = NULL;
	m_eventName = FEventNameInvalid;
}

GTranslation::GTranslation(const FStateKeyType& toState)
{
	m_toState = toState;
	m_userData = NULL;
	m_eventName = FEventNameInvalid;
}

GTranslation::~GTranslation()
{}

bool GTranslation::polling(GState* curState)
{
	assert(m_toState != FStateKeyInvalid);
	return false;
}

bool GTranslation::progressEvent(GState* curState, const FEventNameType& evetName)
{
	return m_eventName == evetName;
}

void GTranslation::setToState(const FStateKeyType& toState)
{
	m_toState = toState;
}

const FStateKeyType& GTranslation::getToState()
{
	return m_toState;
}

void GTranslation::setUserData(void* userData)
{
	m_userData = userData;	
}

void* GTranslation::getUserData()
{
	return m_userData;	
}

void GTranslation::setEventName(const FEventNameType& eventName)
{
	m_eventName = eventName;
}

const FEventNameType& GTranslation::getEventName()
{
	return m_eventName;
}

//////////////////////////////////////////////////////////////////////////
/// GDelayTranslation

GDelayTranslation::GDelayTranslation(const FStateKeyType& toState, const float delayTime)
	: GTranslation(toState)
	, m_delayTime(delayTime)
{
}

bool GDelayTranslation::polling(GState* curState)
{
	return curState->getFSM()->getCurStateStayTime() >= m_delayTime;
}

