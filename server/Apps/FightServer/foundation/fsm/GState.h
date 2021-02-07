#pragma once

#include "GTranslation.h"
#include <vector>

/// 状态代理
class GStateDelegate
{
public:

	GStateDelegate() {}

	virtual ~GStateDelegate() {};

	virtual void onEnter(GState* state) = 0;

	virtual void onExit(GState* state) = 0;

	virtual void onStay(GState* state) = 0;
};

class GFSM;
class GState
{
public:

	GState() = delete;

	GState(const FStateKeyType& stateName);

	virtual ~GState();

	virtual void onEnter(){}

	virtual void onExit(){}

	virtual void onStay(){}

public:

	// 获取状态名称
	inline const FStateKeyType& getStateName() const;

	// 获取有限状态机
	inline GFSM* getFSM() const;

	// 添加状态转换通道,传入指针由状态机管理释放内存
	void addTranslation(GTranslation* translation);

	// 移除状态转换通道
	bool removeTranslation(GTranslation* translation);

	// 状态切换
	bool changeToState(const FStateKeyType& toStateName);

	// 代理设置
	void setDelegate(GStateDelegate* delegate);

	inline GStateDelegate* getDelegate() const;

	inline int getTranslationCount() const;

	inline GTranslation* getTranslationByIndex(int index) const;

	inline const std::vector<GTranslation*>& getTranslation() const;

protected:

	void onEnterEx();

	void onExitEx();

	void onStayEx();

	void setFSM(GFSM* fsm);

	void progressEvent(const FEventNameType& evetName);

	void clear();

protected:
	friend class GFSM;
	GFSM* m_fsm;
	FStateKeyType m_stateName;
	std::vector<GTranslation*> m_translationArr;
	GStateDelegate* m_delegate;
};

GFSM* GState::getFSM() const
{ 
	return m_fsm;
}

const FStateKeyType& GState::getStateName() const
{
	return m_stateName;
}

GStateDelegate* GState::getDelegate() const
{
	return m_delegate;
}

int GState::getTranslationCount() const
{
	return (int)m_translationArr.size();
}

GTranslation* GState::getTranslationByIndex(int index) const
{
	return m_translationArr[index];
}

const std::vector<GTranslation*>& GState::getTranslation() const
{
	return m_translationArr;
}
