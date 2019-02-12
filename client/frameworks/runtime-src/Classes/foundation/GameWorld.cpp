#include "GameWorld.h"
#include "ecs/system/Box2DSystem.h"
#include "ecs/system/MapFollowSystem.h"
#include "ecs/system/ArmatureCollisionSystem.h"
#include "ecs/system/UpdateSystem.h"

GameWorld::GameWorld()
	: m_box2DSystem(NULL)
#ifdef ENABLE_BOX2D_DEBUG_DRAW
	, m_physicsDebugDraw(NULL)
#endif
	, m_gameMap(NULL)
	, m_mapFollowSystem(NULL)
	, m_armatureCollisionSystem(NULL)
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
	if (GameWorldBase::init() == false)
	{
		return false;
	}

	m_armatureCollisionSystem = new ArmatureCollisionSystem();
	m_world.addSystem<ArmatureCollisionSystem>(*m_armatureCollisionSystem);

	m_updateSystem = new UpdateSystem();
	m_world.addSystem<UpdateSystem>(*m_updateSystem);

	return true;
}

void GameWorld::enableBox2DPhysics(bool enable, float left_offset, float right_offset, float top_offset, float bottom_offset)
{
	if (enable)
	{
		CC_ASSERT(m_gameMap != NULL);

		if (m_box2DSystem == NULL)
		{
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
	}
	else
	{
		if (m_box2DSystem)
		{
			m_world.removeSystem<Box2DSystem>();
			CC_SAFE_DELETE(m_box2DSystem);

#ifdef ENABLE_BOX2D_DEBUG_DRAW
			CC_SAFE_DELETE(m_physicsDebugDraw);
#endif
		}
	}
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

	if (m_box2DSystem != NULL)
	{
		m_box2DSystem->updateWorld(delta);
	}

	if (m_mapFollowSystem != NULL)
	{
		m_mapFollowSystem->update();
	}

	m_armatureCollisionSystem->collisionTest();

	callLuaLogicUpdate(delta);
}

void GameWorld::onWorldDestroy()
{
	CC_SAFE_DELETE(m_box2DSystem);
	CC_SAFE_DELETE(m_mapFollowSystem);
	CC_SAFE_DELETE(m_armatureCollisionSystem);
	CC_SAFE_DELETE(m_updateSystem);
	GameWorldBase::onWorldDestroy();
}

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
