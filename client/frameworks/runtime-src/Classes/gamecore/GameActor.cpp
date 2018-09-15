#include "GameActor.h"
#include "GameWord.h"


GameActor* GameActor::create()
{
	GameActor* ret = new GameActor();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return NULL;
}

GameActor::GameActor()
	: m_actorType(GameActorType::AT_NONE)
	, m_collisionEnable(false)
{
}

GameActor::~GameActor()
{}

bool GameActor::init()
{
	if (!Node::init())
		return false;
	return true;
}


void GameActor::logicUpdate(float d)
{
	LuaFunction* handle = getLuaHandle("logicUpdate");
	if (handle)
	{
		handle->ppush();
		handle->pusharg(d);
		handle->pcall();
	}
}


GameActorType GameActor::getActorType()
{
	CC_ASSERT(m_actorType != GameActorType::AT_NONE);
	return m_actorType;
}

void GameActor::setActorType(GameActorType type)
{
	m_actorType = type;
	getGameWord()->updateActors();
}

/// Åö×²Ïà¹Ø
bool GameActor::getAllDefRECT(std::vector<ActorRect>& actorRectVec)
{
	return false;
}

bool GameActor::getAllAttRECT(std::vector<ActorRect>& actorRectVec)
{
	return false;
}

bool GameActor::AABBTest(const Rect& r)
{
	const Rect& r1 = getAABB();
	return r1.intersectsRect(r);
}

const Rect& GameActor::getAABB()
{
	static Rect r;
	r = getBoundingBox();
	return r;
}

bool GameActor::isRunAABB(GameActor* other)
{
	LuaFunction* handle = getLuaHandle("isRunAABB");
	if (handle)
	{
		handle->ppush();
		handle->pushusertype(other, "GameActor");
		handle->pcall(1);

		return handle->retbool();
	}
	return (m_actorType != other->m_actorType);
}

bool GameActor::attLevelTest(GameActor* other)
{
	LuaFunction* handle = getLuaHandle("attLevelTest");
	if (handle)
	{
		handle->ppush();
		handle->pushusertype(other, "GameActor");
		handle->pcall(1);

		return handle->retbool();
	}
	return m_actorType > other->getActorType();
}

void GameActor::AABBCallback(GameActor* other)
{
	LuaFunction* handle = getLuaHandle("AABBCallback");
	if (handle)
	{
		handle->ppush();
		handle->pushusertype(other, "GameActor");
		handle->pcall();
	}
}

bool GameActor::attOtherActorCallback(GameActor* other)
{
	LuaFunction* handle = getLuaHandle("attOtherActorCallback");
	if (handle)
	{
		handle->ppush();
		handle->pushusertype(other, "GameActor");
		handle->pcall(1);

		return handle->retbool();
	}
	return true;
}


