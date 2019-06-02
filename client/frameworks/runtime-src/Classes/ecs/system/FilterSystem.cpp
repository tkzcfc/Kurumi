#include "FilterSystem.h"


FilterSystem::FilterSystem()
{}

FilterSystem::~FilterSystem()
{}

std::vector<Actor*> FilterSystem::getAllActorByFilterData(int filterData)
{
	std::vector<Actor*> outValue;

	const auto& entities = this->getEntities();
	for (auto& it : entities)
	{
		if (it.getComponent<FilterComponent>().m_filterData == filterData)
		{
			outValue.emplace_back(it.getComponent<FilterComponent>().m_owner);
		}
	}
	return outValue;
}

Actor* FilterSystem::randomGetActorByFilterData(int filterData)
{
	std::vector<Actor*> outValue;

	const auto& entities = this->getEntities();
	for (auto& it : entities)
	{
		if (it.getComponent<FilterComponent>().m_filterData == filterData)
		{
			outValue.emplace_back(it.getComponent<FilterComponent>().m_owner);
		}
	}
	
	if (outValue.size() > 0)
	{
		return outValue[std::rand() % outValue.size()];
	}
	return NULL;
}

