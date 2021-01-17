#include "InputSystem.h"
#include "ecs/system/SIMPhysSystem.h"

void InputSystem::update()
{
	auto& entities = this->getEntities();
	for (auto& entity : entities)
	{
		auto& input = entity.getComponent<InputComponent>();
		auto& simPhys = entity.getComponent<SIMPhysComponent>();
		auto& property = entity.getComponent<PropertyComponent>();
		if (input.moveEvent != IEvent_Move::MOVE_NONE)
		{
			if (property.isJumping)
			{
				if (G_BIT_EQUAL(input.moveEvent, IEvent_Move::MOVE_LEFT))
				{
					property.faceRight = false;
					SIMPhysSystem::applyForce(&simPhys, GVec2(-property.moveForce.x, 0.0f));
				}
				else if (G_BIT_EQUAL(input.moveEvent, IEvent_Move::MOVE_RIGHT))
				{
					property.faceRight = true;
					SIMPhysSystem::applyForce(&simPhys, GVec2(property.moveForce.x, 0.0f));
				}
			}
			else
			{
				if (G_BIT_EQUAL(input.moveEvent, IEvent_Move::MOVE_LEFT))
				{
					property.faceRight = false;
					SIMPhysSystem::applyForce(&simPhys, GVec2(-property.moveForce.x, 0.0f));
				}
				else if (G_BIT_EQUAL(input.moveEvent, IEvent_Move::MOVE_RIGHT))
				{
					property.faceRight = true;
					SIMPhysSystem::applyForce(&simPhys, GVec2(property.moveForce.x, 0.0f));
				}
				if (G_BIT_EQUAL(input.moveEvent, IEvent_Move::MOVE_UP))
				{
					SIMPhysSystem::applyForce(&simPhys, GVec2(0.0f, property.moveForce.y));
				}
				else if (G_BIT_EQUAL(input.moveEvent, IEvent_Move::MOVE_DOWN))
				{
					SIMPhysSystem::applyForce(&simPhys, GVec2(0.0f, -property.moveForce.y));
				}
			}
		}


		input.reset();
	}
}

