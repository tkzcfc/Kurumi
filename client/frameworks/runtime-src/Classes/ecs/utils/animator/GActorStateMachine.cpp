#include "GActorStateMachine.h"
#include "ecs/utils/ArmatureUtils.h"
#include "ecs/system/SIMPhysSystem.h"
#include "ecs/components/PropertyComponent.h"

using namespace anim;

void GActorStateMachine::init(const anax::Entity& entity)
{
	m_entity = entity;
	m_entity.getComponent<ArmatureComponent>().onFinishCall = [=]()
	{
		this->onAnimFinished();
	};
}

// 使用json初始化动画状态机
bool GActorStateMachine::initWithJson(const std::string& content)
{
	if (!Super::initWithJson(content))
		return false;

	m_hash_isFight	= params().hashKey("isFight");
	m_hash_isInAir	= params().hashKey("isInAir");
	m_hash_isDeath	= params().hashKey("isDeath");
	m_hash_canBreak = params().hashKey("canBreak");
	m_hash_isJump	= params().hashKey("isJump");
	m_hash_isRun	= params().hashKey("isRun");

	m_hash_toStand	= params().hashKey("toStand");
	m_hash_toHit	= params().hashKey("toHit");
	m_hash_toJumpDown = params().hashKey("toJumpDown");

	return true;
}

// 播放动画接口
void GActorStateMachine::playAnimation(const std::string& animName, bool loop)
{
	ArmatureUtils::playAnimationCMD(m_entity, animName, loop ? kArmaturePlayMode::LOOP : kArmaturePlayMode::DEFAULT);
}

// 缩放动画播放速率
void GActorStateMachine::scaleTime(float scale)
{
	m_entity.getComponent<ArmatureComponent>().timeScale = scale;
}

// 外部调用更新
void GActorStateMachine::update(float dt)
{
	// 更新状态机内部值
	auto& property = m_entity.getComponent<PropertyComponent>();

	//params().setBool(m_hash_isFight, false);
	//params().setBool(m_hash_canBreak, false);
	params().setBool(m_hash_isInAir, G_BIT_EQUAL(property.status, PS_IS_IN_AIR));
	params().setBool(m_hash_isDeath, G_BIT_EQUAL(property.status, PS_IS_DEATH));
	params().setBool(m_hash_isJump, G_BIT_EQUAL(property.status, PS_IS_JUMP));
	params().setBool(m_hash_isRun, G_BIT_EQUAL(property.status, PS_IS_MOVE));

	Super::update(dt);
}

void GActorStateMachine::onAnimFinished()
{
	Super::onAnimFinished();

	auto completeState = getCompleteState();

	// 没有下一个动画
	if (completeState->getTranslationCount() <= 0)
	{
		params().setBool(m_hash_toStand, true);
		return;
	}

	//const auto& motion = getCompleteState()->getMotion();

}

// 状态进入
void GActorStateMachine::onStateEnter(GAnimatorState* state)
{
	m_curStateType = anim::getStateType(state->getStateName().c_str());

	switch (m_curStateType)
	{
	case anim::COMMON_STAND:
	case anim::FIGHT_STAND:
	{
		params().setBool(m_hash_toStand, false);
	}break;
	case anim::COMMON_JUMPUP:
	case anim::FIGHT_JUMPUP:
	case anim::COMMON_JUMPDOWN:
	case anim::FIGHT_JUMPDOWN:
	{
		params().setBool(m_hash_toHit, false);
	}break;
	case anim::HIT:
	{
		params().setBool(m_hash_toHit, false);
	}break;
	default:
		break;
	}
}

// 状态停留
void GActorStateMachine::onStateStay(GAnimatorState* state)
{
	// 跳跃状态时
	if (m_curStateType == COMMON_JUMPUP || m_curStateType == FIGHT_JUMPUP)
	{
		if(m_entity.getComponent<SIMPhysComponent>().linearVelocity.y < 0.0f)
			params().setBool(m_hash_toJumpDown, true);
	}
}

// 状态退出
void GActorStateMachine::onStateExit(GAnimatorState* state)
{}
