#include "TestArmature.h"
#include "foundation/animator/GAnimCMD.h"
#include "ecs/utils/ArmatureUtils.h"
#include "ecs/utils/CommonUtils.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

Scene* TestArmature::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TestArmature::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


// on "init" you need to initialize your instance
bool TestArmature::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}


	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("rect_collide.plist");

	_scheduler->schedule(CC_SCHEDULE_SELECTOR(TestArmature::logicUpdate), this, 1.0f / 60.0f, false);


	m_world.addSystem<ArmatureSystem>(m_armatureSystem);
	m_world.addSystem<ArmatureRenderSystem>(m_armatureRenderSystem);
	m_world.addSystem<ArmatureDebugSystem>(m_armatureDebugSystem);
	m_world.addSystem<CollisionSystem>(m_collisionSystem);
	m_world.addSystem<GlobalSystem>(m_globalSystem);
	m_world.addSystem<TransformSyncSystem>(m_transformSyncSystem);
	m_world.addSystem<RenderSyncSystem>(m_renderSyncSystem);
	
	m_isFirst = true;

	this->runAction(Sequence::createWithTwoActions(
		DelayTime::create(0.1),
		CallFunc::create([=]() 
	{
		auto& component = m_globalSystem.admin.getComponent<UniqueComponent>();
		component.stageNode = Node::create();
		this->addChild(component.stageNode);
		spawnPlayer();
	}
	)));

	m_drawNode = DrawNode::create();
	this->addChild(m_drawNode);

	auto& admin = CommonUtils::getAdmin(m_world);
	admin.getComponent<DebugComponent>().debugDrawNode = m_drawNode;

	return true;
}

void TestArmature::spawnPlayer()
{
	auto player = m_world.createEntity();

	ArmatureUtils::initAnimationComponent(player);

	auto& transform = player.addComponent<TransformComponent>();
	Vec2 pos = Director::getInstance()->getWinSize() * 0.5f;
	pos.y *= 0.5f;
	transform.logicPos.x = pos.x;
	transform.logicPos.y = pos.y;
	transform.position.x = pos.x;
	transform.position.y = pos.y;

	player.activate();
	m_world.refresh();

	m_player = player;

	this->initMenu();
}

void TestArmature::initMenu()
{
	auto winSize = Director::getInstance()->getWinSize();

	auto meun = Menu::create();

	const auto& roleList = GAnimCMDCache::getInstance()->getAllRole();

	Size size(100, 60);
	float space = 30.0f;
	for (auto &it : roleList)
	{
		auto item = MenuItemFont::create(it);
		item->setName(it);
		item->setCallback(std::bind(&TestArmature::onMenuItemClickRole, this, std::placeholders::_1));
		meun->addChild(item);

		size.width += item->getContentSize().width;
		size.width += space;
	}
	meun->setContentSize(size);
	meun->alignItemsHorizontallyWithPadding(space);
	meun->setAnchorPoint(Vec2::ZERO);
	meun->setPosition(size * 0.5f);
	
	auto scrollView = ui::ScrollView::create();
	scrollView->addChild(meun);
	scrollView->setInnerContainerSize(size);
	scrollView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	scrollView->setClippingEnabled(true);
	scrollView->setBounceEnabled(true);
	scrollView->setContentSize(Size(winSize.width - 100, 60));
	scrollView->setAnchorPoint(Vec2(0.5f, 0.0f));
	scrollView->setPosition(Vec2(winSize.width * 0.5f, 0.0f));
	scrollView->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
	scrollView->setBackGroundColor(Color3B(152, 245, 255));
	this->addChild(scrollView);
}

void TestArmature::updateCMDMenu()
{
	if (m_curRoleName.empty())
		return;

	ArmatureUtils::changeRole(m_player, m_curRoleName);

	this->removeChildByTag(100);

	auto cmd = GAnimCMDCache::getInstance()->getOrCreate(m_curRoleName);
	if (cmd == NULL)
		return;

	auto winSize = Director::getInstance()->getWinSize();

	auto meun = Menu::create();

	Size size(100, 60);
	float space = 30.0f;
	MenuItemFont* firstItem = NULL;
	for (auto& it : cmd->m_cmdData)
	{
		auto item = MenuItemFont::create(it.first);
		item->setName(it.first);
		item->setCallback(std::bind(&TestArmature::onMenuItemClickCMD, this, std::placeholders::_1));
		meun->addChild(item);

		size.width += item->getContentSize().width;
		size.width += space;
		if (firstItem == NULL) firstItem = item;
	}
	meun->setContentSize(size);
	meun->alignItemsHorizontallyWithPadding(space);
	meun->setAnchorPoint(Vec2::ZERO);
	meun->setPosition(size * 0.5f);

	auto scrollView = ui::ScrollView::create();
	scrollView->addChild(meun);
	scrollView->setInnerContainerSize(size);
	scrollView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	scrollView->setClippingEnabled(true);
	scrollView->setBounceEnabled(true);
	scrollView->setContentSize(Size(winSize.width - 100, 60));
	scrollView->setAnchorPoint(Vec2(0.5f, 0.0f));
	scrollView->setPosition(Vec2(winSize.width * 0.5f, 100.0f));
	scrollView->setTag(100);
	scrollView->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
	scrollView->setBackGroundColor(Color3B(255, 218, 185));
	this->addChild(scrollView);

	onMenuItemClickCMD(firstItem);
}

void TestArmature::onMenuItemClickRole(Ref* sender)
{
	auto item = dynamic_cast<MenuItemFont*>(sender);
	if (item == NULL) return;
	
	const auto& name = item->getName();

	auto& children = item->getParent()->getChildren();
	for (auto& it : children)
	{
		item = dynamic_cast<MenuItemFont*>(it);
		if (item)
		{
			if (item == sender)
				item->setColor(Color3B::RED);
			else
				item->setColor(Color3B::WHITE);
		}
	}

	if (m_curRoleName != name)
	{
		m_curRoleName = name;
		updateCMDMenu();
	}
}

void TestArmature::onMenuItemClickCMD(Ref* sender)
{
	auto item = dynamic_cast<MenuItemFont*>(sender);
	if (item == NULL) return;

	const auto& name = item->getName();

	auto& children = item->getParent()->getChildren();
	for (auto& it : children)
	{
		item = dynamic_cast<MenuItemFont*>(it);
		if (item)
		{
			if (item == sender)
				item->setColor(Color3B::RED);
			else
				item->setColor(Color3B::WHITE);
		}
	}
	if (m_curCMDName != name)
	{
		m_curCMDName = name;
		ArmatureUtils::playAnimationCMD(m_player, m_curCMDName, kArmaturePlayMode::ONCE);
	}
}

void TestArmature::logicUpdate(float delta)
{
	m_world.refresh();
	m_drawNode->clear();
	m_armatureSystem.update(delta);
	m_transformSyncSystem.sync();
	m_renderSyncSystem.sync();
	m_armatureRenderSystem.render();
	m_armatureDebugSystem.debugDraw();
}

