#include "InputSystem.h"
#include "ecs/system/SIMPhysSystem.h"

void InputSystem::beforeInput()
{
	// 保存上一帧输入状态
	auto& entities = this->getEntities();
	for (auto& entity : entities)
	{
		auto& inputComponent = entity.getComponent<InputComponent>();
		inputComponent.lastKeyDown = inputComponent.keyDown;
	}
}

void InputSystem::input(GOPMsg_Base* msg)
{
	auto& entities = this->getEntities();
	for (auto& entity : entities)
	{
		if (msg->uuid == entity.getComponent<PropertyComponent>().uuid)
		{
			auto& inputComponent = entity.getComponent<InputComponent>();
			// 按键抬起
			if (G_BIT_EQUAL(msg->cmd, G_CMD_KEY_UP))
			{
#if 0
				auto tempValue = inputComponent.keyDown;
#endif
				auto msgKey = (GOPMsg_Key*)msg;
				G_BIT_CLEAR(inputComponent.keyDown, msgKey->key);

#if 0
				// 验证一下上面的方法是对的不
				for (auto i = 1; i < G_BIT_MAX_COUNT; ++i)
				{
					if (G_BIT_EQUAL(msgKey->key, G_FIXED_VALUE << i))
						G_BIT_CLEAR(tempValue, G_FIXED_VALUE << i);
				}
				G_ASSERT(tempValue == inputComponent.keyDown);
#endif
			}
			// 按键按下
			else if (G_BIT_EQUAL(msg->cmd, G_CMD_KEY_DOWN))
			{
				auto msgKey = (GOPMsg_Key*)msg;
				G_BIT_SET(inputComponent.keyDown, msgKey->key);
			}
		}
	}
}

void InputSystem::afterInput()
{
	auto keys = getAutoResetKeys();
	auto& entities = this->getEntities();
	for (auto& entity : entities)
	{
		auto& input = entity.getComponent<InputComponent>();
		auto& simPhys = entity.getComponent<SIMPhysComponent>();
		auto& property = entity.getComponent<PropertyComponent>();

		// 左移
		if (G_BIT_EQUAL(input.keyDown, G_KEY_MOVE_LEFT))
		{
			if (G_BIT_NO_EQUAL(property.lockStatus, LOCK_S_FACE_CAHGNE))
				G_BIT_CLEAR(property.status, PS_IS_FACE_R);

			if (G_BIT_NO_EQUAL(property.lockStatus, LOCK_S_MOVE_X))
				SIMPhysSystem::applyForce(&simPhys, GVec2(-property.moveForce.x, 0.0f));
		}
		// 右移
		else if (G_BIT_EQUAL(input.keyDown, G_KEY_MOVE_RIGHT))
		{
			if (G_BIT_NO_EQUAL(property.lockStatus, LOCK_S_FACE_CAHGNE))
				G_BIT_CLEAR(property.status, (G_BIT_TYPE)PS_IS_FACE_R);
			if (G_BIT_NO_EQUAL(property.lockStatus, LOCK_S_MOVE_X))
				SIMPhysSystem::applyForce(&simPhys, GVec2(property.moveForce.x, 0.0f));
		}
		// 上移
		else if (G_BIT_EQUAL(input.keyDown, G_KEY_MOVE_UP))
		{
			
			if (G_BIT_NO_EQUAL(property.status, PS_IS_IN_AIR))
			{

			}
		}
		// 下移
		else if (G_BIT_EQUAL(input.keyDown, G_KEY_MOVE_DOWN))
		{
			if (G_BIT_NO_EQUAL(property.status, PS_IS_IN_AIR))
			{
			}
		}
		else if (G_BIT_EQUAL(input.keyDown, G_KEY_JUMP))
		{
			/*if (property.arrBeginTime[TIME_S_JUMP])
			{
			}*/
		}
		
		// 自动复原按键
		G_BIT_CLEAR(input.keyDown, keys);
	}
}