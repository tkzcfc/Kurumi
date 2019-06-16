#include "GameWorld.h"
#include "foundation/Actor.h"
#include "ecs/system/Box2DSystem.h"
#include "ecs/system/MapFollowSystem.h"
#include "ecs/system/ArmatureCollisionSystem.h"
#include "ecs/system/UpdateSystem.h"
#include "ecs/system/FilterSystem.h"

GameWorld::GameWorld()
	: m_box2DSystem(NULL)
#ifdef ENABLE_BOX2D_DEBUG_DRAW
	, m_physicsDebugDraw(NULL)
#endif
	, m_gameMap(NULL)
	, m_mapFollowSystem(NULL)
	, m_armatureCollisionSystem(NULL)
	, m_filterSystem(NULL)
	, m_bDebugEnable(true)
{}

GameWorld::~GameWorld()
{
#ifdef ENABLE_BOX2D_DEBUG_DRAW
	CC_SAFE_DELETE(m_physicsDebugDraw);
#endif
}

GameWorld* GameWorld::create()
{
	GameWorld* w = new GameWorld();
	if (w && w->init())
	{
		w->autorelease();
		return w;
	}
	CC_SAFE_DELETE(w);
	return w;
}

bool GameWorld::init()
{
	if (Node::init() == false)
	{
		return false;
	}

	_scheduler->schedule(CC_SCHEDULE_SELECTOR(GameWorld::logicUpdate), this, 1.0f / 60.0f, false);

	m_admin = m_world.createEntity();

	for (int i = GAMEWORLD_NODE_MAP; i < GAMEWORLD_NODE_MAX; ++i)
	{
		m_nodeArr[i] = Node::create();
		this->addChild(m_nodeArr[i], i - 1);
	}

	m_armatureCollisionSystem = new ArmatureCollisionSystem();
	m_world.addSystem<ArmatureCollisionSystem>(*m_armatureCollisionSystem);

	m_updateSystem = new UpdateSystem();
	m_world.addSystem<UpdateSystem>(*m_updateSystem);

	m_filterSystem = new FilterSystem();
	m_world.addSystem<FilterSystem>(*m_filterSystem);

	return true;
}

void GameWorld::onExit()
{
	for (auto i = 0; i < GAMEWORLD_NODE_MAX; ++i)
	{
		m_nodeArr[i]->removeAllChildren();
	}

	m_world.removeAllSystems();
	onWorldDestroy();

	Node::onExit();
}

void GameWorld::destroy(class Actor* actor)
{
	if (!m_destroyActorList.contains(actor))
	{
		m_destroyActorList.pushBack(actor);
	}
}

void GameWorld::initWorld(GameMap* gameMap, float left_offset, float right_offset, float top_offset, float bottom_offset)
{
	m_offsetX.x = left_offset;
	m_offsetX.y = right_offset;
	m_offsetY.x = bottom_offset;
	m_offsetY.y = top_offset;

	setGameMap(gameMap);

	CC_ASSERT(m_gameMap != NULL);
	CC_ASSERT(m_box2DSystem == NULL);

	auto mapSize = Size(m_gameMap->getMapWidth(), m_gameMap->getMapHeight() * 2);

	m_box2DSystem = new Box2DSystem();
	m_box2DSystem->initPhysics(Vec2(0.0f, -10.0f), mapSize, left_offset, right_offset, top_offset, bottom_offset);
	m_world.addSystem<Box2DSystem>(*m_box2DSystem);
	m_world.refresh();

#ifdef ENABLE_BOX2D_DEBUG_DRAW
	m_physicsDebugDraw = new GLESDebugDraw(BOX2D_PIXEL_TO_METER);
	m_physicsDebugDraw->AppendFlags(b2Draw::e_shapeBit);
	//m_physicsDebugDraw->AppendFlags(b2Draw::e_jointBit);
	//m_physicsDebugDraw->AppendFlags(b2Draw::e_aabbBit);
	//m_physicsDebugDraw->AppendFlags(b2Draw::e_pairBit);
	//m_physicsDebugDraw->AppendFlags(b2Draw::e_centerOfMassBit);
	m_box2DSystem->getBox2DWorld()->SetDebugDraw(m_physicsDebugDraw);
#endif
}

