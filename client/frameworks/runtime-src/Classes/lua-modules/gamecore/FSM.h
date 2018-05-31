#pragma once

#include <assert.h>
#include <string>
#include <functional>
#include <map>
#include "../LuaFunction.hpp"

//状态切换指令类型
typedef std::string EK;
//状态名称类型
typedef std::string SK;


class QFSMState;
class QFSMTranslation
{
public:
	QFSMTranslation(QFSMState* fromState, QFSMState* toState)
	{
		m_fromState = fromState;
		m_toState = toState;
	}

	QFSMState* m_fromState;
	QFSMState* m_toState;
};

class QFSM;
typedef std::function<void(QFSMState*, QFSM*)> CallbackFunc;


class QFSMState
{
public:
	QFSMState(SK stateName, const CallbackFunc& enterFunc, const CallbackFunc& leaveFunc)
	{
		m_stateName = stateName;
		m_enterFunc = enterFunc;
		m_leaveFunc = leaveFunc;
		m_fsm = NULL;
	}

	QFSMState(SK stateName, const LuaFunction& enterFunc, const LuaFunction& leaveFunc)
	{
		m_stateName = stateName;
		m_lua_enterFunc = enterFunc;
		m_lua_leaveFunc = leaveFunc;
		m_fsm = NULL;

		m_enterFunc = [=](QFSMState* state, QFSM* fsm)
		{			
			m_lua_enterFunc.ppush();
			m_lua_enterFunc.pushusertype(state, "QFSMState");
			m_lua_enterFunc.pushusertype(fsm, "QFSM");
			m_lua_enterFunc.pcall();
		};
		m_leaveFunc = [=](QFSMState* state, QFSM* fsm)
		{
			m_lua_leaveFunc.ppush();
			m_lua_leaveFunc.pushusertype(state, "QFSMState");
			m_lua_leaveFunc.pushusertype(fsm, "QFSM");
			m_lua_leaveFunc.pcall();
		};
	}

	virtual ~QFSMState()
	{
		clear();
	}

	SK getStateName()
	{
		return m_stateName;
	}

	inline QFSM* getFSM() { return m_fsm; }

protected:

	inline void setFSM(QFSM* fsm) { m_fsm = fsm; }

	bool addTranslation(EK eventName, QFSMState* toState)
	{
		auto it = m_translationDict.find(eventName);
		if (it == m_translationDict.end())
		{
			auto t = new QFSMTranslation(this, toState);
			m_translationDict.insert(std::pair<EK, QFSMTranslation*>(eventName, t));
			return true;
		}
		return false;
	}

	bool removeTranslation(EK eventName, QFSMState* toState)
	{
		auto it = m_translationDict.find(eventName);
		if (it != m_translationDict.end() && it->second->m_toState == toState)
		{
			delete it->second;
			m_translationDict.erase(it);
			return true;
		}
		return false;
	}

	QFSMState* handle(EK eventName)
	{
		auto it = m_translationDict.find(eventName);
		if (it != m_translationDict.end())
		{
			return it->second->m_toState;;
		}
		return NULL;
	}

	void clear()
	{
		auto it = m_translationDict.begin();
		for (; it != m_translationDict.end(); ++it)
		{
			delete it->second;
		}
		m_translationDict.clear();
	}

	void Enter()
	{
		if (m_enterFunc)
		{
			m_enterFunc(this, m_fsm);
		}
	}

	void Leave()
	{
		if (m_leaveFunc)
		{
			m_leaveFunc(this, m_fsm);
		}
	}

protected:
	friend class QFSM;
	SK m_stateName;
	CallbackFunc m_enterFunc;
	CallbackFunc m_leaveFunc;
	std::map<EK, QFSMTranslation*> m_translationDict;
	QFSM* m_fsm;

	LuaFunction m_lua_enterFunc;
	LuaFunction m_lua_leaveFunc;
};

class QFSM
{
	QFSMState* m_curState;
	std::map<SK, QFSMState*> m_stateDict;
	QFSMState* m_nextState;
	QFSMState* m_preState;
	EK m_curEventName;
public:
	QFSM()
	{
		m_nextState = NULL;
		m_preState = NULL;
		m_curState = NULL;
	}

	~QFSM()
	{
		clear();
	}

	bool addState(SK stateName, const CallbackFunc& enterFunc, const CallbackFunc& leaveFunc)
	{
		auto state = getStateByKey(stateName);
		if (state == NULL)
		{
			m_stateDict.insert(std::pair<SK, QFSMState*>(stateName, new QFSMState(stateName, enterFunc, leaveFunc)));
			return true;
		}
		return false;
	}

	bool addState(SK stateName, const LuaFunction& enterFunc, const LuaFunction& leaveFunc)
	{
		auto state = getStateByKey(stateName);
		if (state == NULL)
		{
			m_stateDict.insert(std::pair<SK, QFSMState*>(stateName, new QFSMState(stateName, enterFunc, leaveFunc)));
			return true;
		}
		return false;
	}

	bool addTranslation(SK fromStateName, EK eventName, SK toStateName)
	{
		auto fromState = getStateByKey(fromStateName);
		auto toState = getStateByKey(toStateName);
		if (fromState == NULL || toState == NULL)
		{
			return false;
		}
		return fromState->addTranslation(eventName, toState);
	}

	bool removeTranslation(SK fromStateName, EK eventName, SK toStateName)
	{
		auto fromState = getStateByKey(fromStateName);
		auto toState = getStateByKey(toStateName);
		if (fromState == NULL || toState == NULL)
		{
			return false;
		}
		return fromState->removeTranslation(eventName, toState);
	}

	void start(SK startStateName)
	{
		m_nextState = NULL;
		m_preState = NULL;

		m_curState = getStateByKey(startStateName);
		if (m_curState)
		{
			m_curState->Enter();
		}
		else
		{
			assert(0);
		}
	}

	bool handle(EK eventName)
	{
		if (m_curState == NULL)
		{
			return false;
		}
		auto toState = m_curState->handle(eventName);
		if (toState)
		{
			m_curEventName = eventName;

			m_nextState = toState;

			m_curState->Leave();

			m_preState = m_curState;
			m_nextState = NULL;
			toState->Enter();

			m_curState = toState;
			return true;
		}
		return false;
	}

	void clear()
	{
		auto it = m_stateDict.begin();
		for (; it != m_stateDict.end(); ++it)
		{
			it->second->clear();
			delete it->second;
		}
		m_stateDict.clear();
	}

	inline QFSMState* getPreState()
	{
		return m_preState;
	}

	inline QFSMState* getNextState()
	{
		return m_nextState;
	}

	inline QFSMState* getCurState()
	{
		return m_curState;
	}

	inline EK getCurEventName()
	{
		return m_curEventName;
	}

protected:

	QFSMState* getStateByKey(SK stateName)
	{
		auto it = m_stateDict.find(stateName);
		if (it == m_stateDict.end())
		{
			return NULL;
		}
		return it->second;
	}
};

