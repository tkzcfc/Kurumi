#include "SIMPhysSystem.h"
#include "ecs/utils/CommonUtils.h"


SIMPhysSystem::SIMPhysSystem()
{
	m_gravity = GVec2(0.0f, -50.0f);
	m_static_bodies.reserve(30);
	m_dynamic_bodies.reserve(30);
}

void SIMPhysSystem::setGravity(const GVec2& gravity)
{
	m_gravity = gravity;
}

void SIMPhysSystem::update(float dt)
{
	SIMPhysComponent* simComponent;

	m_static_bodies.clear();
	m_dynamic_bodies.clear();

	auto& entities = this->getEntities();
	for (auto& it : entities)
	{
		simComponent = &it.getComponent<SIMPhysComponent>();
		if (simComponent->isStatic)
			m_static_bodies.push_back(simComponent);
		else
			m_dynamic_bodies.push_back(simComponent);
	}

	for (auto b : m_dynamic_bodies)
	{
		// 简化运算,直接将质量视为1
		// Integrate velocities
		//b->linearVelocity += dt * b->invMass * (b->gravityScale * b->mass * gravity + b->force);
		b->linearVelocity += dt * (b->gravityScale * m_gravity + b->force);

		// 简化运算,忽略阻尼
		// Apply damping
		//b->linearVelocity *= 1.0f / (1.0f + dt * b->linearDamping);

		GVec2 df = b->linearVelocity * dt;

		// Penetration correction
		if (df.x != 0.0f && false == collision(b, df.x, 0.0f))
		{
			b->position.x += df.x;
		}
		if (df.y != 0.0f && false == collision(b, 0.0f, df.y))
		{
			b->position.y += df.y;
		}

		b->force.setzero();
	}
}

//if e.x + dx < e2.x + e2.w and e2.x < e.x + dx + e.w and
//	e.y + dy < e2.y + e2.h and e2.y < e.y + dy + e.h then

bool SIMPhysSystem::collision(SIMPhysComponent* component, float32 dx, float32 dy)
{
	float32 minx = component->position.x + dx;
	float32 maxx = minx + component->size.x;
	float32 miny = component->position.y + dy;
	float32 maxy = miny + dy + component->size.y;
	
	bool mark = false;
	for (auto& it : m_static_bodies)
	{
		if(minx < it->position.x + it->size.x &&  it->position.x < maxx && 
			miny < it->position.y + it->size.y && it->position.y < maxy)
		{
			mark = true;
			if (dy < 0.0f)
			{
				component->position.y = it->position.y + it->size.y;
				component->linearVelocity.y = 0;
			}
			else if (dy > 0.0f)
			{
				component->position.y = it->position.y - component->size.y;
				component->linearVelocity.y = 0;
			}
			else if (dx < 0.0f)
			{
				component->position.x = it->position.x + it->size.x;
				component->linearVelocity.x = 0;
			}
			else if (dx > 0.0f)
			{
				component->position.x = it->position.x - component->size.x;
				component->linearVelocity.x = 0;
			}
			break;
		}
	}
	return mark;
}


void SIMPhysSystem::debugDraw()
{
#if G_TARGET_CLIENT
	auto drawNode = CommonUtils::getDebugDraw(this->getWorld());
	
	if (drawNode == NULL)
		return;

	for (auto& it : m_static_bodies)
	{
		drawNode->drawRect(Vec2(it->position.x, it->position.y), Vec2(it->position.x + it->size.x, it->position.y + it->size.y), Color4F::RED);
	}
	for (auto& it : m_dynamic_bodies)
	{
		drawNode->drawRect(Vec2(it->position.x, it->position.y), Vec2(it->position.x + it->size.x, it->position.y + it->size.y), Color4F::BLUE);
	}
#endif
}

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

void SIMPhysSystem::createBox(anax::Entity& entity, const GVec2& origin, const GVec2& size, const GVec2& anchor)
{
	G_ASSERT(entity.hasComponent<SIMPhysComponent>() == false);

	GVec2 pos = origin;
	pos.x -= (anchor.x * size.x);
	pos.y -= (anchor.y * size.y);

	auto& component = entity.addComponent<SIMPhysComponent>();
	component.position = pos;
	component.size = size;
}


