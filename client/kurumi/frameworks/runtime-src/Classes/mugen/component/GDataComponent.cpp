#include "GDataComponent.h"
#include "GStaticDataComponent.h"

NS_G_BEGIN


GDataComponent ::GDataComponent ()
{
}

GDataComponent ::~GDataComponent ()
{
}
void GDataComponent::onAdd()
{
	build();
}

void GDataComponent::build()
{
	auto pStaticData = G_GetComponent(this, GStaticDataComponent);
	G_ASSERT(pStaticData);

	this->moveSpeed = pStaticData->moveSpeed;
	this->force = pStaticData->force;
	this->impulse = pStaticData->impulse;
	
}

NS_G_END

