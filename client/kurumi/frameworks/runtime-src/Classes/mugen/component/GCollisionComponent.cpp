#include "GCollisionComponent.h"

NS_G_BEGIN


GCollisionComponent::GCollisionComponent()
{
	// 默认所属阵营
	m_campEnums = GCampEnums::CAMP_1;

	// 默认自己为role
	m_categoryBits = GCategoryEnums::ROLE;

	// 接受所有类型的碰撞
	m_maskBits = GCategoryEnums::ROLE | GCategoryEnums::FRIEND_BUFF | GCategoryEnums::HURT_BUFF;
}

GCollisionComponent::~GCollisionComponent()
{
}

bool GCollisionComponent::canCollide(GCollisionComponent* other)
{
	if (G_BIT_GET(this->getCategoryBits(), other->getMaskBits()))
	{
		// 增益型buff，只能碰到同阵营的
		if (G_BIT_EQUAL(this->getCategoryBits(), GCategoryEnums::FRIEND_BUFF))
		{
			// 相同阵营
			return this->getCampEnums() == other->getCampEnums();
		}
		return this->getCampEnums() != other->getCampEnums();
	}

	return false;
}

void GCollisionComponent::onCollision(GCollisionComponent* other)
{
}

NS_G_END
