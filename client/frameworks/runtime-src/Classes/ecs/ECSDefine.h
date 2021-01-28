#pragma once

#include "anaxHelper.h"

// INCLUDE_BEGIN
#include "components/ArmatureComponent.h"
#include "components/TransformComponent.h"
#include "components/PropertyComponent.h"
#include "components/InputComponent.h"
#include "components/DebugComponent.h"
#include "components/MapComponent.h"
#include "components/GlobalComponent.h"
#include "components/SIMPhysComponent.h"
#include "components/BodyComponent.h"
#include "system/PhysicsSystem.h"
#include "system/InputSystem.h"
#include "system/ArmatureDebugSystem.h"
#include "system/ArmatureSystem.h"
#include "system/GlobalSystem.h"
#include "system/TransformSyncSystem.h"
#include "system/CollisionSystem.h"
#include "system/SIMPhysSystem.h"
#include "system/ArmatureRenderSystem.h"
#include "system/RenderSyncSystem.h"
// INCLUDE_END





// DEFINE_BEGIN
DEFINE_COMPONENT(ArmatureComponent)
DEFINE_COMPONENT(ArmatureRenderComponent)
DEFINE_COMPONENT(BodyComponent)
DEFINE_COMPONENT(DebugComponent)
DEFINE_COMPONENT(GlobalComponent)
DEFINE_COMPONENT(InputComponent)
DEFINE_COMPONENT(MapComponent)
DEFINE_COMPONENT(PropertyComponent)
DEFINE_COMPONENT(SIMPhysComponent)
DEFINE_COMPONENT(TransformComponent)
DEFINE_SYSTEM(ArmatureDebugSystem)
#if G_TARGET_CLIENT
DEFINE_SYSTEM(ArmatureRenderSystem)
#endif
DEFINE_SYSTEM(ArmatureSystem)
DEFINE_SYSTEM(CollisionSystem)
DEFINE_SYSTEM(GlobalSystem)
DEFINE_SYSTEM(InputSystem)
DEFINE_SYSTEM(PhysicsSystem)
DEFINE_SYSTEM(RenderSyncSystem)
DEFINE_SYSTEM(SIMPhysSystem)
DEFINE_SYSTEM(TransformSyncSystem)
// DEFINE_END



