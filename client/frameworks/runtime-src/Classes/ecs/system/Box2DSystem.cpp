#include "Box2DSystem.h"
#include "foundation/Actor.h"

Box2DSystem::Box2DSystem()
	: m_box2DWorld(nullptr)
{

}

Box2DSystem::~Box2DSystem()
{
	CC_SAFE_DELETE(m_box2DWorld);
}

bool Box2DSystem::initPhysics(const Vec2 & gravity, const Size& worldSize, float left_offset, float right_offset, float top_offset, float bottom_offset)
{
	CC_ASSERT(m_box2DWorld == NULL);
	if (m_box2DWorld != nullptr)
	{
		return false;
	}

	m_box2DWorld = new b2World(b2Vec2(gravity.x, gravity.y));
	m_box2DWorld->SetAllowSleeping(true);
	m_box2DWorld->SetWarmStarting(true);
	m_box2DWorld->SetContinuousPhysics(true);
	m_box2DWorld->SetContactListener(this);

	initWall(worldSize, left_offset, right_offset);

	left_offset = -worldSize.width * 0.5f;
	right_offset = -worldSize.width * 0.5f;

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	b2Body* groundBody = m_box2DWorld->CreateBody(&groundBodyDef);

	// filter
	b2Filter filter;
	filter.groupIndex = 0;
	filter.categoryBits = BOX2D_FILTER_MASK::B2DM_GROUND;
	filter.maskBits = BOX2D_FILTER_MASK::B2DM_PLAYER | BOX2D_FILTER_MASK::B2DM_SKILL | BOX2D_FILTER_MASK::B2DM_MONSTER;

	// Define the ground box shape.
	b2EdgeShape groundBox;

	const float world_width = worldSize.width;
	const float world_height = worldSize.height;

	Vec2 LB(left_offset, bottom_offset);
	Vec2 LT(left_offset, world_height - top_offset);
	Vec2 RB(world_width - right_offset, bottom_offset);
	Vec2 RT(world_width - right_offset, world_height - top_offset);

	LB = LB / BOX2D_PIXEL_TO_METER;
	LT = LT / BOX2D_PIXEL_TO_METER;
	RB = RB / BOX2D_PIXEL_TO_METER;
	RT = RT / BOX2D_PIXEL_TO_METER;

	// bottom
	groundBox.Set(b2Vec2(LB.x, LB.y), b2Vec2(RB.x, RB.y));
	auto fixture = groundBody->CreateFixture(&groundBox, 0);
	fixture->SetFilterData(filter);
	fixture->SetUserData(this);

	// top
	groundBox.Set(b2Vec2(LT.x, LT.y), b2Vec2(RT.x, RT.y));
	fixture = groundBody->CreateFixture(&groundBox, 0);
	fixture->SetFilterData(filter);

	// left
	groundBox.Set(b2Vec2(LT.x, LT.y), b2Vec2(LB.x, LB.y));
	fixture = groundBody->CreateFixture(&groundBox, 0);
	fixture->SetFilterData(filter);

	// right
	groundBox.Set(b2Vec2(RB.x, RB.y), b2Vec2(RT.x, RT.y));
	fixture = groundBody->CreateFixture(&groundBox, 0);
	fixture->SetFilterData(filter);

	//// 地面定义
	//b2PolygonShape shape;
	//shape.SetAsBox(worldSize.width / BOX2D_PIXEL_TO_METER, 10.0f / BOX2D_PIXEL_TO_METER, b2Vec2(0.0f, LB.y), 0.0f);
	//b2FixtureDef fixdef;
	//fixdef.shape = &shape;
	//fixdef.userData = this;
	//fixdef.isSensor = true;
	//groundBody->CreateFixture(&fixdef);


	return true;
}

