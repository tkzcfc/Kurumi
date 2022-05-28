#include "TestScene1.h"
#include "mugen/component/GAvatarComponent.h"

Scene* TestScene1::createScene()
{
	auto ptr = TestScene1::create();
	if (ptr == NULL)
		return NULL;

	Scene* scene = Scene::create();
	scene->addChild(ptr);
	return scene;
}

TestScene1* TestScene1::create()
{
	auto ptr = new TestScene1();
	if (ptr && ptr->init())
	{
		ptr->autorelease();
		return ptr;
	}
	CC_SAFE_RELEASE_NULL(ptr);
	return NULL;
}

TestScene1::TestScene1()
{
	m_input = 0;
}

TestScene1::~TestScene1()
{}

bool TestScene1::init()
{
	if (!Node::init())
		return false;

	m_pWorld = GGameWorld::create(4, ::time(NULL), this);
	if (m_pWorld == NULL)
	{
		return false;
	}

	this->scheduleUpdate();
	this->schedule(CC_SCHEDULE_SELECTOR(TestScene1::logicUpdate), LogicInterval.to_float());

	m_pWorld->enableDebugDraw(true);
	//m_pWorld->spwanActor("binary/R1001.bytes", GFixedVec3(50.0f, 0.0f, 60.0f));


	m_player = m_pWorld->spwanActor("binary/R1001.bytes", GFixedVec3(0.0f, 0.0f, 0.0f));
	G_GetComponent(m_player, GActorComponent)->setPosition(150.0f, 60.0f);

	m_pWorld->setLocalPlayer(m_player);

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
		case EventKeyboard::KeyCode::KEY_J:
		{
			G_BIT_REMOVE(m_input, G_KEY_SKILL_1);
		}break;
		case EventKeyboard::KeyCode::KEY_K:
		{
			G_BIT_REMOVE(m_input, G_KEY_SKILL_2);
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
		case EventKeyboard::KeyCode::KEY_J:
		{
			G_BIT_SET(m_input, G_KEY_SKILL_1);
		}break;
		case EventKeyboard::KeyCode::KEY_K:
		{
			G_BIT_SET(m_input, G_KEY_SKILL_2);
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

void TestScene1::logicUpdate(float dt)
{
	m_pWorld->input(m_player->getId(), m_pWorld->getGameLogicFrame(), m_input);

	m_pWorld->step();

	/*auto camera = m_pWorld->getMapLayer()->getVirtualCamera();
	if (G_BIT_EQUAL(m_input, G_KEY_MOVE_LEFT))
	{
		auto pos = camera->getPosition();
		pos.x -= 15.0f;
		camera->setPosition(pos);
	}
	else if (G_BIT_EQUAL(m_input, G_KEY_MOVE_RIGHT))
	{
		auto pos = camera->getPosition();
		pos.x += 15.0f;
		camera->setPosition(pos);
	}

	if (G_BIT_EQUAL(m_input, G_KEY_MOVE_UP))
	{
		auto pos = camera->getPosition();
		pos.y -= 15.0f;
		camera->setPosition(pos);
	}
	else if (G_BIT_EQUAL(m_input, G_KEY_MOVE_DOWN))
	{
		auto pos = camera->getPosition();
		pos.y += 15.0f;
		camera->setPosition(pos);
	}

	if (G_BIT_EQUAL(m_input, G_KEY_SKILL_1))
	{
		auto zoom = camera->getZoom();
		zoom -= 0.01f;
		zoom = MAX(zoom, 1.0f);
		camera->setZoom(zoom);
	}
	else if (G_BIT_EQUAL(m_input, G_KEY_SKILL_2))
	{
		auto zoom = camera->getZoom();
		zoom += 0.01f;
		zoom = MIN(zoom, 4.0f);
		camera->setZoom(zoom);
	}*/

	//auto size = Director::getInstance()->getWinSize();
	//m_pMapLayer->getVirtualCamera()->setFocalPos(size * 0.6f);
}

void TestScene1::update(float delta)
{
	m_pWorld->render(delta);
}


