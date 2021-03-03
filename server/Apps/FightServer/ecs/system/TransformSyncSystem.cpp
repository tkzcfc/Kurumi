#include "TransformSyncSystem.h"

void TransformSyncSystem::sync()
{
	const auto& entities = this->getEntities();
	for (auto& it : entities)
	{
		auto& transform = it.getComponent<TransformComponent>();
		auto& simphys = it.getComponent<SIMPhysComponent>();
		transform.logicPos.x = simphys.position.x * PHYSICS_PIXEL_TO_METER;
		transform.logicPos.z = simphys.position.y * PHYSICS_PIXEL_TO_METER;
		
		// 逻辑坐标转屏幕坐标
		transform.position.x = transform.logicPos.x;
		transform.position.y = transform.logicPos.y + transform.logicPos.z;
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
