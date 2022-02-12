#pragma once

#include "mugen/base/GComponent.h"
#include "mugen/GGameDef.h"

NS_G_BEGIN

class GCollisionComponent : public GComponent
{
public:

	G_DEFINE_COMPONENT(GCollisionComponent);

	GCollisionComponent();

	virtual ~GCollisionComponent();
	
	bool canCollide(GCollisionComponent* other);

	void onCollision(GCollisionComponent* other);

public:
	// 自己的分类类型
	G_SYNTHESIZE(uint32_t, m_categoryBits, CategoryBits);
	// 接受攻击的类型
	G_SYNTHESIZE(uint32_t, m_maskBits, MaskBits);

	// 当前所属阵营
	G_SYNTHESIZE(GCampEnums, m_campEnums, CampEnums);
};


NS_G_END
