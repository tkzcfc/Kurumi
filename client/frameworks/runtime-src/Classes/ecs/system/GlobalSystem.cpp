#include "GlobalSystem.h"

void GlobalSystem::initialize()
{
	admin = getWorld().createEntity();

	admin.addComponent<UniqueComponent>();
	admin.addComponent<DebugComponent>();
	admin.addComponent<MapComponent>();

	admin.activate();
}
