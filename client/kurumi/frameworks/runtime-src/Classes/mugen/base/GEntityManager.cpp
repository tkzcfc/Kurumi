#include "GEntityManager.h"

NS_G_BEGIN

static uint32_t entity_id_seed = 0;

GEntityManager* GEntityManager::instance = NULL;

GEntityManager::GEntityManager()
{
	m_entities.reserve(1000);
	m_deadEntities.reserve(50);
}

GEntityManager::~GEntityManager()
{}

GEntityManager* GEntityManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new GEntityManager();
	}
	return instance;
}

void GEntityManager::destroy()
{
	if (instance)
	{
		delete instance;
		instance = NULL;
	}
}

uint32_t GEntityManager::getEntityCount()
{
	return (uint32_t)m_entities.size();
}

void GEntityManager::skill(GEntity* pEntity)
{
	m_deadEntities.push_back(pEntity);
}

void GEntityManager::push(GEntity* pEntity)
{
	entity_id_seed++;
	pEntity->setId(entity_id_seed);
	m_entities.push_back(pEntity);
}

void GEntityManager::clear()
{
	m_deadEntities.clear();

	for (auto it : m_entities)
	{
		delete it;
	}
	m_entities.clear();
	entity_id_seed = 0;
}

void GEntityManager::update()
{
	for (auto& it : m_entities)
	{
		it->update();
	}

	if (!m_deadEntities.empty())
	{
		for (auto ptr : m_deadEntities)
		{
			for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
			{
				if (*it == ptr)
				{
					m_entities.erase(it);
					break;
				}
			}

			delete ptr;
		}
		m_deadEntities.clear();
	}
}

//void GEntityManager::lastUpdate()
//{
//	for (auto& it : m_entities)
//	{
//		it->lastUpdate();
//	}
//}

void GEntityManager::getAllComponent(const std::string& name, std::vector<GComponent*>& components)
{
	components.clear();
	components.reserve(m_entities.size());
	
	for (auto it : m_entities)
	{
		auto ptr = it->getComponent(name);
		if (ptr)
		{
			components.push_back(ptr);
		}
	}
}

GEntity* GEntityManager::getEntity(uint32_t id)
{
	for (auto it : m_entities)
	{
		if (it->getId() == id)
		{
			return it;
		}
	}
	return NULL;
}

NS_G_END

