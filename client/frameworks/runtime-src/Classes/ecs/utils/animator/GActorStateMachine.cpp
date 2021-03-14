#include "GActorStateMachine.h"
#include "ecs/utils/ArmatureUtils.h"
#include "ecs/utils/CommonUtils.h"
#include "ecs/system/SIMPhysSystem.h"
#include "ecs/components/InputComponent.h"
#include "ecs/components/PropertyComponent.h"
#include "ecs/components/TransformComponent.h"

using namespace anim;

void GActorStateMachine::setEntity(const anax::Entity& entity)
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
	{
		G_ASSERT(0);
		return false;
	}

	HASH_IS_FIGHT	= params().hashKey("isFight");
	HASH_IS_INAIR	= params().hashKey("isInAir");
	HASH_IS_DEATH	= params().hashKey("isDeath");
	HASH_CAN_BREAK	= params().hashKey("canBreak");
	HASH_IS_JUMP	= params().hashKey("isJump");
	HASH_IS_RUN		= params().hashKey("isRun");

	HASH_KEY_DOWN_JUMP = params().hashKey("keyDownJump");

	HASH_TO_STAND	= params().hashKey("toStand");
	HASH_TO_HIT		= params().hashKey("toHit");
	HASH_TO_JUMP_DOWN = params().hashKey("toJumpDown");

	return true;
}

// 播放动画接口
void GActorStateMachine::playAnimation(const std::string& animName, bool loop)
{
	G_LOG_I("playAnimation %s", animName.c_str());
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

	//params().setBool(HASH_IS_FIGHT, false);
	//params().setBool(HASH_CAN_BREAK, false);
	params().setBool(HASH_IS_INAIR, G_BIT_EQUAL(property.status, G_PS_IS_IN_AIR));
	params().setBool(HASH_IS_DEATH, G_BIT_EQUAL(property.status, G_PS_IS_DEATH));

	Super::update(dt);
}

void GActorStateMachine::updateInput()
{
	auto& input = m_entity.getComponent<InputComponent>();
	auto& simPhys = m_entity.getComponent<SIMPhysComponent>();
	auto& property = m_entity.getComponent<PropertyComponent>();

	//! 判断是否按下了移动按键
	if (G_BIT_GET(input.keyDown, G_KEY_MOVE_LEFT | G_KEY_MOVE_RIGHT | G_KEY_MOVE_UP | G_KEY_MOVE_DOWN))
		params().setBool(HASH_IS_RUN, true);
	else
		params().setBool(HASH_IS_RUN, false);

	///! 更新朝向
	// 左移
	if (G_BIT_EQUAL(input.keyDown, G_KEY_MOVE_LEFT))
	{
		if (G_BIT_NO_EQUAL(property.lockStatus, G_LOCK_S_FACE_CAHGNE))
			G_BIT_CLEAR(property.status, G_PS_IS_FACE_R);
	}
	// 右移
	else if (G_BIT_EQUAL(input.keyDown, G_KEY_MOVE_RIGHT))
	{
		if (G_BIT_NO_EQUAL(property.lockStatus, G_LOCK_S_FACE_CAHGNE))
			G_BIT_SET(property.status, G_PS_IS_FACE_R);
	}

	//! 跳跃
	if (G_BIT_EQUAL(input.keyDown, G_KEY_JUMP) &&
		G_BIT_NO_EQUAL(property.lockStatus, G_LOCK_S_JUMP) &&
		property.jumpCount < property.jumpMaxCount)
	{
		params().setBool(HASH_KEY_DOWN_JUMP, true);
	}
	else
	{
		params().setBool(HASH_KEY_DOWN_JUMP, false);
	}
}

void GActorStateMachine::onAnimFinished()
{
	Super::onAnimFinished();

	auto completeState = getCompleteState();

	if (m_curStateType == anim::COMMON_JUMPDOWN || m_curStateType == anim::FIGHT_JUMPDOWN)
		return;
	// 没有下一个动画
	if (completeState->getTranslationCount() <= 0)
	{
		params().setBool(HASH_TO_STAND, true);
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
		params().setBool(HASH_TO_STAND, false);
	}break;
	case anim::COMMON_JUMPUP:
	case anim::FIGHT_JUMPUP:
	case anim::COMMON_JUMPDOWN:
	case anim::FIGHT_JUMPDOWN:
	{
		if (m_curStateType == COMMON_JUMPUP || m_curStateType == FIGHT_JUMPUP)
		{
			auto& simPhys = m_entity.getComponent<SIMPhysComponent>();
			auto& property = m_entity.getComponent<PropertyComponent>();
			SIMPhysSystem::applyImpulse(&simPhys, property.jumpIm);
			property.jumpCount++;
		}
		if (m_curStateType == COMMON_JUMPDOWN || m_curStateType == FIGHT_JUMPDOWN)
		{
			params().setBool(HASH_TO_JUMP_DOWN, false);
		}
		params().setBool(HASH_IS_JUMP, true);
	}break;
	case anim::HIT:
	{
		params().setBool(HASH_TO_HIT, false);
	}break;
	default:
		break;
	}
}

