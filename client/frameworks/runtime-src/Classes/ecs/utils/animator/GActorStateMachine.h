#pragma once

#include "foundation/fsm/GAnimatorStateMachine.h"
#include "ecs/anaxHelper.h"
#include "GAniStateDef.h"



class GActorStateMachine : public GAnimatorStateMachine
{
	typedef GAnimatorStateMachine Super;
public:
	
	virtual void setEntity(const anax::Entity& entity);

	virtual void updateInput();


	// 按键按下
	void onKeyDown(G_BIT_TYPE key);

	// 按键抬起
	void onKeyUp(G_BIT_TYPE key);

	// 按键持续按下
	void onKeepPress(G_BIT_TYPE key);

public:

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
	anim::GANI_STATE_TYPE m_curStateType;
public:
	///! 参数hash
	//! 是否处于空中
	int HASH_IS_INAIR;
	//! 是否死亡
	int HASH_IS_DEATH;
	//! 当前状态是否可以打断
	int HASH_CAN_BREAK;
	// 是否处于跳跃状态
	int HASH_IS_JUMP;
	// 是否在处于移动状态
	int HASH_IS_RUN;

	//! 跳跃键按下后,此值置为true
	int HASH_KEY_DOWN_JUMP;

	//! 是否要切换到被受击状态
	int HASH_TO_HIT;
	//! 是否要切换到站立状态
	int HASH_TO_STAND;

	//! Y轴速度
	int HASH_Y_VELOCITY;
};

anax::Entity& GActorStateMachine::entity()
{
	return m_entity;
}
