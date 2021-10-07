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

		//CCLOG("sync x: %f", transform.logicRenderPos.x);
		// 保存实际渲染坐标
		transform.lastRenderPos = transform.logicRenderPos;

		// 逻辑坐标转屏幕坐标
		transform.logicRenderPos.x = transform.logicPos.x;
		transform.logicRenderPos.y = transform.logicPos.y + transform.logicPos.z;

		//CCLOG("sync x222: %f", transform.logicRenderPos.x);

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
				transform.lastRenderPos = transform.logicRenderPos;
			}
			else
			{
				transform.renderPos = transform.lastRenderPos.lerp(transform.logicRenderPos, percent);
			}

			//if (component.render->getPositionX() > transform.renderPos.x)
			//{
			//	CCLOG("diff x :%f, percent:%f", component.render->getPositionX() - transform.renderPos.x, percent);
			//}

			component.render->setPosition(transform.renderPos);

			component.render->setScaleX(transform.scaleX);
			component.render->setScaleY(transform.scaleY);
		}
	}
}
