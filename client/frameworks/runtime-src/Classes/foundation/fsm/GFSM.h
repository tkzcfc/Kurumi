#pragma once

#include "GState.h"
#include <unordered_map>

// 有限状态机
class GFSM
{
public:
	GFSM();

	virtual ~GFSM();

	void addState(GState* state);

	void addTranslation(const FStateKeyType& fromStateName, GTranslation* translation);

	bool removeTranslation(const FStateKeyType& fromStateName, GTranslation* translation);

	bool changeToStateByName(const FStateKeyType& stateName);

	void setEntryStateByName(const FStateKeyType& stateName);

	void setEntryState(GState* state);

	void progressEvent(const FEventNameType& evetName);

	void update(float dt);

	GState* getStateByKey(const FStateKeyType& stateName);

public:

	inline GState* getPreState();

	inline const FStateKeyType& getPreStateName();

	inline GState* getCurState();

	inline const FStateKeyType& getCurStateName();

	inline float getFrameTime();

	inline float getCurStateStayTime();

protected:

	void changeToState(GState* state);

	void clear();

private:
	std::unordered_map<FStateKeyType, GState*> m_stateDict;
	GState* m_curState;
	GState* m_preState;
	float m_frameTime;
	float m_runStateTime;
};


GState* GFSM::getPreState()
{
	return m_preState;
}

const FStateKeyType& GFSM::getPreStateName()
{
	return (m_preState == NULL) ? FStateKeyInvalid : m_preState->m_stateName;
}

GState* GFSM::getCurState()
{
	return m_curState;
}

const FStateKeyType& GFSM::getCurStateName()
{
	return (m_curState == NULL) ? FStateKeyInvalid : m_curState->m_stateName;
}

float GFSM::getFrameTime()
{
	return m_frameTime;
}

float GFSM::getCurStateStayTime()
{
	return m_runStateTime;	
}

