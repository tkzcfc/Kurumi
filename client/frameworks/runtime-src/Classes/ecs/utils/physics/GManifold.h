#pragma once

#include "ecs/anaxHelper.h"

class GManifold
{
public:
	GManifold()
		: bodyA(NULL)
		, bodyB(NULL)
	{}

	void Reset(class BodyComponent* a, class BodyComponent* b);

	void Solve(void);                 // Generate contact information
	void Initialize(const GVec2& gravity, float dt);            // Precalculations for impulse solving
	void ApplyImpulse(void);          // Solve impulse and apply
	void PositionalCorrection(void);  // Naive correction of positional penetration
	void InfiniteMassCorrection(void);

	class BodyComponent* bodyA;
	class BodyComponent* bodyB;

	real penetration;     // Depth of penetration from collision
	GVec2 normal;          // From A to B
	GVec2 contacts[2];     // Points of contact during collision
	uint32_t contact_count; // Number of contacts that occured during collision
	real e;               // Mixed restitution
	real df;              // Mixed dynamic friction
	real sf;              // Mixed static friction
};
