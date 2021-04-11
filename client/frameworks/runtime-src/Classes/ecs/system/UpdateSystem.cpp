#include "UpdateSystem.h"

void UpdateSystem::update(float dt)
{
	const auto& entities = this->getEntities();
	for (auto& it : entities)
	{
		auto& property = it.getComponent<PropertyComponent>();
		property.stateMachine->update(dt);
	}
}
