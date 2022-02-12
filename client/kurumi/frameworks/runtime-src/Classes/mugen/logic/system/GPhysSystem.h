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

private:

	bool collision(GRigidBodyComponent* component, const fixedPoint& dx, const fixedPoint& dy);
	
private:
	std::vector<GRigidBodyComponent*> m_static_bodies;
	std::vector<GRigidBodyComponent*> m_dynamic_bodies;
	// 重力
	GFixedVec3 m_gravity;
};

NS_G_END
