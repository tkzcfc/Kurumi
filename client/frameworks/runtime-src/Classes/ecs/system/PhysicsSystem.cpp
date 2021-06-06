#include "PhysicsSystem.h"
#include "ecs/utils/physics/GManifold.h"
#include "ecs/utils/CommonUtils.h"

//////////////////////////////////////////////////////////////////////////


// Acceleration
//    F = mA
// => A = F * 1/m

// Explicit Euler
// x += v * dt
// v += (1/m * F) * dt

// Semi-Implicit (Symplectic) Euler
// v += (1/m * F) * dt
// x += v * dt

// see http://www.niksula.hut.fi/~hkankaan/Homepages/gravity.html
static inline void IntegrateForces(BodyComponent *b, real dt)
{
	if (b->bodyType == GBodyType::STATIC_BODY)
		return;

	b->velocity += (b->force * b->im + PhysicsSystem::Gravity) * (dt * 0.5f);
	b->angularVelocity += b->torque * b->iI * (dt * 0.5f);
}

static void IntegrateVelocity(BodyComponent *b, real dt)
{
	if (b->bodyType == GBodyType::STATIC_BODY)
		return;

	b->position += b->velocity * dt;
	b->radians += b->angularVelocity * dt;
	PhysicsSystem::setRotation(b, b->radians);
	IntegrateForces(b, dt);
}



//////////////////////////////////////////////////////////////////////////

GVec2 PhysicsSystem::Gravity = GVec2(0.0f, -30.0f);

PhysicsSystem::PhysicsSystem(uint32_t iterations)
{
	m_iterations = iterations;
	m_bodies.reserve(32);
	m_contacts.reserve(32);
	m_contactsPool.reserve(32);
}

PhysicsSystem::~PhysicsSystem()
{
	for (auto& it : m_contactsPool)
	{
		delete it.m;
	}
	m_contactsPool.clear();
}

void PhysicsSystem::update(float32 dt)
{
	m_bodies.clear();
	m_contacts.clear();

	auto& entities = this->getEntities();

	for (auto& it : entities)
	{
		m_bodies.push_back(&it.getComponent<BodyComponent>());
	}

	// Generate new collision info
	for (uint32_t i = 0; i < m_bodies.size(); ++i)
	{
		auto A = m_bodies[i];
		for (uint32_t j = i + 1; j < m_bodies.size(); ++j)
		{
			auto B = m_bodies[j];
			if (A->bodyType == GBodyType::STATIC_BODY && B->bodyType == GBodyType::STATIC_BODY)
				continue;

			auto m = this->get();
			m->Reset(A, B);
			m->Solve();

			if (m->contact_count > 0)
				m_contacts.push_back(m);
			else
				this->revert(m);
		}
	}

	// Integrate forces
	for (uint32_t i = 0; i < m_bodies.size(); ++i)
		IntegrateForces(m_bodies[i], dt);

	// Initialize collision
	for (uint32_t i = 0; i < m_contacts.size(); ++i)
		m_contacts[i]->Initialize(Gravity, dt);

	// Solve collisions
	for (uint32_t j = 0; j < m_iterations; ++j)
		for (uint32_t i = 0; i < m_contacts.size(); ++i)
			m_contacts[i]->ApplyImpulse();

	// Integrate velocities
	for (uint32_t i = 0; i < m_bodies.size(); ++i)
		IntegrateVelocity(m_bodies[i], dt);

	// Correct positions
	for (uint32_t i = 0; i < m_contacts.size(); ++i)
	{
		m_contacts[i]->PositionalCorrection();
		this->revert(m_contacts[i]);
	}

	// Clear all forces
	for (uint32_t i = 0; i < m_bodies.size(); ++i)
	{
		auto *b = m_bodies[i];
		b->force.setzero();
		b->torque = 0;
	}
}

void PhysicsSystem::debugDraw()
{
	auto drawNode = CommonUtils::getDebugDraw(this->getWorld());
	if (drawNode == NULL)
		return;

	auto& entities = this->getEntities();
	for (auto& it : entities)
	{
		it.getComponent<BodyComponent>().shape->debugDraw(drawNode);
	}

	for (auto& m : m_contacts)
	{
		const auto& normal = m->normal;
		for (uint32_t j = 0; j < m->contact_count; ++j)
		{
			const auto& c = m->contacts[j];
			drawNode->drawLine(Vec2(c.x * PHYSICS_PIXEL_TO_METER, c.y * PHYSICS_PIXEL_TO_METER), Vec2(c.x * PHYSICS_PIXEL_TO_METER + normal.x * 10.0f, c.y * PHYSICS_PIXEL_TO_METER + normal.y * 10.0f), Color4F::GREEN);
			//drawNode->drawPoint(Vec2(c.x, c.y), 5.0f, Color4F::BLUE);
		}
	}
}


class GManifold* PhysicsSystem::get()
{
	for (auto& it : m_contactsPool)
	{
		if (it.free)
		{
			it.free = false;
			return it.m;
		}
	}

	auto m = new GManifold();

	CacheInfo info;
	info.m = m;
	info.free = false;
	m_contactsPool.emplace_back(info);

	return m;
}

