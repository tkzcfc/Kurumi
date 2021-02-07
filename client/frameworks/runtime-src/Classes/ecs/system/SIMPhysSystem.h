#pragma once

#include "ecs/components/SIMPhysComponent.h"

class SIMPhysSystem : public anax::System<anax::Requires<SIMPhysComponent>>
{
public:
	SIMPhysSystem();

	void setGravity(const GVec2& gravity);

	void update(float dt);

	bool collision(SIMPhysComponent* component, float32 dx, float32 dy);

	void debugDraw();

public:

	static G_FORCEINLINE void applyForce(anax::Entity& entity, const GVec2& f);

	static G_FORCEINLINE void applyForce(SIMPhysComponent* component, const GVec2& f);

	static G_FORCEINLINE void applyImpulse(anax::Entity& entity, const GVec2& impulse);

	static G_FORCEINLINE void applyImpulse(SIMPhysComponent* component, const GVec2& impulse);

	static void createBox(anax::Entity& entity, const GVec2& origin, const GVec2& size, const GVec2& anchor);
	
private:

	std::vector<SIMPhysComponent*> m_static_bodies;
	std::vector<SIMPhysComponent*> m_dynamic_bodies;
	GVec2 m_gravity;
};



void SIMPhysSystem::applyForce(anax::Entity& entity, const GVec2& f)
{
	applyForce(&entity.getComponent<SIMPhysComponent>(), f);
}

void SIMPhysSystem::applyForce(SIMPhysComponent* component, const GVec2& f)
{
	component->force += f;
}

void SIMPhysSystem::applyImpulse(anax::Entity& entity, const GVec2& impulse)
{
	applyImpulse(&entity.getComponent<SIMPhysComponent>(), impulse);
}

void SIMPhysSystem::applyImpulse(SIMPhysComponent* component, const GVec2& impulse)
{
	// 简化运算,直接将质量视为1
	//component->linearVelocity += body->im * impulse;
	component->linearVelocity += impulse;
}