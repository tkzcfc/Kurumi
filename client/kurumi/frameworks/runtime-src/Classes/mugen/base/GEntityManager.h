#pragma once

#include "GEntity.h"

NS_G_BEGIN

class GEntityManager
{
public:

	GEntityManager();

	~GEntityManager();

	static GEntityManager* getInstance();

	static void destroy();

public:

	uint32_t getEntityCount();

	template<typename T = GEntity>
	T* newEntity()
	{
		auto ptr = new T;
		this->push(ptr);
		return ptr;
	}

	void skill(GEntity* pEntity);

	void clear();

	void update();

	//void lastUpdate();

	void getAllComponent(const std::string& name, std::vector<GComponent*>& components);

	GEntity* getEntity(uint32_t id);

private:

	void push(GEntity* pEntity);

private:
		
	G_SYNTHESIZE_READONLY_BY_REF(std::vector<GEntity*>, m_entities, Entities);

	std::vector<GEntity*> m_deadEntities;

	static GEntityManager* instance;
};

NS_G_END
