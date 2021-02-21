#include "TestSIMPhys.h"
#include "ecs/utils/CommonUtils.h"


cocos2d::Scene* TestSIMPhys::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TestSIMPhys::create();

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

TestSIMPhys::TestSIMPhys()
{
}

TestSIMPhys::~TestSIMPhys()
{
	m_world.clear();
}

bool TestSIMPhys::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	_scheduler->schedule(CC_SCHEDULE_SELECTOR(TestSIMPhys::logicUpdate), this, 1.0f / 60.0f, false);

	m_physicsSystem.setGravity(GVec2(0, -500.0f));
	m_world.addSystem(m_physicsSystem);
	m_world.addSystem(m_globalSystem);

	m_drawNode = DrawNode::create();
	this->addChild(m_drawNode);

	auto& global = CommonUtils::getGlobalComponent(m_world);
	global.debugDrawNode = m_drawNode;

	auto winSize = Director::getInstance()->getWinSize();

	float32 space = 100.0f;
	float32 width = 10.0f;

	float32 h_width = width;
	float32 h_height = winSize.height - space * 2.0f;
	float32 v_width = winSize.width - space * 2.0f - width * 2.0f;
	float32 v_height = width;

	anax::Entity entity;

	//  left
	entity = m_world.createEntity();
	SIMPhysSystem::createBox(entity, GVec2(space, space), GVec2(h_width, h_height), GVec2(0.0f, 0.0f));
	entity.getComponent<SIMPhysComponent>().isStatic = true;
	entity.activate();

	// bottom
	entity = m_world.createEntity();
	SIMPhysSystem::createBox(entity, GVec2(space + width, space), GVec2(v_width, v_height), GVec2(0.0f, 0.0f));
	entity.getComponent<SIMPhysComponent>().isStatic = true;
	entity.activate();
	
	// right
	entity = m_world.createEntity();
	SIMPhysSystem::createBox(entity, GVec2(winSize.width - space, space), GVec2(h_width, h_height), GVec2(1.0f, 0.0f));
	entity.getComponent<SIMPhysComponent>().isStatic = true;
	entity.activate();

	// top
	entity = m_world.createEntity();
	SIMPhysSystem::createBox(entity, GVec2(space + width, winSize.height - space), GVec2(v_width, v_height), GVec2(0.0f, 1.0f));
	entity.getComponent<SIMPhysComponent>().isStatic = true;
	entity.activate();

	entity = m_world.createEntity();
	SIMPhysSystem::createBox(entity, GVec2(winSize.width * 0.5f, winSize.height * 0.5f), GVec2(winSize.width * 0.3f, 10.0f), GVec2(0.5f, 0.5f));
	entity.getComponent<SIMPhysComponent>().isStatic = true;
	entity.activate();

	entity = m_world.createEntity();
	SIMPhysSystem::createBox(entity, GVec2(winSize.width * 0.25f, winSize.height * 0.25f), GVec2(winSize.width * 0.3f, 10.0f), GVec2(0.5f, 0.5f));
	entity.getComponent<SIMPhysComponent>().isStatic = true;
	entity.activate();

	entity = m_world.createEntity();
	SIMPhysSystem::createBox(entity, GVec2(winSize.width * 0.65f, winSize.height * 0.35f), GVec2(winSize.width * 0.3f, 10.0f), GVec2(0.5f, 0.5f));
	entity.getComponent<SIMPhysComponent>().isStatic = true;
	entity.activate();

	m_player = m_world.createEntity();
	SIMPhysSystem::createBox(m_player, GVec2(winSize.width * 0.5f, winSize.height * 0.5f), GVec2(30.0f, 60.0f), GVec2(0.5f, 0.5f));
	m_player.activate();

	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	this->setTouchEnabled(true);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event*)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			if (m_moveDir == MoveDir::STOP)
				m_moveDir = MoveDir::MOVE_TO_LEFT;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)
		{
			if (m_moveDir == MoveDir::STOP)
				m_moveDir = MoveDir::MOVE_TO_RIGHT;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_W)
		{
			auto &component = m_player.getComponent<SIMPhysComponent>();
			if(component.linearVelocity.y == 0.0f)
				SIMPhysSystem::applyImpulse(m_player, GVec2(0.0f, 400.0f));
		}
	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event*)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_D)
		{
			m_moveDir = MoveDir::STOP;	
			auto& component = m_player.getComponent<SIMPhysComponent>();
			component.linearVelocity.x = 0.0f;
			component.force.setzero();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	m_moveDir = MoveDir::STOP;

	return true;
}

void TestSIMPhys::logicUpdate(float dt)
{
	m_world.refresh();
	m_drawNode->clear();
	m_physicsSystem.update(dt);
	m_physicsSystem.debugDraw();

	if (m_moveDir == MoveDir::MOVE_TO_LEFT)
	{
		SIMPhysSystem::applyForce(m_player, GVec2(-200.0f, 0.0f));
	}
	else if (m_moveDir == MoveDir::MOVE_TO_RIGHT)
	{
		SIMPhysSystem::applyForce(m_player, GVec2(200.0f, 0.0f));
	}
}


bool TestSIMPhys::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void TestSIMPhys::onTouchMoved(Touch *touch, Event *unused_event)
{}

void TestSIMPhys::onTouchEnded(Touch *touch, Event *unused_event)
{
	auto center = touch->getLocation();

	//auto size = GVec2(Random(20.0f, 50.0f), Random(20.0f, 100.0f));
	auto size = GVec2(30.0f, 100.0f);

	auto & entity = m_world.createEntity();
	SIMPhysSystem::createBox(entity, GVec2(center.x, center.y), size, GVec2(0.0f, 1.0f));
	entity.getComponent<SIMPhysComponent>().gravityScale = Random(1.0f, 5.0f);
	entity.activate();
}

void TestSIMPhys::onTouchCancelled(Touch *touch, Event *unused_event)
{}

