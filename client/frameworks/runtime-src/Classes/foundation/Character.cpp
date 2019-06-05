#include "Character.h"
#include "ecs/components/ArmatureComponent.h"
#include "ecs/components/Box2DComponent.h"
#include "ecs/components/UpdateComponent.h"
#include "ecs/components/MapFollowComponent.h"
#include "ecs/system/Box2DSystem.h"
#include "foundation/GameMacro.h"
#include "foundation/ParticleSystemHelper.h"

Character::Character(GameWorld* world)
	: Actor(world)
	, m_armature(NULL)
	, m_categoryBits(BOX2D_FILTER_MASK::B2DM_PLAYER)
{
	// 碰撞组件
	ArmatureCollisionComponent& collisionComponent = m_entity.addComponent<ArmatureCollisionComponent>();

	// 碰撞过滤器
	CollisionFilterComponent& filterComponent = m_entity.addComponent<CollisionFilterComponent>();
	filterComponent.m_collisionEnable = true;
}

Character::~Character()
{}

Character* Character::create(GameWorld* world)
{
	Character* character = new Character(world);
	if (character && character->init())
	{
		character->autorelease();
		return character;
	}
	CC_SAFE_DELETE(character);
	return character;
}

bool Character::init()
{
	if (Actor::init() == false)
		return false;
	return true;
}

void Character::killEntity()
{
	if (m_gameWorld != NULL && m_entity.hasComponent<Box2DComponent>())
	{
		auto sys = m_gameWorld->getWorld()->getSystem<Box2DSystem>();
		if (sys)
		{
			auto body = m_entity.getComponent<Box2DComponent>().m_body;
			if (body)
			{
				auto fixtureList = body->GetFixtureList();
				for (auto it = fixtureList; it != NULL; it = fixtureList->GetNext())
				{
					it->SetUserData(NULL);
				}
				sys->addDiscardB2Body(body);
			}
		}
	}
	Actor::killEntity();
}

void Character::loadArmature(const std::string& filepath)
{
	CC_ASSERT(m_armature == NULL);

	m_armature = cocostudio::Armature::create(filepath);
	CC_ASSERT(m_armature != NULL);
	this->addChild(m_armature);

	// 动画组件
	ArmatureComponent& armatureComponent = m_entity.addComponent<ArmatureComponent>();
	armatureComponent.m_armature = m_armature;
	armatureComponent.m_owner = this;
	armatureComponent.m_armature->getAnimation()->playWithIndex(0);

	changeParticleSystemPositionType(m_armature, (int)ParticleSystem::PositionType::GROUPED);
	this->m_entity.activate();
}

void Character::enableBox2DComponent(const Vec2& bodyPos, const Size& characterSize)
{
	CC_ASSERT(m_entity.isValid());
	CC_ASSERT(m_entity.hasComponent<Box2DComponent>() == false);
	
	Box2DSystem* box2DSystem = m_gameWorld->getWorld()->getSystem<Box2DSystem>();
	CC_ASSERT(box2DSystem != NULL);

	if (box2DSystem == NULL)
	{
		return;
	}

	b2BodyDef bodydef;
	bodydef.bullet = false;
	bodydef.allowSleep = true;
	bodydef.fixedRotation = true;
	bodydef.type = b2_dynamicBody;
	bodydef.position.x = bodyPos.x / BOX2D_PIXEL_TO_METER;
	bodydef.position.y = bodyPos.y / BOX2D_PIXEL_TO_METER;

	b2Body* body = box2DSystem->getBox2DWorld()->CreateBody(&bodydef);

	const float box_w = characterSize.width / BOX2D_PIXEL_TO_METER;
	const float box_h = characterSize.height / BOX2D_PIXEL_TO_METER;

	b2Filter filter;
	filter.groupIndex = -1;
	filter.categoryBits = m_categoryBits;
	filter.maskBits = BOX2D_FILTER_MASK::B2DM_GROUND | BOX2D_FILTER_MASK::B2DM_SIDE_WALL;

	// 实体矩形
	b2PolygonShape shape;
	shape.SetAsBox(box_w, box_h, b2Vec2(0.0f, box_h), 0.0f);
	b2FixtureDef fixdef;
	fixdef.shape = &shape;
	fixdef.userData = this;
	fixdef.filter = filter;
	fixdef.friction = 0.0f;
	b2Fixture* fixture = body->CreateFixture(&fixdef);

	//// 脚底碰撞器
	//shape.SetAsBox(box_w, 10.0f / BOX2D_PIXEL_TO_METER, b2Vec2(0.0f, 0.0f), 0.0f);
	//fixdef.shape = &shape;
	//fixdef.userData = this;
	//fixdef.filter = filter;
	//fixdef.isSensor = true;
	//body->CreateFixture(&fixdef);

	// 物理组件
	Box2DComponent& box2DComponent = m_entity.addComponent<Box2DComponent>();
	box2DComponent.m_body = body;

	this->m_entity.activate();
}

void Character::setPositionAndSyncPhysicsTransform(const Vec2& inPos)
{
	this->setPosition(inPos);

	if (this->m_entity.hasComponent<Box2DComponent>())
	{
		Box2DComponent& component = this->m_entity.getComponent<Box2DComponent>();
		component.m_body->SetTransform(b2Vec2(inPos.x / BOX2D_PIXEL_TO_METER, inPos.y / BOX2D_PIXEL_TO_METER), component.m_body->GetAngle());
	}
}

void Character::setCategoryBits(unsigned short categoryBits)
{
	m_categoryBits = categoryBits;
	if (this->m_entity.hasComponent<Box2DComponent>())
	{
		Box2DComponent& component = this->m_entity.getComponent<Box2DComponent>();
		for (auto fixture = component.m_body->GetFixtureList(); fixture != NULL; fixture = fixture->GetNext())
		{
			auto filterData = fixture->GetFilterData();
			filterData.categoryBits = categoryBits;
			fixture->SetFilterData(filterData);
		}
	}
}

unsigned short Character::getCategoryBits()
{
	return m_categoryBits;
}
