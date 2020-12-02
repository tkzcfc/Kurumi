#pragma once

#include <assert.h>
#include <string>
#include <functional>
#include <map>
#include "lua_function/LuaFunction.h"

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
	QFSMState(const SK& stateName, const CallbackFunc& enterFunc, const CallbackFunc& leaveFunc)
	{
		m_stateName = stateName;
		m_enterFunc = enterFunc;
		m_leaveFunc = leaveFunc;
		m_fsm = NULL;
	}

	QFSMState(const SK& stateName, int enterFunc, int leaveFunc)
	{
		m_stateName = stateName;
		m_lua_enterFunc = enterFunc;
		m_lua_leaveFunc = leaveFunc;
		m_fsm = NULL;

		m_enterFunc = [this](QFSMState* state, QFSM* fsm)
		{			
			m_lua_enterFunc.ppush();
			m_lua_enterFunc.pushusertype<QFSMState>(state, "QFSMState");
			m_lua_enterFunc.pushusertype<QFSM>(fsm, "QFSM");
			m_lua_enterFunc.pcall();
		};
		m_leaveFunc = [this](QFSMState* state, QFSM* fsm)
		{
			m_lua_leaveFunc.ppush();
			m_lua_leaveFunc.pushusertype<QFSMState>(state, "QFSMState");
			m_lua_leaveFunc.pushusertype<QFSM>(fsm, "QFSM");
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

	bool addTranslation(const EK& eventName, QFSMState* toState)
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

	bool removeTranslation(const EK& eventName, QFSMState* toState)
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

	QFSMState* handle(const EK& eventName)
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

// 有限状态机
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

	// 添加状态
	bool addState(const SK& stateName, const CallbackFunc& enterFunc, const CallbackFunc& leaveFunc)
	{
		auto state = getStateByKey(stateName);
		if (state == NULL)
		{
			state = new QFSMState(stateName, enterFunc, leaveFunc);
			state->m_fsm = this;
			m_stateDict.insert(std::pair<SK, QFSMState*>(stateName, state));
			return true;
		}
		return false;
	}

	// 添加状态
	bool addState(const SK& stateName, int enterFunc, int leaveFunc)
	{
		auto state = getStateByKey(stateName);
		if (state == NULL)
		{
			state = new QFSMState(stateName, enterFunc, leaveFunc);
			state->m_fsm = this;
			m_stateDict.insert(std::pair<SK, QFSMState*>(stateName, state));
			return true;
		}
		return false;
	}

	// 添加状态切换指令
	bool addTranslation(const SK& fromStateName, const EK& eventName, const SK& toStateName)
	{
		auto fromState = getStateByKey(fromStateName);
		auto toState = getStateByKey(toStateName);
		if (fromState == NULL || toState == NULL)
		{
			return false;
		}
		return fromState->addTranslation(eventName, toState);
	}

	// 移除状态切换指令
	bool removeTranslation(const SK& fromStateName, const EK& eventName, const SK& toStateName)
	{
		auto fromState = getStateByKey(fromStateName);
		auto toState = getStateByKey(toStateName);
		if (fromState == NULL || toState == NULL)
		{
			return false;
		}
		return fromState->removeTranslation(eventName, toState);
	}

	// 状态机开始
	void start(const SK& startStateName)
	{
		m_nextState = NULL;
		m_preState = NULL;

		m_curState = getStateByKey(startStateName);
		assert(m_curState != NULL);
		if (m_curState)
		{
			m_curState->Enter();
		}
	}

	// 状态切换触发
	bool handle(const EK& eventName)
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

	// 强制切换到某个状态
	/// 注意清理！！！
	bool forceSwitch(const SK& startStateName)
	{
		assert(m_curState != NULL);

		auto toState = getStateByKey(startStateName);
		assert(toState != NULL);
		if (toState == NULL)
			return false;

		m_nextState = toState;

		m_curState->Leave();

		m_preState = m_curState;
		m_nextState = NULL;
		toState->Enter();

		m_curState = toState;
		return true;
	}

	// 获取上一个状态
	inline QFSMState* getPreState()
	{
		return m_preState;
	}

	// 获取上一个状态名
	inline SK getPreStateName()
	{
		return (m_preState == NULL) ? "" : m_preState->m_stateName;
	}

	// 获取下一个状态
	inline QFSMState* getNextState()
	{
		return m_nextState;
	}

	// 获取当前状态
	inline QFSMState* getCurState()
	{
		return m_curState;
	}

	// 获取当前状态名
	inline const SK& getCurStateName()
	{
		return m_curState->m_stateName;
	}

	// 获取当前事件
	inline EK getCurEventName()
	{
		return m_curEventName;
	}

protected:

	QFSMState* getStateByKey(const SK& stateName)
	{
		auto it = m_stateDict.find(stateName);
		if (it == m_stateDict.end())
		{
			return NULL;
		}
		return it->second;
	}
};

