#include "anaxHelper.h"

#include "ecs/components/ArmatureComponent.h"
#include "ecs/components/Box2DComponent.h"
#include "ecs/components/MapFollowComponent.h"
#include "ecs/components/OrientationComponent.h"
#include "ecs/components/UpdateComponent.h"

#include "ecs/system/ArmatureCollisionSystem.h"
#include "ecs/system/Box2DSystem.h"
#include "ecs/system/MapFollowSystem.h"
#include "ecs/system/UpdateSystem.h"


std::unordered_map<std::string, SystemHelper*> AnaxHelper::GSystemHelperMap;
std::unordered_map<std::string, ComponentHelper*> AnaxHelper::GComponentHelperMap;

void AnaxHelper::implementation()
{
	IMPLEMENTATION_COMPONENT(ArmatureComponent);
	IMPLEMENTATION_COMPONENT(ArmatureCollisionComponent);
	IMPLEMENTATION_COMPONENT(CollisionFilterComponent);
	IMPLEMENTATION_COMPONENT(Box2DComponent);
	IMPLEMENTATION_COMPONENT(MapFollowComponent);
	IMPLEMENTATION_COMPONENT(OrientationComponent);
	IMPLEMENTATION_COMPONENT(UpdateComponent);


	IMPLEMENTATION_SYSTEM(ArmatureCollisionSystem);
	IMPLEMENTATION_SYSTEM(Box2DSystem);
	IMPLEMENTATION_SYSTEM(MapFollowSystem);
	IMPLEMENTATION_SYSTEM(UpdateSystem);


#if (COCOS2D_DEBUG == 1)
	CCLOG("[--------------------component begin--------------------]");
	for (auto& it : GComponentHelperMap)
	{
		CCLOG("|register component[%s]->[%d]|", it.first.c_str(), it.second->typeId);
	}
	CCLOG("[--------------------component end--------------------]\n\n");
	CCLOG("[--------------------system begin--------------------]");
	for (auto& it : GSystemHelperMap)
	{
		CCLOG("|register system[%s]->[%d]|", it.first.c_str(), it.second->typeId);
	}
	CCLOG("[--------------------system end--------------------]");
#endif
}