void PhysicsSystem::revert(class GManifold* m)
{
	for (auto& it : m_contactsPool)
	{
		if (it.m == m)
		{
			it.free = true;
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void PhysicsSystem::applyForce(anax::Entity& entity, const GVec2& f)
{
	applyForce(&entity.getComponent<BodyComponent>(), f);
}

void PhysicsSystem::applyForce(BodyComponent* body, const GVec2& f)
{
	body->force += f;
}

void PhysicsSystem::applyImpulse(anax::Entity& entity, const GVec2& impulse, const GVec2& contactVector)
{
	applyImpulse(&entity.getComponent<BodyComponent>(), impulse, contactVector);
}

void PhysicsSystem::applyImpulse(BodyComponent* body, const GVec2& impulse, const GVec2& contactVector)
{
	body->velocity += body->im * impulse;
	body->angularVelocity += body->iI * cross(contactVector, impulse);
}

void PhysicsSystem::setStatic(anax::Entity& entity)
{
	setStatic(&entity.getComponent<BodyComponent>());
}

void PhysicsSystem::setStatic(BodyComponent* body)
{
	body->bodyType = GBodyType::STATIC_BODY;
	body->I = 0.0f;
	body->iI = 0.0f;
	body->m = 0.0f;
	body->im = 0.0f;
}

void PhysicsSystem::setRotation(anax::Entity& entity, real radians)
{
	setRotation(&entity.getComponent<BodyComponent>(), radians);
}

void PhysicsSystem::setRotation(BodyComponent* body, real radians)
{
	body->radians = radians;
	if(body->shape)
		body->shape->setRotation(radians);
}

void PhysicsSystem::setPosition(anax::Entity& entity, real posx, real posy)
{
	setPosition(&entity.getComponent<BodyComponent>(), posx, posy);
}

void PhysicsSystem::setPosition(BodyComponent* body, real posx, real posy)
{
	body->position.set(posx, posy);
}

void PhysicsSystem::createCircleBody(anax::Entity& entity, real radius, real density)
{
	G_ASSERT(entity.hasComponent<BodyComponent>() == false);
	auto& bodyCom = entity.addComponent<BodyComponent>();

	auto shape = new GCircle(radius);
	shape->body = &bodyCom;
	shape->setRotation(bodyCom.radians);

	computeMass(shape, &bodyCom, density);
	bodyCom.shape = shape;
}

void PhysicsSystem::createPolygonBody(anax::Entity& entity, GVec2 *vertices, uint32_t count, real density)
{
	G_ASSERT(entity.hasComponent<BodyComponent>() == false);
	auto& bodyCom = entity.addComponent<BodyComponent>();

	auto shape = new GPolygonShape();
	shape->body = &bodyCom;
	shape->set(vertices, count);
	shape->setRotation(bodyCom.radians);

	computeMass(shape, &bodyCom, density);
	bodyCom.shape = shape;
}

void PhysicsSystem::createBoxBody(anax::Entity& entity, real halfWidth, real halfHeight, real density)
{
	G_ASSERT(entity.hasComponent<BodyComponent>() == false);
	auto& bodyCom = entity.addComponent<BodyComponent>();

	auto shape = new GPolygonShape();
	shape->body = &bodyCom;
	shape->setBox(halfWidth, halfHeight);
	shape->setRotation(bodyCom.radians);

	computeMass(shape, &bodyCom, density);
	bodyCom.shape = shape;
}

void PhysicsSystem::computeMass(GCircle* shape, BodyComponent* body, real density)
{
	body->m = G_PI * shape->radius * shape->radius * density;
	body->im = (body->m) ? 1.0f / body->m : 0.0f;
	body->I = body->m * shape->radius * shape->radius;
	body->iI = (body->I) ? 1.0f / body->I : 0.0f;
}

void PhysicsSystem::computeMass(GPolygonShape* shape, BodyComponent* body, real density)
{
	// Calculate centroid and moment of interia
	GVec2 c(0.0f, 0.0f); // centroid
	real area = 0.0f;
	real I = 0.0f;
	const real k_inv3 = 1.0f / 3.0f;
	
	for (uint32_t i1 = 0; i1 < shape->m_vertexCount; ++i1)
	{
		// Triangle vertices, third vertex implied as (0, 0)
		GVec2 p1(shape->m_vertices[i1]);
		uint32_t i2 = i1 + 1 < shape->m_vertexCount ? i1 + 1 : 0;
		GVec2 p2(shape->m_vertices[i2]);
	
		real D = cross(p1, p2);
		real triangleArea = 0.5f * D;
	
		area += triangleArea;
	
		// Use area to weight the centroid average, not just vertex position
		c += triangleArea * k_inv3 * (p1 + p2);
	
		real intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
		real inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;
		I += (0.25f * k_inv3 * D) * (intx2 + inty2);
	}
	
	c *= 1.0f / area;
	
	// Translate vertices to centroid (make the centroid (0, 0)
	// for the polygon in model space)
	// Not really necessary, but I like doing this anyway
	for (uint32_t i = 0; i < shape->m_vertexCount; ++i)
		shape->m_vertices[i] -= c;
	
	body->m = density * area;
	body->im = (body->m) ? 1.0f / body->m : 0.0f;
	body->I = I * density;
	body->iI = body->I ? 1.0f / body->I : 0.0f;
}
