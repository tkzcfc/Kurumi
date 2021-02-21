#include "UpdateSystem.h"

void UpdateSystem::update(float dt)
{
	const auto& entities = this->getEntities();
	for (auto& it : entities)
	{
		it.getComponent<PropertyComponent>().stateMachine->update(dt);
	}
}
