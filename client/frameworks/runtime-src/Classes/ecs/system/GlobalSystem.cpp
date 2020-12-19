#include "GlobalSystem.h"

void GlobalSystem::initialize()
{
	admin = getWorld().createEntity();
	auto& component = admin.addComponent<UniqueComponent>();
	admin.activate();
}
