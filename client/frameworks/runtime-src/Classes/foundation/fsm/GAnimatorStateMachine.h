#pragma once

#include <memory>
#include "GFSM.h"
#include "GAnimatorState.h"
#include "GAnimatorParams.h"
#include "GAnimatorTranslation.h"

/// 动画状态机
class GAnimatorStateMachine
{
public:
	GAnimatorStateMachine();

	virtual ~GAnimatorStateMachine();

public:

	// 状态进入
	virtual void onStateEnter(GAnimatorState* state);

	// 状态停留
	virtual void onStateStay(GAnimatorState* state);

	// 状态退出
	virtual void onStateExit(GAnimatorState* state);

	// 播放动画接口
	virtual void playAnimation(const std::string& animName, bool loop) {}

	// 缩放动画播放速率
	virtual void scaleTime(float scale) {}

public:

	bool initWithJson(const std::string& content);

	void update(float dt);

	void onAnimFinished();

	void resetAnimComplete();

	inline GAnimatorParams& params() const;

	inline GFSM& fsm() const;

	inline bool isAnimComplete() const;

	inline GAnimatorState* getCompleteState() const;

private:
	std::unique_ptr<GAnimatorParams> m_params;
	std::unique_ptr<GFSM> m_fsm;
	GAnimatorState* m_anyState;
	GAnimatorState* m_animCompleteState;
	bool m_animComplete;
};

GAnimatorParams& GAnimatorStateMachine::params() const
{
	return *m_params;
}

GFSM& GAnimatorStateMachine::fsm() const
{
	return *m_fsm;
}

bool GAnimatorStateMachine::isAnimComplete() const
{
	return m_animComplete;
}

GAnimatorState* GAnimatorStateMachine::getCompleteState() const
{
	return m_animCompleteState;
}