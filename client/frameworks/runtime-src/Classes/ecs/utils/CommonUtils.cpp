#include "CommonUtils.h"
#include "ecs/system/GlobalSystem.h"
#include "ecs/components/DebugComponent.h"

anax::Entity& CommonUtils::getAdmin(anax::World& world)
{
	auto sys = world.getSystem<GlobalSystem>();
	G_ASSERT(sys != NULL);

	return sys->admin;
}

#if G_TARGET_CLIENT
DrawNode* CommonUtils::getDebugDraw(anax::World& world)
{
	auto& admin = CommonUtils::getAdmin(world);
	auto& component = admin.getComponent<DebugComponent>();
	return component.debugDrawNode;
}
#endif

