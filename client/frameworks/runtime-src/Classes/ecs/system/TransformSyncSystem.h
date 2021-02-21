#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/components/ArmatureComponent.h"
#include "ecs/components/SIMPhysComponent.h"

// 坐标同步系统,将逻辑3D坐标转换为2D坐标
class TransformSyncSystem : public anax::System<anax::Requires<TransformComponent, SIMPhysComponent>>
{
public:

	void sync();

	void syncRender();
};
