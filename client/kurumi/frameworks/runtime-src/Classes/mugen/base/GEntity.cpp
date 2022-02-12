#include "GEntity.h"
#include "GEntityManager.h"
#include "mugen/GGameDef.h"

NS_G_BEGIN


GEntity::GEntity()
	: m_id(0)
	, m_timeScale(1.0f)
	, m_elapsed(0.0f)
{
	m_components.reserve(10);
}

GEntity::~GEntity()
{
	removeAllComponents();
}

void GEntity::addComponent(GComponent* component)
{
	m_components.push_back(component);
	component->m_pEntity = this;
	component->onAdd();

	std::string name = component->name();

	auto it = m_componentMap.find(name);
	if (m_componentMap.end() == it)
	{
		m_componentMap[name] = component;
	}
	else
	{
		G_ASSERT(0);
	}
}

void GEntity::removeComponent(const std::string& name)
{
	auto it = m_componentMap.find(name);
	if (m_componentMap.end() != it)
	{
		auto ptr = it->second;
		for (auto itv = m_components.begin(); itv != m_components.end(); ++itv)
		{
			if (*itv == ptr)
			{
				m_components.erase(itv);
				break;
			}
		}

		ptr->m_pEntity = NULL;
		delete ptr;

		m_componentMap.erase(it);
	}
}

GComponent* GEntity::getComponent(const std::string& name)
{
	auto it = m_componentMap.find(name);
	if (m_componentMap.end() != it)
		return it->second;
	return NULL;
}

void GEntity::removeAllComponents()
{
	for (auto& it : m_components)
	{
		it->m_pEntity = NULL;
		delete it;
	}
	m_components.clear();
	m_componentMap.clear();
}

void GEntity::update()
{
	auto temp = LogicInterval * m_timeScale;
	m_elapsed += temp;
	while (m_elapsed >= LogicInterval)
	{
		m_elapsed -= LogicInterval;

		for (auto& it : m_components)
		{
			it->onUpdate();
		}
	}
}

//void GEntity::lastUpdate()
//{
	//for (auto& it : m_components)
	//{
	//	it->onLastUpdate();
	//}
//}

NS_G_END