void Box2DSystem::initWall(const Size& worldSize, float letf_offset, float right_offset)
{
	// Define the left wall body.
	b2BodyDef leftBodyDef;
	leftBodyDef.position.Set(0, 0);
	leftBodyDef.type = b2BodyType::b2_staticBody;
	b2Body* leftBody = m_box2DWorld->CreateBody(&leftBodyDef);

	b2Filter filter;
	filter.groupIndex = 0;
	filter.categoryBits = BOX2D_FILTER_MASK::B2DM_SIDE_WALL;
	filter.maskBits = BOX2D_FILTER_MASK::B2DM_PLAYER | BOX2D_FILTER_MASK::B2DM_MONSTER;

	// 实体矩形
	b2PolygonShape shape;
	shape.SetAsBox(letf_offset / BOX2D_PIXEL_TO_METER * 2, worldSize.height / BOX2D_PIXEL_TO_METER, b2Vec2(0.0f, 0.0f), 0.0f);
	b2FixtureDef fixdef;
	fixdef.shape = &shape;
	fixdef.filter = filter;
	fixdef.friction = 0.0f;
	leftBody->CreateFixture(&fixdef);

	// Define the right wall body.
	b2BodyDef rightBodyDef;
	rightBodyDef.position.Set(worldSize.width / BOX2D_PIXEL_TO_METER, 0);
	rightBodyDef.type = b2BodyType::b2_staticBody;
	b2Body* rightBody = m_box2DWorld->CreateBody(&rightBodyDef);

	// 实体矩形
	shape.SetAsBox(letf_offset / BOX2D_PIXEL_TO_METER * 2, worldSize.height / BOX2D_PIXEL_TO_METER, b2Vec2(0.0f, 0.0f), 0.0f);
	fixdef.shape = &shape;
	rightBody->CreateFixture(&fixdef);
}

void Box2DSystem::updateWorld(float delta)
{
	clearDiscardB2BodyList();
	m_box2DWorld->Step(delta, 4, 4);
	//clearDiscardB2BodyList();
	syncPhysicsTransform();
}

void Box2DSystem::addDiscardB2Body(b2Body* body)
{
	auto it = std::find(m_discardB2BodyList.begin(), m_discardB2BodyList.end(), body);
	if (it == m_discardB2BodyList.end())
	{
		m_discardB2BodyList.push_back(body);
	}
}

void Box2DSystem::clearDiscardB2BodyList()
{
	if (m_discardB2BodyList.empty())
		return;

	for (auto& it : m_discardB2BodyList)
	{
		m_box2DWorld->DestroyBody(it);
	}
	m_discardB2BodyList.clear();
}

void Box2DSystem::syncPhysicsTransform()
{
	auto& entities = getEntities();
	for (auto& it : entities)
	{
		auto& component = it.getComponent<Box2DComponent>();
		if (component.m_syncPhysicsTransformCall.isvalid())
		{
			float _x = component.m_body->GetTransform().p.x * BOX2D_PIXEL_TO_METER;
			float _y = component.m_body->GetTransform().p.y * BOX2D_PIXEL_TO_METER;
			float _a = CC_RADIANS_TO_DEGREES(component.m_body->GetAngle());
			component.m_syncPhysicsTransformCall.ppush();
			component.m_syncPhysicsTransformCall.pusharg(_x);
			component.m_syncPhysicsTransformCall.pusharg(_y);
			component.m_syncPhysicsTransformCall.pusharg(_a);
			component.m_syncPhysicsTransformCall.pcall();
		}
	}
}

/// b2ContactListener
void Box2DSystem::BeginContact(b2Contact* contact)
{
	void* userdateA = contact->GetFixtureA()->GetUserData();
	void* userdateB = contact->GetFixtureB()->GetUserData();
	if (userdateA == this && userdateB != NULL)
	{
		Actor* actor = (Actor*)userdateB;
		LuaFunction* handle = actor->getLuaHandle("beginContactCall");
		if (handle)
		{
			handle->ppush();
			handle->pcall();
		}
	}
	if (userdateB == this && userdateA != NULL)
	{
		Actor* actor = (Actor*)userdateA;
		LuaFunction* handle = actor->getLuaHandle("beginContactCall");
		if (handle)
		{
			handle->ppush();
			handle->pcall();
		}
	}
}

void Box2DSystem::EndContact(b2Contact* contact)
{
	void* userdateA = contact->GetFixtureA()->GetUserData();
	void* userdateB = contact->GetFixtureB()->GetUserData();
	if (userdateA == this && userdateB != NULL)
	{
		Actor* actor = (Actor*)userdateB;
		LuaFunction* handle = actor->getLuaHandle("endContactCall");
		if (handle)
		{
			handle->ppush();
			handle->pcall();
		}
	}
	if (userdateB == this && userdateA != NULL)
	{
		Actor* actor = (Actor*)userdateA;
		LuaFunction* handle = actor->getLuaHandle("endContactCall");
		if (handle)
		{
			handle->ppush();
			handle->pcall();
		}
	}
}