// 状态退出
void GActorStateMachine::onStateExit(GAnimatorState* state)
{
	switch (m_curStateType)
	{
	case anim::COMMON_JUMPUP:
	case anim::FIGHT_JUMPUP:
	case anim::COMMON_JUMPDOWN:
	case anim::FIGHT_JUMPDOWN:
	{
		params().setBool(HASH_IS_JUMP, false);
	}break;
	default:
		break;
	}
}

// 状态停留
void GActorStateMachine::onStateStay(GAnimatorState* state)
{
	//! 跳跃且处于上升状态时,速度小于0则切换为下降状态
	if (m_curStateType == COMMON_JUMPUP || m_curStateType == FIGHT_JUMPUP)
	{
		if(m_entity.getComponent<SIMPhysComponent>().linearVelocity.y < 0.0f)
			params().setBool(HASH_TO_JUMP_DOWN, true);
	}
	if (m_curStateType == COMMON_JUMPDOWN || m_curStateType == FIGHT_JUMPDOWN)
	{
		if (G_BIT_NO_EQUAL(m_entity.getComponent<PropertyComponent>().status, G_PS_IS_IN_AIR))
			params().setBool(HASH_TO_STAND, true);
	}

	if (m_curStateType == COMMON_RUN || m_curStateType == FIGHT_RUN)
	{
		auto& input = m_entity.getComponent<InputComponent>();
		auto& simPhys = m_entity.getComponent<SIMPhysComponent>();
		auto& property = m_entity.getComponent<PropertyComponent>();

		///! X轴移动
		// 左移
		if (G_BIT_EQUAL(input.keyDown, G_KEY_MOVE_LEFT))
		{
			if (G_BIT_NO_EQUAL(property.lockStatus, G_LOCK_S_MOVE_X))
				SIMPhysSystem::applyForce(&simPhys, GVec2(-property.moveForce.x, 0.0f));
		}
		// 右移
		else if (G_BIT_EQUAL(input.keyDown, G_KEY_MOVE_RIGHT))
		{
			if (G_BIT_NO_EQUAL(property.lockStatus, G_LOCK_S_MOVE_X))
				SIMPhysSystem::applyForce(&simPhys, GVec2(property.moveForce.x, 0.0f));
		}
		
		///! Y轴移动
		// 上移
		if (G_BIT_EQUAL(input.keyDown, G_KEY_MOVE_UP))
		{
			if (G_BIT_NO_EQUAL(property.status, G_PS_IS_IN_AIR) && G_BIT_NO_EQUAL(property.lockStatus, G_LOCK_S_MOVE_Y))
			{
				// SIMPhysComponent 模拟X轴和Z轴,Y轴移动单独更改TransformComponent的逻辑坐标值
				auto& logicPos = m_entity.getComponent<TransformComponent>().logicPos;
				auto& global = CommonUtils::getGlobalComponent(m_entity.getWorld());

				logicPos.y += property.moveForce.y;
				logicPos.y = clamp(global.minPosy, global.maxPosy, logicPos.y);
			}
		}
		// 下移
		else if (G_BIT_EQUAL(input.keyDown, G_KEY_MOVE_DOWN))
		{
			if (G_BIT_NO_EQUAL(property.status, G_PS_IS_IN_AIR) && G_BIT_NO_EQUAL(property.lockStatus, G_LOCK_S_MOVE_Y))
			{
				auto& logicPos = m_entity.getComponent<TransformComponent>().logicPos;
				auto& global = CommonUtils::getGlobalComponent(m_entity.getWorld());

				logicPos.y -= property.moveForce.y;
				logicPos.y = clamp(global.minPosy, global.maxPosy, logicPos.y);
			}
		}
	}
}
