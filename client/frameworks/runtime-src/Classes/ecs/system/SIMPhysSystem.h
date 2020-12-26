#pragma once

#include "ecs/components/SIMPhysComponent.h"

class SIMPhysSystem : public anax::System<anax::Requires<SIMPhysComponent>>
{
public:
	SIMPhysSystem(const GVec2& gravity);

	void update(float dt);

	bool collision(SIMPhysComponent* component, float32 dx, float32 dy);

#if G_TARGET_CLIENT
	void debugDraw(DrawNode* drawNode);
#endif

public:

	static void applyForce(anax::Entity& entity, const GVec2& f);

	static void applyForce(SIMPhysComponent* component, const GVec2& f);

	static void applyImpulse(anax::Entity& entity, const GVec2& impulse);

	static void applyImpulse(SIMPhysComponent* component, const GVec2& impulse);

	static void createBox(anax::Entity& entity, const GVec2& origin, const GVec2& size, const GVec2& anchor);
	
private:

	std::vector<SIMPhysComponent*> m_static_bodies;
	std::vector<SIMPhysComponent*> m_dynamic_bodies;
	GVec2 m_gravity;
};
