#include "GState.h"
#include "GFSM.h"


GState::GState(const FStateKeyType& stateName)
{
	m_stateName = stateName;
	m_fsm = NULL;
}

GState::~GState()
{
	clear();
}

void GState::setFSM(GFSM* fsm)
{ 
	m_fsm = fsm; 
}

void GState::progressEvent(const FEventNameType& evetName)
{
	if(m_translationArr.empty())
		return;
	
	for(auto it : m_translationArr)
	{
		if(it->progressEvent(this, evetName) && this->changeToState(it->getToState()))
		{				
			return;
		}
	}
}

void GState::addTranslation(GTranslation* translation)
{
	m_translationArr.push_back(translation);
}

bool GState::removeTranslation(GTranslation* translation)
{
	for(auto it = m_translationArr.begin(); it != m_translationArr.end(); ++it)
	{
		if(*it == translation)
		{
			delete translation;
			m_translationArr.erase(it);
			return true;
		}
	}
	return false;
}

void GState::clear()
{
	for(auto& it : m_translationArr)
	{
		delete it;
	}
	m_translationArr.clear();
}

bool GState::changeToState(const FStateKeyType& toStateName)
{
	return m_fsm->changeToStateByName(toStateName);
}

void GState::onStayEx() 
{
	if(m_translationArr.empty())
	{
		onStay();
	}
	else
	{		
		for(auto it : m_translationArr)
		{
			if(it->polling(this) && this->changeToState(it->getToState()))
			{				
				return;
			}
		}
		onStay();
	}	
}
