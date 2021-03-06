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

	HASH_IS_INAIR	= params().hashKey("isInAir");
	HASH_IS_DEATH	= params().hashKey("isDeath");
	HASH_CAN_BREAK	= params().hashKey("canBreak");
	HASH_IS_JUMP	= params().hashKey("isJump");
	HASH_IS_RUN		= params().hashKey("isRun");

	HASH_KEY_DOWN_JUMP = params().hashKey("keyDownJump");

	HASH_TO_STAND	= params().hashKey("toStand");
	HASH_TO_HIT		= params().hashKey("toHit");

	HASH_Y_VELOCITY = params().hashKey("yVelocity");

	return true;
}

// 播放动画接口
void GActorStateMachine::playAnimation(const std::string& animName, bool loop)
{
	std::string curAniName = getAniName(animName.c_str(), true);
	G_LOG_I("playAnimation %s", curAniName.c_str());
	ArmatureUtils::playAnimationCMD(m_entity, curAniName, loop ? kArmaturePlayMode::LOOP : kArmaturePlayMode::ONCE);
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
	auto& simphys = m_entity.getComponent<SIMPhysComponent>();

	if (float_equal(simphys.linearVelocity.y, 0.0f))
	{
		G_BIT_REMOVE(property.status, G_PS_IS_IN_AIR);
		property.jumpCount = 0;
	}
	else
	{
		G_BIT_SET(property.status, G_PS_IS_IN_AIR);
	}

	//params().setBool(HASH_CAN_BREAK, false);
	params().setBool(HASH_IS_INAIR, G_BIT_EQUAL(property.status, G_PS_IS_IN_AIR));
	params().setBool(HASH_IS_DEATH, G_BIT_EQUAL(property.status, G_PS_IS_DEATH));
	params().setFloat(HASH_Y_VELOCITY, simphys.linearVelocity.y);

	Super::update(dt);
}

void GActorStateMachine::updateInput()
{
	//auto& input = m_entity.getComponent<InputComponent>();
	//auto& property = m_entity.getComponent<PropertyComponent>();

	////!< 判断是否按下了移动按键
	//bool isMove = G_BIT_GET(input.keyDown, G_KEY_MOVE_MUSTER);
	//params().setBool(HASH_IS_RUN, isMove);

	//if (isMove)
	//{
	//	///! 更新朝向
	//	// 左移
	//	if (G_BIT_EQUAL(input.keyDown, G_KEY_MOVE_LEFT))
	//	{
	//		if (G_BIT_NO_EQUAL(property.lockStatus, G_LOCK_S_FACE_CAHGNE))
	//			G_BIT_REMOVE(property.status, G_PS_IS_FACE_R);
	//	}
	//	// 右移
	//	else if (G_BIT_EQUAL(input.keyDown, G_KEY_MOVE_RIGHT))
	//	{
	//		if (G_BIT_NO_EQUAL(property.lockStatus, G_LOCK_S_FACE_CAHGNE))
	//			G_BIT_SET(property.status, G_PS_IS_FACE_R);
	//	}
	//}
	//else
	//{
	//	auto& simPhys = m_entity.getComponent<SIMPhysComponent>();
	//	simPhys.linearVelocity.x = 0.0f;
	//	simPhys.force.setzero();
	//}

	////!< 跳跃
	//if (G_BIT_EQUAL(input.keyDown, G_KEY_JUMP) &&
	//	G_BIT_NO_EQUAL(property.lockStatus, G_LOCK_S_JUMP) &&
	//	property.jumpCount < property.jumpMaxCount)
	//{
	//	params().setBool(HASH_KEY_DOWN_JUMP, true);
	//}
	//else
	//{
	//	params().setBool(HASH_KEY_DOWN_JUMP, false);
	//}
}

// 按键按下
void GActorStateMachine::onKeyDown(G_BIT_TYPE key)
{
	auto& property = m_entity.getComponent<PropertyComponent>();

	///! 更新朝向
	// 左移
	if (G_BIT_EQUAL(key, G_KEY_MOVE_LEFT))
	{
		if (G_BIT_NO_EQUAL(property.lockStatus, G_LOCK_S_FACE_CAHGNE))
			G_BIT_REMOVE(property.status, G_PS_IS_FACE_R);
	}
	// 右移
	else if (G_BIT_EQUAL(key, G_KEY_MOVE_RIGHT))
	{
		if (G_BIT_NO_EQUAL(property.lockStatus, G_LOCK_S_FACE_CAHGNE))
			G_BIT_SET(property.status, G_PS_IS_FACE_R);
	}
	// 跳跃
	else if (G_BIT_EQUAL(key, G_KEY_JUMP))
	{
		if (G_BIT_NO_EQUAL(property.lockStatus, G_LOCK_S_JUMP) && property.jumpCount < property.jumpMaxCount)
		{
			params().setBool(HASH_KEY_DOWN_JUMP, true);
		}
	}
}

