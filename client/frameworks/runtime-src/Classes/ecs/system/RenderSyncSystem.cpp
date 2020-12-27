#include "RenderSyncSystem.h"

void RenderSyncSystem::sync()
{
#if G_TARGET_CLIENT
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
