#pragma once

#include <memory>
#include <functional>
#include "GFSM.h"
#include "GAnimatorState.h"
#include "GAnimatorParams.h"
#include "GAnimatorTranslation.h"

class GAnimatorStateMachine;

//typedef GAnimatorState* (*GStateGenInterface)(GAnimatorStateMachine*, const FStateKeyType&);

// lambda
typedef std::function<GAnimatorState*(GAnimatorStateMachine*, const FStateKeyType&)> GStateGenInterface;


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

	// 动画播放完毕回调
	//! 需要外部手动调用,状态机内部不知道动画何时完成
	virtual void onAnimFinished();

public:

	// 使用json初始化动画状态机
	virtual bool initWithJson(const std::string& content);

	// 外部调用更新
	virtual void update(float dt);
	
	// 重置动画完毕标记
	virtual void resetAnimComplete();

	// 状态机参数
	inline GAnimatorParams& params() const;

	// 获取有限状态机
	inline GFSM& fsm() const;

	// 动画播放是否完成
	inline bool isAnimComplete() const;

	// 获取动画播放完成对应的状态
	inline GAnimatorState* getCompleteState() const;

	// 注册状态创建逻辑
	void registerStateGenLogic(const FStateKeyType& stateName, const GStateGenInterface& func);

private:

	GAnimatorState* newState(const FStateKeyType& stateName);

private:
	std::unique_ptr<GAnimatorParams> m_params;
	std::unique_ptr<GFSM> m_fsm;
	GAnimatorState* m_anyState;
	GAnimatorState* m_animCompleteState;
	bool m_animComplete;
	std::unordered_map<FStateKeyType, GStateGenInterface> m_stateFactory;
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