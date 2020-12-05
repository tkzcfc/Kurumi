#include "GBody.h"
#include "GShape.h"

GBody::GBody(GShape *shape_, uint32_t x, uint32_t y)
	: shape(shape_->clone())
{
	shape->body = this;
	position.set((real)x, (real)y);
	velocity.set(0, 0);
	angularVelocity = 0;
	torque = 0;
	orient = 0;
	force.set(0, 0);
	staticFriction = 0.5f;
	dynamicFriction = 0.3f;
	restitution = 0.2f;
	shape->initialize();
}

void GBody::setOrient(real radians)
{
	orient = radians;
	shape->setOrient(radians);
}

