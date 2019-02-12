#include "GameWorldBase.h"
#include "foundation/Actor.h"

GameWorldBase::GameWorldBase()
{}

GameWorldBase::~GameWorldBase()
{
	m_world.removeAllSystems();
	onWorldDestroy();
}

GameWorldBase* GameWorldBase::create()
{
	GameWorldBase* w = new GameWorldBase();
	if (w && w->init())
	{
		w->autorelease();
		return w;
	}
	CC_SAFE_DELETE(w);
	return w;
}

bool GameWorldBase::init()
{
	if (Node::init() == false)
	{
		return false;
	}

	_scheduler->schedule(CC_SCHEDULE_SELECTOR(GameWorldBase::logicUpdate), this, 1.0f / 60.0f, false);

	m_admin = m_world.createEntity();

	for (int i = GAMEWORLD_NODE_MAP; i < GAMEWORLD_NODE_MAX; ++i)
	{
		m_nodeArr[i] = Node::create();
		this->addChild(m_nodeArr[i], i - 1);
	}

	return true;
}

void GameWorldBase::destroy(class Actor* actor)
{
	m_destroyActorList.pushBack(actor);
}

void GameWorldBase::logicUpdate(float delta)
{
	clearDestroyList();
	m_world.refresh();
	callLuaLogicUpdate(delta);
}

void GameWorldBase::onWorldDestroy()
{
	auto handle = getLuaHandle("onWorldDestroy");
	if (handle)
	{
		handle->ppush();
		handle->pcall();
	}
	else
	{
		CC_ASSERT(0);
	}
}

void GameWorldBase::clearDestroyList()
{
	if (m_destroyActorList.empty())
	{
		return;
	}
	for (auto &it : m_destroyActorList)
	{
		it->removeFromParent();
	}
	m_destroyActorList.clear();
}

void GameWorldBase::callLuaLogicUpdate(float delta)
{
	auto logicUpdateHandle = getLuaHandle("logicUpdate");
	if (logicUpdateHandle != NULL)
	{
		logicUpdateHandle->ppush();
		logicUpdateHandle->pusharg(delta);
		logicUpdateHandle->pcall();
	}
}

