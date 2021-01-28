#pragma once

#include "GState.h"

class GAnimatorStateMachine;
/// 动画状态
class GAnimatorState : public GState
{
public:
	
	GAnimatorState(GAnimatorStateMachine* stateMachine, const FStateKeyType& stateName);

	virtual void onEnter() override;

	virtual void onExit() override;

	virtual void onStay() override;

	inline GAnimatorStateMachine* getStateMachine() const;

	inline void setLoop(bool loop);

	inline bool isLoop() const;

	inline void setMotion(const std::string& motion);

	inline const std::string& getMotion() const;

	inline void setSpeed(float speed);

	inline float getSpeed() const;

	inline void setMutiplier(const std::string& mutiplier);

	inline const std::string& getMutiplier() const;

private:
	GAnimatorStateMachine* m_stateMachine;
	// 是否循环播放
	bool m_loop;
	// 状态对应的动画
	std::string m_motion;
	// 动画速度
	float m_speed;
	// 动画最终速度 = speed * mutiplier
	std::string m_mutiplier;
};

GAnimatorStateMachine* GAnimatorState::getStateMachine() const
{
	assert(m_stateMachine != NULL);
	return m_stateMachine;
}

void GAnimatorState::setLoop(bool loop)
{
	m_loop = loop;
}

bool GAnimatorState::isLoop() const
{
	return m_loop;
}

void GAnimatorState::setMotion(const std::string& motion)
{
	m_motion = motion;
}

const std::string& GAnimatorState::getMotion() const
{
	return m_motion;
}

void GAnimatorState::setSpeed(float speed)
{
	m_speed = speed;
}

float GAnimatorState::getSpeed() const
{
	return m_speed;
}

void GAnimatorState::setMutiplier(const std::string& mutiplier)
{
	m_mutiplier = mutiplier;
}

const std::string& GAnimatorState::getMutiplier() const
{
	return m_mutiplier;
}