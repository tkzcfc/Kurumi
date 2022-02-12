#include "GPhysSystem.h"
#include "mugen/logic/GGameWorld.h"

NS_G_BEGIN


GPhysSystem::GPhysSystem()
{
	// 重力设置
	m_gravity = GFixedVec3(0.0f, -9.8f * 3.0f, 0.0f);
	m_static_bodies.reserve(10);
	m_dynamic_bodies.reserve(10);
}

GPhysSystem::~GPhysSystem()
{}

void GPhysSystem::step()
{
	doFilter("GRigidBodyComponent");

	if (m_cacheComponents.empty()) 
		return;

	const auto& dt = LogicInterval;
	const fixedPoint one(1.0f);

	m_static_bodies.clear();
	m_dynamic_bodies.clear();

	GRigidBodyComponent* rigidBodyCom = NULL;
	for (auto& it : m_cacheComponents)
	{
		rigidBodyCom = (GRigidBodyComponent*)it;
		if (rigidBodyCom->isStatic)
			m_static_bodies.push_back(rigidBodyCom);
		else
			m_dynamic_bodies.push_back(rigidBodyCom);
	}

	for (auto b : m_dynamic_bodies)
	{
		// Integrate velocities
		b->linearVelocity += dt * b->invMass * (b->gravityScale * b->mass * m_gravity + b->force);

		// Apply damping
		b->linearVelocity *= one / (one + dt * b->linearDamping);
		
		GFixedVec3 df = b->linearVelocity + b->offsetOneFrame;
		df = df * dt;

		b->offsetOneFrame.setZero();
		
		// Penetration correction
		if (!df.x.isZero() && !collision(b, df.x, 0.0f))
		{
			b->position.x += df.x;
		}
		if (!df.z.isZero() && !collision(b, 0.0f, df.z))
		{
			b->position.z += df.z;
		}

		b->position.y += df.y;
		if (b->position.y < 0.0f)
		{
			b->position.y = 0.0f;
			b->linearVelocity.y.setZero();
		}

		// Clear force
		b->force.setZero();
	}
}

bool GPhysSystem::collision(GRigidBodyComponent* component, const fixedPoint& dx, const fixedPoint& dz)
{
	auto minx = component->position.x + dx;
	auto maxx = minx + component->size.x;
	auto minz = component->position.z + dz;
	auto maxz = minz + dz + component->size.z;

	bool mark = false;
	for (auto& it : m_static_bodies)
	{
		if (minx < it->position.x + it->size.x &&  it->position.x < maxx &&
			minz < it->position.z + it->size.z && it->position.z < maxz)
		{
			mark = true;
			if (dz < 0.0f)
			{
				component->position.z = it->position.z + it->size.z;
				component->linearVelocity.z.setZero();
			}
			else if (dz > 0.0f)
			{
				component->position.z = it->position.z - component->size.z;
				component->linearVelocity.z.setZero();
			}
			else if (dx < 0.0f)
			{
				component->position.x = it->position.x + it->size.x;
				component->linearVelocity.x.setZero();
			}
			else if (dx > 0.0f)
			{
				component->position.x = it->position.x - component->size.x;
				component->linearVelocity.x.setZero();
			}
			break;
		}
	}
	return mark;
}

void GPhysSystem::debugDraw()
{	
	auto drawNode = GGameWorld::getInstance()->getMapLayer()->getDrawNode();

	for (auto it : m_static_bodies)
	{
		auto x = it->position.x.to_float() * PHYSICS_PIXEL_TO_METER;
		auto y = it->position.y.to_float() * PHYSICS_PIXEL_TO_METER;
		auto z = it->position.z.to_float() * PHYSICS_PIXEL_TO_METER;

		auto w = it->size.x.to_float() * PHYSICS_PIXEL_TO_METER;
		auto zh = it->size.z.to_float() * PHYSICS_PIXEL_TO_METER;
		auto yh = it->size.y.to_float() * PHYSICS_PIXEL_TO_METER;

		if (zh > 1.0f && w > 1.0f)
		{
			Vec2 origin(x, z);
			Vec2 destination(origin.x + w, origin.y + zh);

			drawNode->drawSolidRect(origin, destination, Color4F(1.0f, 0.0f, 0.0f, 0.2));
			drawNode->drawRect(origin, destination, Color4F(1.0f, 0.0f, 0.0f, 0.8));
		}
		if (yh > 1.0f && w > 1.0f)
		{
			Vec2 origin(x, y + z);
			Vec2 destination(origin.x + w, origin.y + yh);

			drawNode->drawSolidRect(origin, destination, Color4F(0.0f, 0.8f, 0.0f, 0.1));
			drawNode->drawRect(origin, destination, Color4F(0.0f, 0.8f, 0.0f, 0.4));
		}
	}

	for (auto it : m_dynamic_bodies)
	{
		auto x = it->position.x.to_float() * PHYSICS_PIXEL_TO_METER;
		auto y = it->position.y.to_float() * PHYSICS_PIXEL_TO_METER;
		auto z = it->position.z.to_float() * PHYSICS_PIXEL_TO_METER;

		auto w = it->size.x.to_float() * PHYSICS_PIXEL_TO_METER;
		auto zh = it->size.z.to_float() * PHYSICS_PIXEL_TO_METER;
		auto yh = it->size.y.to_float() * PHYSICS_PIXEL_TO_METER;

		if(zh > 1.0f)
		{
			Vec2 origin(x, z);
			Vec2 destination(origin.x + w, origin.y + zh);

			drawNode->drawSolidRect(origin, destination, Color4F(0.3f, 0.3f, 0.8f, 0.2));
			drawNode->drawRect(origin, destination, Color4F(0.3f, 0.3f, 0.8f, 0.8));
		}
		if (yh > 1.0f)
		{
			Vec2 origin(x, y + z);
			Vec2 destination(origin.x + w, origin.y + yh);
			drawNode->drawSolidRect(origin, destination, Color4F(0.0f, 0.8f, 0.0f, 0.1));
			drawNode->drawRect(origin, destination, Color4F(0.0f, 0.8f, 0.0f, 0.4));
		}
	}
}

NS_G_END
