#pragma once

#include "GTranslation.h"
#include <vector>

class GFSM;
class GState
{
public:
	GState(const FStateKeyType& stateName);

	virtual ~GState();

	virtual void onEnter(){}

	virtual void onExit(){}

	virtual void onStay() {}

public:

	inline const FStateKeyType& getStateName();

	inline GFSM* getFSM();

	void addTranslation(GTranslation* translation);

	bool removeTranslation(GTranslation* translation);

	bool changeToState(const FStateKeyType& toStateName);

protected:

	virtual void onEnterEx() {}

	virtual void onExitEx() {}

	void onStayEx();

	void setFSM(GFSM* fsm);

	void progressEvent(const FEventNameType& evetName);

	void clear();

protected:
	friend class GFSM;
	GFSM* m_fsm;
	FStateKeyType m_stateName;
	std::vector<GTranslation*> m_translationArr;
};

GFSM* GState::getFSM()
{ 
	return m_fsm;
}

const FStateKeyType& GState::getStateName()
{
	return m_stateName;
}
