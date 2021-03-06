#include "TestPhysics.h"
#include "ecs/utils/CommonUtils.h"

cocos2d::Scene* TestPhysics::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TestPhysics::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

//////////////////////////////////////////////////////////////////////////

static inline real Random(real l, real h)
{
	real a = (real)rand();
	a /= RAND_MAX;
	a = (h - l) * a + l;
	return a;
}

//////////////////////////////////////////////////////////////////////////

TestPhysics::TestPhysics()
{
	m_physicsSystem = new PhysicsSystem(10);
}

TestPhysics::~TestPhysics()
{
	m_world.clear();
	delete m_physicsSystem;
}

bool TestPhysics::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	_scheduler->schedule(CC_SCHEDULE_SELECTOR(TestPhysics::logicUpdate), this, 1.0f / 60.0f, false);
	m_world.addSystem(*m_physicsSystem);
	m_world.addSystem(m_globalSystem);

	m_drawNode = DrawNode::create();
	this->addChild(m_drawNode);

	auto& global = CommonUtils::getGlobalComponent(m_world);
	global.debugDrawNode = m_drawNode;

	auto winSize = Director::getInstance()->getWinSize();

	anax::Entity entity;
	entity = m_world.createEntity();
	PhysicsSystem::createCircleBody(entity, 50.0f / PHYSICS_PIXEL_TO_METER, 1);
	PhysicsSystem::setStatic(entity);
	PhysicsSystem::setPosition(entity, winSize.width * 0.5f / PHYSICS_PIXEL_TO_METER, 300.0f / PHYSICS_PIXEL_TO_METER);
	entity.activate();

	//Random(1, 2);
	//Random(1, 2);
	//Random(1, 2);
	//spawnPolygon(Vec2(winSize.width * 0.5f, 300.0f));

	entity = m_world.createEntity();
	PhysicsSystem::createBoxBody(entity, winSize.width * 0.8f * 0.5f / PHYSICS_PIXEL_TO_METER, 10.0f / PHYSICS_PIXEL_TO_METER);
	PhysicsSystem::setPosition(entity, winSize.width * 0.5f / PHYSICS_PIXEL_TO_METER, 100.0f / PHYSICS_PIXEL_TO_METER);
	PhysicsSystem::setStatic(entity);
	PhysicsSystem::setRotation(entity, 0.0f);
	entity.activate();

	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	this->setTouchEnabled(true);

	m_createCircle = true;

	/// Menu
	auto meun = Menu::create();

	auto item = MenuItemFont::create("Create Circle");
	item->setCallback([=](Ref* sender) 
	{
		this->m_createCircle = !this->m_createCircle;
		if (m_createCircle)
			item->setString("Create Circle");
		else
			item->setString("Create Polygon");
	});
	meun->addChild(item);
	meun->alignItemsVertically();
	this->addChild(meun);
	return true;
}



void TestPhysics::spawnCircle(const Vec2& pos)
{
	auto entity = m_world.createEntity();
	PhysicsSystem::createCircleBody(entity, Random(1.0f, 3.0f) * 10.0f / PHYSICS_PIXEL_TO_METER);
	PhysicsSystem::setPosition(entity, pos.x / PHYSICS_PIXEL_TO_METER, pos.y / PHYSICS_PIXEL_TO_METER);

	entity.activate();
}

void TestPhysics::spawnPolygon(const Vec2& pos)
{
	uint32_t count = (uint32_t)Random(3, MaxPolyVertexCount);
	GVec2 *vertices = new GVec2[count];
	real e = Random(50.0f / PHYSICS_PIXEL_TO_METER, 100.0f / PHYSICS_PIXEL_TO_METER);
	for (uint32_t i = 0; i < count; ++i)
		vertices[i].set(Random(-e, e), Random(-e, e));

	auto entity = m_world.createEntity();
	PhysicsSystem::createPolygonBody(entity, vertices, count);
	PhysicsSystem::setPosition(entity, pos.x / PHYSICS_PIXEL_TO_METER, pos.y / PHYSICS_PIXEL_TO_METER);
	PhysicsSystem::setRotation(entity, Random(-G_PI, G_PI));

	auto& component = entity.getComponent<BodyComponent>();
	component.restitution = Random(0.2f, 2.0f);
	component.dynamicFriction = 0.2f;
	component.staticFriction = 0.4f;

	delete[]vertices;

	entity.activate();
}

void TestPhysics::logicUpdate(float dt)
{
	m_world.refresh();
	m_drawNode->clear();
	m_physicsSystem->update(dt);
	m_physicsSystem->debugDraw();
}


bool TestPhysics::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void TestPhysics::onTouchMoved(Touch *touch, Event *unused_event)
{}

void TestPhysics::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (m_createCircle)
		spawnCircle(touch->getLocation());
	else
		spawnPolygon(touch->getLocation());
}

void TestPhysics::onTouchCancelled(Touch *touch, Event *unused_event)
{}
