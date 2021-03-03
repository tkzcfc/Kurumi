#include "UUIDSystem.h"


bool UUIDSystem::query(GUUID uuid, anax::Entity* pEntity)
{
	auto& entities = getEntities();
	for (auto i = 0; i < entities.size(); ++i)
	{
		if (entities[i].getComponent<PropertyComponent>().uuid == uuid)
		{
			if (pEntity)
			{
				*pEntity = entities[i];
			}
			return true;
		}
	}
	return false;
}
