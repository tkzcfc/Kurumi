#include "anaxHelper.h"
#include "ECSDefine.h"

std::unordered_map<std::string, SystemHelper*> AnaxHelper::GSystemHelperMap;
std::unordered_map<std::string, ComponentHelper*> AnaxHelper::GComponentHelperMap;

void AnaxHelper::implementation()
{
	// IMPLEMENT_BEGIN
	IMPLEMENTATION_COMPONENT(ArmatureComponent);
	IMPLEMENTATION_COMPONENT(ArmatureRenderComponent);
	IMPLEMENTATION_COMPONENT(BodyComponent);
	IMPLEMENTATION_COMPONENT(DebugComponent);
	IMPLEMENTATION_COMPONENT(GlobalComponent);
	IMPLEMENTATION_COMPONENT(InputComponent);
	IMPLEMENTATION_COMPONENT(MapComponent);
	IMPLEMENTATION_COMPONENT(PropertyComponent);
	IMPLEMENTATION_COMPONENT(SIMPhysComponent);
	IMPLEMENTATION_COMPONENT(TransformComponent);
	IMPLEMENTATION_SYSTEM(ArmatureDebugSystem);
	#if G_TARGET_CLIENT
	IMPLEMENTATION_SYSTEM(ArmatureRenderSystem);
	#endif
	IMPLEMENTATION_SYSTEM(ArmatureSystem);
	IMPLEMENTATION_SYSTEM(CollisionSystem);
	IMPLEMENTATION_SYSTEM(GlobalSystem);
	IMPLEMENTATION_SYSTEM(InputSystem);
	IMPLEMENTATION_SYSTEM(PhysicsSystem);
	IMPLEMENTATION_SYSTEM(RenderSyncSystem);
	IMPLEMENTATION_SYSTEM(SIMPhysSystem);
	IMPLEMENTATION_SYSTEM(TransformSyncSystem);
	// IMPLEMENT_END

}

