#include "CollisionSystem.h"

void CollisionSystem::update()
{
}

GAnimationData* CollisionSystem::getAnimData(ArmatureComponent& component)
{
	if (component.roleName.empty())
		return NULL;

	auto tmp = GAnimDataCache::getInstance()->getOrCreate(component.roleName);
	if (tmp == NULL)
		return NULL;

	auto aniData = tmp->getAniData(component.curAniName);
	if (aniData == NULL)
		return NULL;

	if (component.curFrameIndex >= aniData->duration)
	{
		G_ASSERT(false);
		return NULL;
	}
	return aniData;
}
