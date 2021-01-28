#pragma once

#include "GState.h"
#include <unordered_map>

/// 有限状态机
class GFSM
{
public:
	GFSM();

	virtual ~GFSM();

	// 添加状态,传入指针由状态机管理释放内存
	void addState(GState* state);

	// 添加状态转换通道,传入指针由状态机管理释放内存
	void addTranslation(const FStateKeyType& fromStateName, GTranslation* translation);

	// 移除状态转换通道
	bool removeTranslation(const FStateKeyType& fromStateName, GTranslation* translation);

	// 通过状态名称切换到某个状态
	bool changeToStateByName(const FStateKeyType& stateName);

	// 设置默认状态
	void setEntryStateByName(const FStateKeyType& stateName);

	// 设置默认状态
	void setEntryState(GState* state);

	// 发射事件
	void progressEvent(const FEventNameType& evetName);

	// 逻辑更新
	void update(float dt);

	// 通过状态名称获取状态
	GState* getStateByKey(const FStateKeyType& stateName) const;

	// 设置anyState,传入指针由状态机管理释放内存
	void setAnyState(GState* state);

public:

	// 获取上一个状态
	inline GState* getPreState() const;

	// 获取上一个状态名称
	inline const FStateKeyType& getPreStateName() const;

	// 获取当前状态
	inline GState* getCurState() const;

	// 获取当前状态名称
	inline const FStateKeyType& getCurStateName() const;

	// 获取帧时间
	inline float getFrameTime() const;

	// 获取当前状态运行时长
	inline float getCurStateStayTime() const;

protected:

	// 切换到某个状态
	void changeToState(GState* state);

	// 状态机清理
	void clear();

private:
	std::unordered_map<FStateKeyType, GState*> m_stateDict;
	GState* m_curState;
	GState* m_preState;
	GState* m_anyState;
	float m_frameTime;
	float m_runStateTime;
};


GState* GFSM::getPreState() const
{
	return m_preState;
}

const FStateKeyType& GFSM::getPreStateName() const
{
	return (m_preState == NULL) ? FStateKeyInvalid : m_preState->m_stateName;
}

GState* GFSM::getCurState() const
{
	return m_curState;
}

const FStateKeyType& GFSM::getCurStateName() const
{
	return (m_curState == NULL) ? FStateKeyInvalid : m_curState->m_stateName;
}

float GFSM::getFrameTime() const
{
	return m_frameTime;
}

float GFSM::getCurStateStayTime() const
{
	return m_runStateTime;	
}

