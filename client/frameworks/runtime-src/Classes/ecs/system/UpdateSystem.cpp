#include "UpdateSystem.h"

UpdateSystem::UpdateSystem()
{}

UpdateSystem::~UpdateSystem()
{}

void UpdateSystem::update(float delta)
{
	auto& entities = getEntities();
	for (auto& it : entities)
	{
		auto& component = it.getComponent<UpdateComponent>();
		if (component.m_updateCall.isvalid())
		{
			component.m_updateCall(delta);
		}
	}
}

void UpdateSystem::lastUpdate(float delta)
{
	auto& entities = getEntities();
	for (auto& it : entities)
	{
		auto& component = it.getComponent<UpdateComponent>();
		if (component.m_lastUpdateCall.isvalid())
		{
			component.m_lastUpdateCall(delta);
		}
	}
}
