#include "TransformSyncSystem.h"

void TransformSyncSystem::sync()
{
	const auto& entities = this->getEntities();
	for (auto& it : entities)
	{
		auto& transform = it.getComponent<TransformComponent>();
		auto& simphys = it.getComponent<SIMPhysComponent>();
		auto& property = it.getComponent<PropertyComponent>();

		transform.logicPos.x = simphys.position.x * PHYSICS_PIXEL_TO_METER;
		transform.logicPos.z = simphys.position.y * PHYSICS_PIXEL_TO_METER;
		
		// 逻辑坐标转屏幕坐标
		transform.position.x = transform.logicPos.x;
		transform.position.y = transform.logicPos.y + transform.logicPos.z;

		if (G_BIT_EQUAL(property.status, G_PS_IS_FACE_R))
		{
			transform.scale = property.scale;
		}
		else
		{
			transform.scale = -property.scale;
		}

#if G_TARGET_CLIENT
		auto& renderCom = it.getComponent<ArmatureRenderComponent>();
		if (renderCom.render)
		{
			renderCom.render->setScaleX(transform.scale);
		}
#endif
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
