#pragma once

#include "foundation/fsm/GAnimatorStateMachine.h"
#include "ecs/anaxHelper.h"
#include "GAniStateDef.h"

class GActorStateMachine : public GAnimatorStateMachine
{
	typedef GAnimatorStateMachine Super;
public:
	
	virtual void init(const anax::Entity& entity);

	// 使用json初始化动画状态机
	virtual bool initWithJson(const std::string& content) override;
	
	// 播放动画接口
	virtual void playAnimation(const std::string& animName, bool loop)override;

	// 缩放动画播放速率
	virtual void scaleTime(float scale)override;

	// 外部调用更新
	virtual void update(float dt)override;

	// 动画播放完毕回调
	//! 需要外部手动调用,状态机内部不知道动画何时完成
	virtual void onAnimFinished() override;

	// 状态进入
	virtual void onStateEnter(GAnimatorState* state) override;

	// 状态停留
	virtual void onStateStay(GAnimatorState* state) override;

	// 状态退出
	virtual void onStateExit(GAnimatorState* state) override;

	G_FORCEINLINE anax::Entity& entity();
	
protected:
	anax::Entity m_entity;


	//! 是否处于战斗状态
	int m_hash_isFight;
	//! 是否处于空中
	int m_hash_isInAir;
	//! 是否死亡
	int m_hash_isDeath;
	//! 当前状态是否可以打断
	int m_hash_canBreak;
	// 是否处于跳跃状态
	int m_hash_isJump;
	// 是否在处于移动状态
	int m_hash_isRun;


	//! 是否要切换到被受击状态
	int m_hash_toHit;
	//! 是否要切换到站立状态
	int m_hash_toStand;
	//! 是否要切换到下落状态
	int m_hash_toJumpDown;

	anim::GANI_STATE_TYPE m_curStateType;
};

anax::Entity& GActorStateMachine::entity()
{
	return m_entity;
}
