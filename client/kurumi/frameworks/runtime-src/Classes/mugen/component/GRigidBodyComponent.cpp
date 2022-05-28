#include "GRigidBodyComponent.h"
#include "mugen/GGameDef.h"

NS_G_BEGIN

GRigidBodyComponent::GRigidBodyComponent()
{
	isStatic = false;
	mass = 1.0f;
	invMass = fixedPoint(1.0f) / mass;
	linearDamping = 1.0f;
	gravityScale = 1.0f;
}

GRigidBodyComponent::~GRigidBodyComponent()
{
}

void GRigidBodyComponent::setMass(const fixedPoint& mass)
{
	this->mass = mass;
	this->invMass = fixedPoint(1.0f) / mass;
}

void GRigidBodyComponent::appendOffset(const fixedPoint& x, const fixedPoint& y)
{
	offsetOneFrame.x += x;
	offsetOneFrame.z += y;
}

void GRigidBodyComponent::appendOffsetOneSecond(const fixedPoint& x, const fixedPoint& y)
{
	this->appendOffset(x * LogicInterval, y * LogicInterval);
}

void GRigidBodyComponent::setBox(const GFixedVec3& origin, const GFixedVec3& size, const GFixedVec3& anchor)
{
	G_LOG("size %f - %f - %f", size.x.to_float(), size.y.to_float(), size.z.to_float());
	GFixedVec3 pos = origin / PHYSICS_PIXEL_TO_METER;
	auto newSize = size / PHYSICS_PIXEL_TO_METER;

	pos.x -= (anchor.x * newSize.x);
	pos.y -= (anchor.y * newSize.y);
	pos.z -= (anchor.z * newSize.z);

	this->position = pos;
	this->size = newSize;
}

void GRigidBodyComponent::setStaticBox(const GFixedVec2& origin, const GFixedVec2& size, const GFixedVec2& anchor)
{
	GFixedVec2 pos = origin / PHYSICS_PIXEL_TO_METER;
	auto newSize = size / PHYSICS_PIXEL_TO_METER;

	pos.x -= (anchor.x * newSize.x);
	pos.y -= (anchor.y * newSize.y);

	this->position.x = pos.x;
	this->position.y = 0.0f;
	this->position.z = pos.y;

	this->size.x = newSize.x;
	this->size.y = 0.0f;
	this->size.z = newSize.y;

	this->isStatic = true;
}

void GRigidBodyComponent::applyForce(const GFixedVec3& f)
{
	this->force += f;
}

void GRigidBodyComponent::applyImpulse(const GFixedVec3& impulse)
{
	this->linearVelocity += this->invMass * impulse;
}

NS_G_END
