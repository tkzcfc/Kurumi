#include "Buff.h"
#include "ecs/system/UUIDSystem.h"


Buff::Buff(anax::World* world, GUUID creator)
	: m_creator(creator)
	, m_pWorld(world)
	, m_removeTag(false)
{
	G_ASSERT(m_pWorld != NULL);
}

Buff::~Buff()
{}

bool Buff::canRemove()
{
	if (m_removeTag)
		return false;

	if (m_creator != INVALID_UUID)
	{
		return m_pWorld->getSystem<UUIDSystem>()->query(m_creator);
	}
	return true;
}

void Buff::remove()
{
	m_removeTag = true;
}

