#include "TransformSyncSystem.h"

void TransformSyncSystem::sync()
{
	// Âß¼­×ø±ê×ªÆÁÄ»×ø±ê
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