void GameWorld::setGameMap(GameMap* gameMap)
{
	if (gameMap == NULL)
	{
		if (m_gameMap)
		{
			m_gameMap->removeFromParent();
			m_gameMap = NULL;
		}
		m_world.removeSystem<MapFollowSystem>();
		CC_SAFE_DELETE(m_mapFollowSystem);
		return;
	}

	if (gameMap == m_gameMap)
	{
		return;
	}
	m_gameMap = gameMap;
	m_nodeArr[GAMEWORLD_NODE_MAP]->addChild(m_gameMap, -1);

	if (m_mapFollowSystem == NULL)
	{
		m_mapFollowSystem = new MapFollowSystem(gameMap);
		m_world.addSystem<MapFollowSystem>(*m_mapFollowSystem);
	}
	m_mapFollowSystem->resetGameMap(gameMap);

	m_armatureCollisionSystem->setDebugDrawNode(m_gameMap->getDrawNode());
}

float GameWorld::getValidWorldX(float inValue, float actorRadius)
{
	if (m_gameMap == NULL)
		return inValue;

	return m_gameMap->getValidWorldX(inValue, actorRadius + MAX(m_offsetX.x, m_offsetX.y));
}

float GameWorld::getValidWorldY(float inValue, float actorRadius)
{
	if (m_gameMap == NULL)
		return inValue;

	return m_gameMap->getValidWorldY(inValue, actorRadius + MAX(m_offsetY.x, m_offsetY.y));
}

void GameWorld::setDebugEnable(bool enable)
{
	m_bDebugEnable = enable;
#ifdef ENABLE_BOX2D_DEBUG_DRAW
	m_physicsDebugDraw->setEnable(enable);
#endif
#if COCOS2D_DEBUG == 1 
	if (m_gameMap && m_gameMap->getDrawNode())
	{
		m_gameMap->getDrawNode()->setVisible(enable);
	}
#endif
}

bool GameWorld::isEnableDebug()
{
	return m_bDebugEnable;
}

void GameWorld::logicUpdate(float delta)
{
	clearDestroyList();
	m_world.refresh();

	m_updateSystem->update(delta);
	m_updateSystem->lastUpdate(delta);
	m_box2DSystem->updateWorld(delta);
	m_mapFollowSystem->update();
	m_armatureCollisionSystem->collisionTest();

	callLuaLogicUpdate(delta);
}

void GameWorld::onWorldDestroy()
{
	CC_SAFE_DELETE(m_box2DSystem);
	CC_SAFE_DELETE(m_mapFollowSystem);
	CC_SAFE_DELETE(m_armatureCollisionSystem);
	CC_SAFE_DELETE(m_updateSystem);
	CC_SAFE_DELETE(m_filterSystem);
	auto handle = getLuaHandle("onWorldDestroy");
	if (handle)
	{
		handle->ppush();
		handle->pcall();
	}
}

void GameWorld::clearDestroyList()
{
	if (m_destroyActorList.empty())
	{
		return;
	}
	for (auto &it : m_destroyActorList)
	{
		it->removeFromParent();
		auto handle = getLuaHandle("onActorDestroy");
		if (handle)
		{
			handle->ppush();
			handle->pushusertype<Actor>(it, "Actor");
			handle->pcall();
		}
	}
	m_destroyActorList.clear();
}

void GameWorld::callLuaLogicUpdate(float delta)
{
	auto logicUpdateHandle = getLuaHandle("logicUpdate");
	if (logicUpdateHandle != NULL)
	{
		logicUpdateHandle->ppush();
		logicUpdateHandle->pusharg(delta);
		logicUpdateHandle->pcall();
	}
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#ifdef ENABLE_BOX2D_DEBUG_DRAW

void GameWorld::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
	Node::draw(renderer, transform, flags);

	if (m_box2DSystem == NULL)
	{
		return;
	}

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	_modelViewMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	_customCommand.init(_globalZOrder + 1);
	_customCommand.func = CC_CALLBACK_0(GameWorld::onDraw, this);
	renderer->addCommand(&_customCommand);

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void GameWorld::onDraw()
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");

	auto oldMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewMV);

	if (m_gameMap != NULL)
	{
		director->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, m_gameMap->getRootNode()->getNodeToParentTransform());
	}

	auto box2dSystem = m_world.getSystem<Box2DSystem>();
	box2dSystem->getBox2DWorld()->DrawDebugData();

	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, oldMV);
}

#endif
