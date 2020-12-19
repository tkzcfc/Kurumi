#include "CommonUtils.h"
#include "ecs/system/GlobalSystem.h"

anax::Entity& CommonUtils::getAdmin(anax::World& world)
{
	auto sys = world.getSystem<GlobalSystem>();
	G_ASSERT(sys != NULL);

	return sys->admin;
}


