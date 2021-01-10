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

GGameWorld::GGameWorld()
	: m_debugDrawNode(NULL)
{}

#if G_TARGET_CLIENT
bool GGameWorld::init(int mapId, Node* rootNode)
#else
bool GGameWorld::init(int mapId)
#endif
{
	do 
	{
		m_SIMPhysSystem.setGravity(GVec2(0.0f, -50.0f));

		m_world.addSystem<ArmatureSystem>(m_armatureSystem);
		m_world.addSystem<CollisionSystem>(m_collisionSystem);
		m_world.addSystem<GlobalSystem>(m_globalSystem);
		m_world.addSystem<SIMPhysSystem>(m_SIMPhysSystem);
		m_world.addSystem<TransformSyncSystem>(m_transformSyncSystem);

		// 客户端所需渲染系统
#if G_TARGET_CLIENT
		m_world.addSystem<ArmatureDebugSystem>(m_armatureDebugSystem);
		m_world.addSystem<ArmatureRenderSystem>(m_armatureRenderSystem);

		m_rootNode = rootNode;
#endif
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

// 初始化世界边界碰撞
bool GGameWorld::initBorder()
{
	auto& admin = m_globalSystem.admin;
	auto& mapComponent = admin.getComponent<MapComponent>();
	auto mapWidth = mapComponent.mapWidth;
	auto mapHeight = mapComponent.mapHeight;

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
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event*)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			if (static_h_dir == MOVE_DIR::STOP)
				static_h_dir = MOVE_DIR::LEFT;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)
		{
			if (static_h_dir == MOVE_DIR::STOP)
				static_h_dir = MOVE_DIR::RIGHT;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_W)
		{
			if (static_v_dir == MOVE_DIR::STOP)
				static_v_dir = MOVE_DIR::TOP;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_S)
		{
			if (static_v_dir == MOVE_DIR::STOP)
				static_v_dir = MOVE_DIR::BOTTOM;
		}
	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event*)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_D)
		{
			static_h_dir = MOVE_DIR::STOP;
		}

		if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_S)
		{
			static_v_dir = MOVE_DIR::STOP;
		}
	};
	m_rootNode->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_rootNode);
	return true;
}


bool GGameWorld::initAdmin(int mapId)
{
	auto& admin = m_globalSystem.admin;

	/// 初始化地图组件
	auto& mapComponent = admin.getComponent<MapComponent>();

	if (CommonUtils::initMapSize(admin, mapId) == false)
		return false;

#if G_TARGET_CLIENT
	// 初始化地图渲染
	auto mapLayer = GMapLayer::create(mapId);
	m_rootNode->addChild(mapLayer);
	mapComponent.render = mapLayer;

	m_camera = mapLayer->getVirtualCamera();

	G_ASSERT(std::fabs(mapLayer->getMapWidth() - mapComponent.mapWidth) < 1.0f);
	G_ASSERT(std::fabs(mapLayer->getMapHeight() - mapComponent.mapHeight) < 1.0f);

	/// DebugComponent
	auto& debugComponent = admin.getComponent<DebugComponent>();
	m_debugDrawNode = mapLayer->getDrawNode();
	debugComponent.debugDrawNode = m_debugDrawNode;
#endif

	if (!initBorder())
		return false;

	return true;
}

bool GGameWorld::initPlayer()
{
	for (auto i = 0; i < 4; ++i)
	{
		spawnPlayer();
	}
	return true;
}

bool GGameWorld::spawnPlayer()
{
	anax::Entity entity;

	ActorIdentityInfo info;
	info.bodySize = GVec2(40.0f, 120.0f);
	info.originPos = GVec2(300.0f, 200.0f);
	info.roleName = "A1044";
	CommonUtils::spawnActor(m_world, info, &entity);
	
	entity.activate();
	m_players.push_back(entity);
	return true;
}

void GGameWorld::updateLogic(float32 dt)
{
	m_world.refresh();

	m_SIMPhysSystem.update(dt);
	m_transformSyncSystem.sync();

	m_armatureSystem.update(dt);
	m_collisionSystem.update();


	auto& admin = m_globalSystem.admin;
	auto& mapComponent = admin.getComponent<MapComponent>();

	const float step = 5.0f;

	auto viewPos = m_camera->getPosition();
	if (static_h_dir == MOVE_DIR::LEFT)
	{
		viewPos.x -= step;
	}
	else if (static_h_dir == MOVE_DIR::RIGHT)
	{
		viewPos.x += step;
	}
	if (static_v_dir == MOVE_DIR::TOP)
	{
		viewPos.y += step;
	}
	else if (static_v_dir == MOVE_DIR::BOTTOM)
	{
		viewPos.y -= step;
	}
	m_camera->setPosition(viewPos);
}

void GGameWorld::render()
{
#if G_TARGET_CLIENT
	m_armatureRenderSystem.render();

#if G_DEBUG
	if (m_debugDrawNode)
	{
		m_debugDrawNode->clear();
		m_armatureDebugSystem.debugDraw();
		m_SIMPhysSystem.debugDraw();
	}
#endif
#endif
}


