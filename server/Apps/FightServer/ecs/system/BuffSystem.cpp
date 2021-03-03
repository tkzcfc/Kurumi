#include "BuffSystem.h"


void BuffSystem::removeInvalid()
{
	for (auto& it : getEntities())
	{
		auto& buffCom = it.getComponent<BuffComponent>();
		if (!buffCom.buffList.empty())
		{
			for (auto bufit = buffCom.buffList.begin(); bufit != buffCom.buffList.end(); )
			{
				if ((*bufit)->canRemove())
					bufit = buffCom.buffList.erase(bufit);
				else
					bufit++;
			}
		}
	}
}

void BuffSystem::update()
{
	for (auto& it : getEntities())
	{
		auto& buffCom = it.getComponent<BuffComponent>();
		if (!buffCom.buffList.empty())
		{
			for (auto& buf : buffCom.buffList)
			{
				buf->execute(it);
			}
		}
	}
}

