#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/components/ArmatureComponent.h"
#include "ecs/components/SIMPhysComponent.h"
#include "ecs/components/PropertyComponent.h"

// 坐标同步系统,将逻辑3D坐标转换为2D坐标
#if G_TARGET_CLIENT
class TransformSyncSystem : public anax::System<anax::Requires<TransformComponent, SIMPhysComponent, PropertyComponent, ArmatureRenderComponent>>
#else
class TransformSyncSystem : public anax::System<anax::Requires<TransformComponent, SIMPhysComponent, PropertyComponent>>
#endif
{
public:

	void sync();

	void syncRender();
};