// 按键抬起
void GActorStateMachine::onKeyUp(G_BIT_TYPE key)
{
	if (G_BIT_EQUAL(key, G_KEY_MOVE_LEFT) || G_BIT_EQUAL(key, G_KEY_MOVE_RIGHT))
	{
		auto& simPhys = m_entity.getComponent<SIMPhysComponent>();
		simPhys.linearVelocity.x = 0.0f;
		simPhys.force.setzero();
	}
	else if (G_BIT_EQUAL(key, G_KEY_JUMP))
	{
		params().setBool(HASH_KEY_DOWN_JUMP, false);
	}
}

// 按键持续按下
void GActorStateMachine::onKeepPress(G_BIT_TYPE key)
{}

void GActorStateMachine::onAnimFinished()
{
	Super::onAnimFinished();

	//auto completeState = getCompleteState();

	//// 没有下一个动画
	//if (completeState->getTranslationCount() <= 0)
	//{
	//	params().setBool(HASH_TO_STAND, true);
	//	return;
	//}
}

// 状态进入
void GActorStateMachine::onStateEnter(GAnimatorState* state)
{
	m_curStateType = anim::getStateType(state->getStateName().c_str());

	switch (m_curStateType)
	{
	case anim::FIGHT_STAND:
	{
		params().setBool(HASH_TO_STAND, false);
	}break;
	case anim::FIGHT_JUMPUP:
	case anim::FIGHT_JUMPDOWN:
	{
		if (m_curStateType == FIGHT_JUMPUP)
		{
			auto& simPhys = m_entity.getComponent<SIMPhysComponent>();
			auto& property = m_entity.getComponent<PropertyComponent>();
			simPhys.linearVelocity.y = 0.0f;
			SIMPhysSystem::applyImpulse(&simPhys, property.jumpIm);
			property.jumpCount++;
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
	case anim::FIGHT_JUMPUP:
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
	auto& input = m_entity.getComponent<InputComponent>();
	auto& simPhys = m_entity.getComponent<SIMPhysComponent>();
	auto& property = m_entity.getComponent<PropertyComponent>();

	// 按下了左右移动按键
	if (G_BIT_GET(input.keyDown, G_KEY_MOVE_X) && G_BIT_NO_EQUAL(property.lockStatus, G_LOCK_S_MOVE_X))
	{
		// 最大速度
		auto moveMaxVelocityX = property.moveMaxVelocityX;
		// 移动力
		auto moveForceX = property.moveForce.x;

		if (m_curStateType != FIGHT_RUN)
		{
			moveMaxVelocityX *= 0.2f;
		}

		// 左移
		if (G_BIT_EQUAL(input.keyDown, G_KEY_MOVE_LEFT))
		{
			simPhys.linearVelocity.x = MIN(simPhys.linearVelocity.x, 0.0f);
			simPhys.linearVelocity.x = MAX(simPhys.linearVelocity.x, -moveMaxVelocityX);
			if (simPhys.linearVelocity.x > -moveMaxVelocityX)
			{
				SIMPhysSystem::applyForce(&simPhys, GVec2(-moveForceX, 0.0f));
			}
		}
		// 右移
		else if (G_BIT_EQUAL(input.keyDown, G_KEY_MOVE_RIGHT))
		{
			simPhys.linearVelocity.x = MAX(simPhys.linearVelocity.x, 0.0f);
			simPhys.linearVelocity.x = MIN(simPhys.linearVelocity.x, moveMaxVelocityX);
			if (simPhys.linearVelocity.x < moveMaxVelocityX)
			{
				SIMPhysSystem::applyForce(&simPhys, GVec2(moveForceX, 0.0f));
			}
		}
	}
	else
	{
		simPhys.linearVelocity.x = 0;
	}

	///! 上下移动逻辑(Z轴移动)
	if (m_curStateType == FIGHT_RUN &&
		G_BIT_NO_EQUAL(property.status, G_PS_IS_IN_AIR) &&
		G_BIT_NO_EQUAL(property.lockStatus, G_LOCK_S_MOVE_Y))
	{
		// 上移
		if (G_BIT_EQUAL(input.keyDown, G_KEY_MOVE_UP))
		{
			// SIMPhysComponent 模拟X轴和Z轴,Y轴移动单独更改TransformComponent的逻辑坐标值
			auto& logicPos = m_entity.getComponent<TransformComponent>().logicPos;
			auto& global = CommonUtils::getGlobalComponent(m_entity.getWorld());

			logicPos.y += property.moveForce.y;
			logicPos.y = clamp(global.minPosy, global.maxPosy, logicPos.y);
		}
		// 下移
		else if (G_BIT_EQUAL(input.keyDown, G_KEY_MOVE_DOWN))
		{
			auto& logicPos = m_entity.getComponent<TransformComponent>().logicPos;
			auto& global = CommonUtils::getGlobalComponent(m_entity.getWorld());

			logicPos.y -= property.moveForce.y;
			logicPos.y = clamp(global.minPosy, global.maxPosy, logicPos.y);
		}
	}
}
