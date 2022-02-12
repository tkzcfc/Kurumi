#include "GComponent.h"
#include "GEntity.h"

NS_G_BEGIN


GComponent::GComponent()
	: m_pEntity(NULL)
{}

GComponent::~GComponent()
{}

void GComponent::addComponent(GComponent* component)
{
	m_pEntity->addComponent(component);
}

void GComponent::removeComponent(const std::string& name)
{
	m_pEntity->removeComponent(name);
}

GComponent* GComponent::getComponent(const std::string& name)
{
	return m_pEntity->getComponent(name);
}

GEntity* GComponent::getEntity()
{
	return m_pEntity;
}

void GComponent::serialize(GByteBuffer& byteBuffer)
{
	GObject::serialize(byteBuffer);
	byteBuffer.writeString(this->name());
}

bool GComponent::deserialize(GByteBuffer& byteBuffer)
{
	do
	{
		G_BREAK_IF(!GObject::deserialize(byteBuffer));
		
		std::string name;
		G_BREAK_IF(!byteBuffer.getString(name));

		return true;
	} while (0);
	return false;
}

NS_G_END

