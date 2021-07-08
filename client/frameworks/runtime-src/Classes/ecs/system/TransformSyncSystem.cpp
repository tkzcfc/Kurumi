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
		
		// 保存实际渲染坐标
		transform.lastRenderPos = transform.renderPos;

		// 逻辑坐标转屏幕坐标
		transform.logicRenderPos.x = transform.logicPos.x;
		transform.logicRenderPos.y = transform.logicPos.y + transform.logicPos.z;

		if (G_BIT_EQUAL(property.status, G_PS_IS_FACE_R))
		{
			transform.scaleX = property.scale;
			transform.scaleY = property.scale;
		}
		else
		{
			transform.scaleX = -property.scale;
			transform.scaleY = property.scale;
		}
	}
}

void TransformSyncSystem::syncRender(float percent)
{
	const auto& entities = this->getEntities();
	for (auto& it : entities)
	{
		auto& component = it.getComponent<ArmatureRenderComponent>();
		if (component.render)
		{
			auto& transform = it.getComponent<TransformComponent>();
			if (percent >= 1.0f)
			{
				transform.renderPos = transform.logicRenderPos;
			}
			else
			{
				transform.renderPos = transform.lastRenderPos.lerp(transform.logicRenderPos, percent);
				//CCLOG("percent:%f", percent);
			}
			component.render->setPosition(transform.logicRenderPos);

			component.render->setScaleX(transform.scaleX);
			component.render->setScaleY(transform.scaleY);
		}
	}
}
