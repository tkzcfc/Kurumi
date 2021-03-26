#include "GGameWorld.h"
#include "ecs/utils/CommonUtils.h"

enum MOVE_DIR
{
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	STOP
};

static MOVE_DIR static_h_dir = MOVE_DIR::STOP;
static MOVE_DIR static_v_dir = MOVE_DIR::STOP;

/////////////////////////////////////////////////////
/// init
#if G_TARGET_CLIENT
bool GGameWorld::init(int mapId, Node* rootNode)
#else
bool GGameWorld::init(int32_t mapId)
#endif
{
	do
	{
		m_SIMPhysSystem.setGravity(GVec2(0.0f, -15.0f));

		m_world.addSystem(m_armatureSystem);
		m_world.addSystem(m_collisionSystem);
		m_world.addSystem(m_globalSystem);
		m_world.addSystem(m_SIMPhysSystem);
		m_world.addSystem(m_transformSyncSystem);
		m_world.addSystem(m_inputSystem);
		m_world.addSystem(m_updateSystem);
		m_world.addSystem(m_skillInjurySystem);
		m_world.addSystem(m_UUIDSystem);

		// 客户端所需渲染系统
#if G_TARGET_CLIENT
		m_world.addSystem(m_armatureDebugSystem);
		m_world.addSystem(m_armatureRenderSystem);

		m_rootNode = rootNode;
#endif
		m_pGlobal = &m_globalSystem.admin.getComponent<GlobalComponent>();

		if (!this->initAdmin(mapId))
			break;

		if (!this->initPlayer())
			break;

		if (!this->initTest())
			break;

		return true;
	} while (0);
	return false;
}


// 初始化世界边界碰撞体
bool GGameWorld::initBorder()
{
	auto mapWidth = m_pGlobal->mapWidth;
	auto mapHeight = m_pGlobal->mapHeight;

	float32 space = 0.0f;
	float32 width = 10.0f;

	float32 h_width = width;
	float32 h_height = mapHeight - space * 2.0f;
	float32 v_width = mapWidth - space * 2.0f - width * 2.0f;
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
	SIMPhysSystem::createBox(entity, GVec2(mapWidth - space, space), GVec2(h_width, h_height), GVec2(1.0f, 0.0f));
	entity.getComponent<SIMPhysComponent>().isStatic = true;
	entity.activate();

	// top
	entity = m_world.createEntity();
	SIMPhysSystem::createBox(entity, GVec2(space + width, mapHeight - space), GVec2(v_width, v_height), GVec2(0.0f, 1.0f));
	entity.getComponent<SIMPhysComponent>().isStatic = true;
	entity.activate();

	return true;
}

bool GGameWorld::initTest()
{
#if G_TARGET_CLIENT
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event*)
	{
		auto frame = m_pGlobal->gameLogicFrame + 1;
		if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			auto msg = m_pGlobal->inputQue.addMsg<GOPMsg_Key>(frame, 1, G_CMD_KEY_DOWN);
			msg->key = G_KEY_MOVE_LEFT;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)
		{
			auto msg = m_pGlobal->inputQue.addMsg<GOPMsg_Key>(frame, 1, G_CMD_KEY_DOWN);
			msg->key = G_KEY_MOVE_RIGHT;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_W)
		{
			auto msg = m_pGlobal->inputQue.addMsg<GOPMsg_Key>(frame, 1, G_CMD_KEY_DOWN);
			msg->key = G_KEY_MOVE_UP;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_S)
		{
			auto msg = m_pGlobal->inputQue.addMsg<GOPMsg_Key>(frame, 1, G_CMD_KEY_DOWN);
			msg->key = G_KEY_MOVE_DOWN;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_J)
		{
			auto msg = m_pGlobal->inputQue.addMsg<GOPMsg_Key>(frame, 1, G_CMD_KEY_DOWN);
			msg->key = G_KEY_JUMP;
		}
	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event*)
	{
		auto frame = m_pGlobal->gameLogicFrame + 1;
		if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			auto msg = m_pGlobal->inputQue.addMsg<GOPMsg_Key>(frame, 1, G_CMD_KEY_UP);
			msg->key = G_KEY_MOVE_LEFT;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)
		{
			auto msg = m_pGlobal->inputQue.addMsg<GOPMsg_Key>(frame, 1, G_CMD_KEY_UP);
			msg->key = G_KEY_MOVE_RIGHT;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_W)
		{
			auto msg = m_pGlobal->inputQue.addMsg<GOPMsg_Key>(frame, 1, G_CMD_KEY_UP);
			msg->key = G_KEY_MOVE_UP;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_S)
		{
			auto msg = m_pGlobal->inputQue.addMsg<GOPMsg_Key>(frame, 1, G_CMD_KEY_UP);
			msg->key = G_KEY_MOVE_DOWN;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_J)
		{
			auto msg = m_pGlobal->inputQue.addMsg<GOPMsg_Key>(frame, 1, G_CMD_KEY_UP);
			msg->key = G_KEY_JUMP;
		}
		
	};
	m_rootNode->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_rootNode);
#endif
	return true;
}

bool GGameWorld::initAdmin(int32_t mapId)
{
	/// 初始化地图
	if (CommonUtils::initMapSize(m_globalSystem.admin, mapId) == false)
		return false;

#if G_TARGET_CLIENT
	// 初始化地图渲染
	auto mapLayer = GMapLayer::create(mapId);
	m_rootNode->addChild(mapLayer);

	m_camera = mapLayer->getVirtualCamera();

	G_ASSERT(std::fabs(mapLayer->getMapWidth() - m_pGlobal->mapWidth) < 1.0f);
	G_ASSERT(std::fabs(mapLayer->getMapHeight() - m_pGlobal->mapHeight) < 1.0f);

	m_pGlobal->debugDrawNode = mapLayer->getDrawNode();
	m_pGlobal->mapRender = mapLayer;
#endif

	if (!initBorder())
		return false;

	return true;
}

bool GGameWorld::initPlayer()
{
	for (auto i = 0; i < 1; ++i)
	{
		spawnPlayer();
	}
	return true;
}

bool GGameWorld::spawnPlayer()
{
	anax::Entity entity;

	static int s_index = 0;
	s_index++;

	ActorIdentityInfo info;
	info.bodySize = GVec2(40.0f, 120.0f);
	info.originPos = GVec2(300.0f + s_index * 200, 200.0f);
	info.roleName = "R1022";
	info.uuid = CommonUtils::genUUID();
	info.anifsm = "json/ani_fsm/dao_runtime.json";
	info.moveForce = GVec2(10.0f, 10.0f);
	info.jumpIm = GVec2(0.0f, 10.0f);

	if (!CommonUtils::spawnActor(m_world, info, &entity))
		return false;

	entity.activate();
	m_players.push_back(entity);
	return true;
}

