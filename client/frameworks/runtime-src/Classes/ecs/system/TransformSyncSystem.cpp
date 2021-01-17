#include "TransformSyncSystem.h"

void TransformSyncSystem::sync()
{
	const auto& entities = this->getEntities();
	for (auto& it : entities)
	{
		auto& transform = it.getComponent<TransformComponent>();
		auto& simphys = it.getComponent<SIMPhysComponent>();
		transform.logicPos.x = simphys.position.x;
		transform.logicPos.y = simphys.position.y;
		// Âß¼­×ø±ê×ªÆÁÄ»×ø±ê
		transform.position.x = transform.logicPos.x;
		transform.position.y = transform.logicPos.y;
	}
}

void TransformSyncSystem::syncRender()
{
#if G_TARGET_SERVER
#else
	const auto& entities = this->getEntities();
	for (auto& it : entities)
	{
		auto& component = it.getComponent<ArmatureRenderComponent>();
		if (component.render)
		{
			component.render->setPosition(it.getComponent<TransformComponent>().position);
		}
	}
#endif
}
