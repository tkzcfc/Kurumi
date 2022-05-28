#pragma once

#include "GSystem.h"
#include "mugen/component/GRigidBodyComponent.h"

NS_G_BEGIN

class GPhysSystem : public GSystem
{
public:

	GPhysSystem();

	~GPhysSystem();

	void step();

	void debugDraw();

	void setMapBox(const GFixedVec2& min, const GFixedVec2& max);

private:

	bool collision(GRigidBodyComponent* component, const fixedPoint& offset, bool isx);
	
private:
	std::vector<GRigidBodyComponent*> m_static_bodies;
	std::vector<GRigidBodyComponent*> m_dynamic_bodies;
	// 重力
	GFixedVec3 m_gravity;

	GFixedVec2 m_mapMin;
	GFixedVec2 m_mapMax;
};

NS_G_END
