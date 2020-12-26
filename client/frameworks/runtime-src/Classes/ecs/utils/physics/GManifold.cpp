#include "GManifold.h"
#include "ecs/components/BodyComponent.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/system/PhysicsSystem.h"
#include "ecs/utils/physics/GCollision.h"

void GManifold::Reset(class BodyComponent* a, class BodyComponent* b)
{
	bodyA = a;
	bodyB = b;
}

void GManifold::Solve(void)
{
	GCollision::Dispatch[bodyA->shape->getType()][bodyB->shape->getType()](this, bodyA, bodyB);
}

void GManifold::Initialize(const GVec2& gravity, float dt)
{
	// Calculate average restitution
	e = std::min(bodyA->restitution, bodyB->restitution);

	// Calculate static and dynamic friction
	sf = std::sqrt(bodyA->staticFriction * bodyB->staticFriction);
	df = std::sqrt(bodyA->dynamicFriction * bodyB->dynamicFriction);

	for (uint32_t i = 0; i < contact_count; ++i)
	{
		// Calculate radii from COM to contact
		GVec2 ra = contacts[i] - bodyA->position;
		GVec2 rb = contacts[i] - bodyB->position;

		GVec2 rv = bodyB->velocity + cross(bodyB->angularVelocity, rb) -
			bodyA->velocity - cross(bodyA->angularVelocity, ra);


		// Determine if we should perform a resting collision or not
		// The idea is if the only thing moving this object is gravity,
		// then the collision should be performed without any restitution
		if (rv.lenSqr() < (dt * gravity).lenSqr() + G_EPSILON)
			e = 0.0f;
	}
}

void GManifold::ApplyImpulse(void)
{
	// Early out and positional correct if both objects have infinite mass
	if (equal_real(bodyA->im + bodyB->im, 0))
	{
		InfiniteMassCorrection();
		return;
	}
	for (uint32_t i = 0; i < contact_count; ++i)
	{
		// Calculate radii from COM to contact
		GVec2 ra = contacts[i] - bodyA->position;
		GVec2 rb = contacts[i] - bodyB->position;

		// Relative velocity
		GVec2 rv = bodyB->velocity + cross(bodyB->angularVelocity, rb) -
			bodyA->velocity - cross(bodyA->angularVelocity, ra);

		// Relative velocity along the normal
		real contactVel = dot(rv, normal);

		// Do not resolve if velocities are separating
		if (contactVel > 0)
			return;

		real raCrossN = cross(ra, normal);
		real rbCrossN = cross(rb, normal);
		real invMassSum = bodyA->im + bodyB->im + sqr_real(raCrossN) * bodyA->iI + sqr_real(rbCrossN) * bodyB->iI;

		// Calculate impulse scalar
		real j = -(1.0f + e) * contactVel;
		j /= invMassSum;
		j /= (real)contact_count;

		// Apply impulse
		GVec2 impulse = normal * j;
		PhysicsSystem::applyImpulse(bodyA, -impulse, ra);
		PhysicsSystem::applyImpulse(bodyB, impulse, rb);

		// Friction impulse
		rv = bodyB->velocity + cross(bodyB->angularVelocity, rb) -
			bodyA->velocity - cross(bodyA->angularVelocity, ra);

		GVec2 t = rv - (normal * dot(rv, normal));
		t.normalize();

		// j tangent magnitude
		real jt = -dot(rv, t);
		jt /= invMassSum;
		jt /= (real)contact_count;

		// Don't apply tiny friction impulses
		if (equal_real(jt, 0.0f))
			return;

		// Coulumb's law
		GVec2 tangentImpulse;
		if (std::abs(jt) < j * sf)
			tangentImpulse = t * jt;
		else
			tangentImpulse = t * -j * df;

		// Apply friction impulse
		PhysicsSystem::applyImpulse(bodyA, -tangentImpulse, ra);
		PhysicsSystem::applyImpulse(bodyB, tangentImpulse, rb);
	}
}

void GManifold::PositionalCorrection(void)
{
	const real k_slop = 0.05f; // Penetration allowance
	const real percent = 0.4f; // Penetration percentage to correct
	GVec2 correction = (std::max(penetration - k_slop, 0.0f) / (bodyA->im + bodyB->im)) * normal * percent;
	bodyA->position -= correction * bodyA->im;
	bodyB->position += correction * bodyB->im;
}

void GManifold::InfiniteMassCorrection(void)
{
	bodyA->velocity.setzero();
	bodyB->velocity.setzero();
}
