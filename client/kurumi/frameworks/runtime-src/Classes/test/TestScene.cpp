#include "TestScene.h"

Scene* TestScene::createScene()
{
	auto ptr = TestScene::create();
	if (ptr == NULL)
		return NULL;

	Scene* scene = Scene::create();
	scene->addChild(ptr);
	return scene;
}

TestScene* TestScene::create()
{
	auto ptr = new TestScene();
	if (ptr && ptr->init())
	{
		ptr->autorelease();
		return ptr;
	}
	CC_SAFE_RELEASE_NULL(ptr);
	return NULL;
}

TestScene::TestScene()
	: m_player(NULL)
	, m_pWorld(NULL)
	, m_delayTime(0.0f)
{
	m_input = 0;
	m_lastPosx = 0.0f;
}

TestScene::~TestScene()
{}

bool TestScene::init()
{
	if (!Node::init())
		return false;

	m_pWorld = GGameWorld::create(4, ::time(NULL), this);
	if (m_pWorld == NULL)
	{
		return false;
	}

	this->schedule(CC_SCHEDULE_SELECTOR(TestScene::logicUpdate), LogicInterval.to_float());

	m_player = m_pWorld->getEntityManager()->newEntity();

	auto pComponent = new GRigidBodyComponent();
	pComponent->setMass(100.0f / PHYSICS_PIXEL_TO_METER);
	pComponent->setBox(GFixedVec3(100.0f, 100.0f, 50.0f), GFixedVec3(50.0f, 200.0f, 10.0f), GFixedVec3(0.5f, 0.5f, 0.0f));
	m_player->addComponent(pComponent);

	//auto winSize = Director::getInstance()->getWinSize();

	//{
	//	auto pComponent = new GRigidBodyComponent();
	//	m_pWorld->getPhysSystem()->setStaticBox(pComponent, GFixedVec2(300.0f, 150.0f), GFixedVec2(400.0f, 10.0f), GFixedVec2(0.0f, 0.0f));
	//	m_pWorld->getEntityManager()->newEntity()->addComponent(pComponent);
	//}
	//{
	//	auto pComponent = new GRigidBodyComponent();
	//	m_pWorld->getPhysSystem()->setStaticBox(pComponent, GFixedVec2(200.0f, 300.0f), GFixedVec2(200.0f, 50.0f), GFixedVec2(0.5f, 0.0f));
	//	m_pWorld->getEntityManager()->newEntity()->addComponent(pComponent);
	//}

	const float range_x_min = 100.0f;
	const float range_x_max = 1000.0f;

	const float range_y_min = 10.0f;
	const float range_y_max = 100.0f;

	const float size_min = 20.0f;
	const float size_max = 200.0f;

	const float static_size_w_min = 5.0f;
	const float static_size_w_max = 200.0f;
	const float static_size_h_min = 5.0f;
	const float static_size_h_max = 50.0f;


	// //添加若干动态对象
	//for (auto i = 0; i < 5; ++i)
	//{
	//	GFixedVec3 pos;
	//	pos.x = m_pWorld->getRandom()->randomFloat(range_x_min, range_x_max);
	//	pos.z = m_pWorld->getRandom()->randomFloat(range_y_min, range_y_max);

	//	GFixedVec3 size;
	//	size.x = m_pWorld->getRandom()->randomFloat(size_min, size_max);
	//	size.z = 10.0f;
	//	size.y = 100.0f;
	//	
	//	auto pComponent = new GRigidBodyComponent();
	//	m_pWorld->getPhysSystem()->setBox(pComponent, pos, size, GFixedVec3(0.5f, 0.5f, 0.0f));
	//	m_pWorld->getEntityManager()->newEntity()->addComponent(pComponent);

	//	Box box;
	//	box.component = pComponent;
	//	box.waitTime = 0.0f;
	//	m_otherBox.push_back(box);
	//}

	//// 添加若干静态对象
	//for (auto i = 0; i < 10; ++i)
	//{
	//	GFixedVec2 pos;
	//	pos.x = m_pWorld->getRandom()->randomFloat(range_x_min, range_x_max);
	//	pos.y = m_pWorld->getRandom()->randomFloat(range_y_min, range_y_max);

	//	GFixedVec2 size;
	//	size.x = m_pWorld->getRandom()->randomFloat(static_size_w_min, static_size_w_max);
	//	size.y = m_pWorld->getRandom()->randomFloat(static_size_h_min, static_size_h_max);

	//	auto pComponent = new GRigidBodyComponent();
	//	m_pWorld->getPhysSystem()->setStaticBox(pComponent, pos, size, GFixedVec2(0.5f, 0.5f));
	//	m_pWorld->getEntityManager()->newEntity()->addComponent(pComponent);
	//}

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [this](EventKeyboard::KeyCode code, Event *e)
	{
		switch (code)
		{
		case EventKeyboard::KeyCode::KEY_SPACE:
		{
			G_BIT_REMOVE(m_input, G_KEY_JUMP);
		}break;
		case EventKeyboard::KeyCode::KEY_A:
		{
			G_BIT_REMOVE(m_input, G_KEY_MOVE_LEFT);
		}break;
		case EventKeyboard::KeyCode::KEY_W:
		{
			G_BIT_REMOVE(m_input, G_KEY_MOVE_UP);
		}break;
		case EventKeyboard::KeyCode::KEY_S:
		{
			G_BIT_REMOVE(m_input, G_KEY_MOVE_DOWN);
		}break;
		case EventKeyboard::KeyCode::KEY_D:
		{
			G_BIT_REMOVE(m_input, G_KEY_MOVE_RIGHT);
		}break;
		default:
			break;
		}
	};
	listener->onKeyPressed = [this](EventKeyboard::KeyCode code, Event *e)
	{
		switch (code)
		{
		case EventKeyboard::KeyCode::KEY_SPACE:
		{
			G_BIT_SET(m_input, G_KEY_JUMP);
		}break;
		case EventKeyboard::KeyCode::KEY_A:
		{
			G_BIT_SET(m_input, G_KEY_MOVE_LEFT);
		}break;
		case EventKeyboard::KeyCode::KEY_W:
		{
			G_BIT_SET(m_input, G_KEY_MOVE_UP);
		}break;
		case EventKeyboard::KeyCode::KEY_S:
		{
			G_BIT_SET(m_input, G_KEY_MOVE_DOWN);
		}break;
		case EventKeyboard::KeyCode::KEY_D:
		{
			G_BIT_SET(m_input, G_KEY_MOVE_RIGHT);
		}break;
		default:
			break;
		}
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

static float movex_force = 300.0f / PHYSICS_PIXEL_TO_METER;
static float movez_force = 300.0f / PHYSICS_PIXEL_TO_METER;

void TestScene::logicUpdate(float dt)
{
	m_pWorld->step();

	auto pComponent = G_GetComponent(m_player, GRigidBodyComponent);

	if (G_BIT_EQUAL(m_input, G_KEY_JUMP))
	{
		G_BIT_REMOVE(m_input, G_KEY_JUMP);
		pComponent->applyImpulse(GFixedVec3(0.0f, 1000.0f / PHYSICS_PIXEL_TO_METER, 0.0f));
	}

	if (G_BIT_EQUAL(m_input, G_KEY_MOVE_LEFT))
	{
		pComponent->applyForce(GFixedVec3(-movex_force, 0.0f, 0.0f));
	}
	else if (G_BIT_EQUAL(m_input, G_KEY_MOVE_RIGHT))
	{
		pComponent->applyForce(GFixedVec3(movex_force, 0.0f, 0.0f));
	}
	else
	{
		pComponent->linearVelocity.x.setZero();
	}


	if (G_BIT_EQUAL(m_input, G_KEY_MOVE_UP))
	{
		pComponent->applyForce(GFixedVec3(0.0f, 0.0f, movez_force));
	}
	else if (G_BIT_EQUAL(m_input, G_KEY_MOVE_DOWN))
	{
		pComponent->applyForce(GFixedVec3(0.0f, 0.0f, -movez_force));
	}
	else
	{
		pComponent->linearVelocity.z.setZero();
	}


	auto random = m_pWorld->getRandom();
	for (auto& it : m_otherBox)
	{
		float forcex = random->random0_1() * 300.0f / PHYSICS_PIXEL_TO_METER;
		float forcey = random->random0_1() * 300.0f / PHYSICS_PIXEL_TO_METER;

		if (random->random(0, 1) == 0)
			forcex = -forcex;
		if (random->random(0, 1) == 0)
			forcey = -forcey;
		it.component->applyForce(GFixedVec3(forcex, forcey, 0.0f));

		if (it.waitTime > 0)
		{
			it.waitTime -= dt;
		}
		else
		{
			it.waitTime = random->random0_1() * 5.0f;
			it.component->applyImpulse(GFixedVec3(0.0f, random->random0_1() * 20.0f, 0.0f));
		}
	}

	m_delayTime += dt;
	if (m_delayTime >= 1.0f)
	{
		m_delayTime = 0.0f;
		auto pCom = G_GetComponent(m_player, GRigidBodyComponent);

		auto curPosx = (pCom->position.x * PHYSICS_PIXEL_TO_METER).to_float();
		CCLOG("speed:%f", std::fabsf(curPosx - m_lastPosx));

		m_lastPosx = curPosx;
	}
}

