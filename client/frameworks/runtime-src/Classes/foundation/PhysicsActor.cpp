#include "PhysicsActor.h"
#include "foundation/GameWorldBase.h"
#include "ecs/system/Box2DSystem.h"


PhysicsActor::PhysicsActor(GameWorldBase* world)
	: Actor(world)
{
}

PhysicsActor::~PhysicsActor()
{
}

PhysicsActor* PhysicsActor::create(GameWorldBase* world)
{
	PhysicsActor* actor = new PhysicsActor(world);
	if (actor && actor->init())
	{
		actor->autorelease();
		return actor;
	}
	CC_SAFE_DELETE(actor);
	return actor;
}

void PhysicsActor::killEntity()
{
	if (m_gameWorld != NULL && m_entity.hasComponent<Box2DComponent>())
	{
		auto sys = m_gameWorld->getWorld()->getSystem<Box2DSystem>();
		if (sys)
		{
			sys->addDiscardB2Body(m_entity.getComponent<Box2DComponent>().m_body);
		}
	}
	Actor::killEntity();
}

void PhysicsActor::syncPhysicsTransform(float x, float y, float angle)
{
	Node::setPosition(x, y);
	Node::setRotation(CC_RADIANS_TO_DEGREES(angle));
}

// Override the setters and getters to always reflect the body's properties.
const Vec2& PhysicsActor::getPosition() const
{
	return getPosFromPhysics();
}

void PhysicsActor::getPosition(float* x, float* y) const
{
	if (x == nullptr || y == nullptr) {
		return;
	}
	const Vec2& pos = getPosFromPhysics();
	*x = pos.x;
	*y = pos.y;
}

float PhysicsActor::getPositionX() const
{
	return getPosFromPhysics().x;
}

float PhysicsActor::getPositionY() const
{
	return getPosFromPhysics().y;
}

Vec3 PhysicsActor::getPosition3D() const
{
	Vec2 pos = getPosFromPhysics();
	return Vec3(pos.x, pos.y, 0);
}

const Vec2& PhysicsActor::getPosFromPhysics() const
{
	static Vec2 s_physicPosion;

	if (false == m_entity.hasComponent<Box2DComponent>())
	{
		return Node::getPosition();
	}

	auto &component = m_entity.getComponent<Box2DComponent>();
	b2Body* pB2Body = component.m_body;

	b2Vec2 pos = pB2Body->GetPosition();
	float x = pos.x * BOX2D_PIXEL_TO_METER;
	float y = pos.y * BOX2D_PIXEL_TO_METER;
	s_physicPosion.set(x, y);

	return s_physicPosion;
}

void PhysicsActor::setPosition(float x, float y)
{
	if (false == m_entity.hasComponent<Box2DComponent>())
	{
		Node::setPosition(x, y);
		return;
	}
	auto &component = m_entity.getComponent<Box2DComponent>();
	b2Body* pB2Body = component.m_body;

	float angle = pB2Body->GetAngle();
	pB2Body->SetTransform(b2Vec2(x / BOX2D_PIXEL_TO_METER, y / BOX2D_PIXEL_TO_METER), angle);
}

void PhysicsActor::setPosition(const Vec2 &pos)
{
	this->setPosition(pos.x, pos.y);
}

void PhysicsActor::setPositionX(float x)
{
	this->setPosition(x, getPositionY());
}

void PhysicsActor::setPositionY(float y)
{
	this->setPosition(this->getPositionX(), y);
}

void PhysicsActor::setPosition3D(const Vec3& position)
{
	this->setPosition(position.x, position.y);
}

float PhysicsActor::getRotation() const
{
	if (false == m_entity.hasComponent<Box2DComponent>())
	{
		return Node::getRotation();
	}
	auto &component = m_entity.getComponent<Box2DComponent>();
	b2Body* pB2Body = component.m_body;

	return CC_RADIANS_TO_DEGREES(pB2Body->GetAngle());
}

void PhysicsActor::setRotation(float fRotation)
{
	if (false == m_entity.hasComponent<Box2DComponent>())
	{
		Node::setRotation(fRotation);
		return;
	}

	auto &component = m_entity.getComponent<Box2DComponent>();
	b2Body* pB2Body = component.m_body;

	b2Vec2 p = pB2Body->GetPosition();
	float radians = CC_DEGREES_TO_RADIANS(fRotation);
	pB2Body->SetTransform(p, radians);
}





