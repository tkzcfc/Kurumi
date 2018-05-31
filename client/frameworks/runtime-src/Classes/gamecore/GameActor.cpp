#include "GameActor.h"


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
{
	m_armature = NULL;
	m_actorType = GameActorType::AT_NONE;
}

GameActor::~GameActor()
{
	clearLuaHandle();
}

bool GameActor::init()
{
	if (!Node::init())
		return false;
	return true;
}

void GameActor::resetMoveSpeed(float x, float y)
{
	m_gameAttribute.m_curSpeed = Vec2(x, y);

	LuaFunction* handle = getLuaHandle("resetMoveSpeed");
	if (handle)
	{
		handle->ppush();
		handle->pusharg(x);
		handle->pusharg(y);
		handle->pcall();
	}
}

// 附加移动属性
void GameActor::appendMoveSpeed(float x, float y)
{
	m_gameAttribute.m_curSpeed += Vec2(x, y);

	LuaFunction* handle = getLuaHandle("appendMoveSpeed");
	if (handle)
	{
		handle->ppush();
		handle->pusharg(x);
		handle->pusharg(y);
		handle->pcall();
	}
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
	updateMoveLogic(d);
}

bool GameActor::isCanMove()
{
	LuaFunction* handle = getLuaHandle("isCanMove");
	if (handle)
	{
		handle->ppush();
		handle->pcall(1);
		return handle->retbool();
	}
	return true;
}

void GameActor::setOrientation(short ori)
{
	if (m_gameAttribute.m_curOrientation == ori)
		return;
	m_gameAttribute.m_curOrientation = ori;
	
	updateArmatureInfo();
}

void GameActor::updateMoveLogic(float d)
{
	if (isCanMove())
	{
		Vec2 curSpeed = m_gameAttribute.m_curSpeed;
		const Vec2& curPos = this->getActorPosition();

		curSpeed = curSpeed * d;

		this->setActorPosition(curPos + curSpeed);
	}
}

void GameActor::updateArmatureInfo()
{
	if (m_armature == NULL)
		return;

	if(m_gameAttribute.m_curOrientation == GAME_ORI_RIGHT)
		m_armature->setScaleX(1.0);
	else
		m_armature->setScaleX(-1.0);

	LuaFunction* handle = getLuaHandle("updateArmatureInfo");
	if (handle)
	{
		handle->ppush();
		handle->pcall();
	}
}

void GameActor::loadArmature(const std::string& filepath)
{
	if (m_armature)
	{
		m_armature->removeFromParent();
		m_armature = NULL;
	}

	m_gameAttribute.m_curOrientation = GAME_ORI_RIGHT;

	m_armature = cocostudio::Armature::create(filepath);
	m_armature->getAnimation()->playWithIndex(0);
	this->addChild(m_armature);

	LuaFunction* handle = getLuaHandle("loadArmature");
	if (handle)
	{
		handle->ppush();
		handle->pusharg(filepath);
		handle->pcall();
	}

	updateArmatureInfo();
}

GameActorType GameActor::getActorType()
{
	CC_ASSERT(m_actorType != GameActorType::AT_NONE);
	return m_actorType;
}

void GameActor::setActorType(GameActorType type)
{
	m_actorType = type;
}

const Vec2& GameActor::getActorPosition()
{
	return this->getPosition();
}

float GameActor::getActorPositionX()
{
	return getActorPosition().x;
}

float GameActor::getActorPositionY()
{
	return getActorPosition().y;
}

void GameActor::setActorPosition(float x, float y)
{
	setActorPosition(Vec2(x, y));
}

void GameActor::setActorPosition(const Vec2& pos)
{
	this->setPosition(pos);

	LuaFunction* handle = getLuaHandle("setActorPosition");
	if (handle)
	{
		handle->ppush();
		handle->pusharg(pos.x, pos.y);
		handle->pcall();
	}
}

/// 碰撞相关
bool GameActor::getAllDefRECT(std::vector<ActorRect>& actorRectVec)
{
	bool r = false;

	actorRectVec.clear();

	if (m_armature == NULL)
		return false;

	const auto& boneDic = m_armature->getBoneDic();

	for (auto it = boneDic.begin(); it != boneDic.end(); ++it)
	{
		Bone *bone = it->second;
		ColliderDetector *detector = bone->getColliderDetector();

		if (!detector || it->first.find("RECT_HIT") == std::string::npos)
			continue;

		const cocos2d::Vector<ColliderBody*>& bodyList = detector->getColliderBodyList();

		for (auto& object : bodyList)
		{
			ColliderBody *body = static_cast<ColliderBody*>(object);
			const std::vector<Vec2> &vertexList = body->getCalculatedVertexList();

			unsigned long length = vertexList.size();

			ActorRect ar;
			if (length % 4 == 0)
			{
				r = true;
				for (unsigned long i = 0; i < length; i += 4)
				{
					for (unsigned long j = 0; j < 4; ++j)
					{
						Vec2 p = vertexList.at(i + j);
						p = PointApplyAffineTransform(p, this->getNodeToParentAffineTransform());
						ar.v[j].x = p.x;
						ar.v[j].y = p.y;
					}
					actorRectVec.push_back(ar);
				}
			}
		}
	}

	return r;
}

bool GameActor::getAllAttRECT(std::vector<ActorRect>& actorRectVec)
{
	bool r = false;

	actorRectVec.clear();

	if (m_armature == NULL)
		return false;

	const auto& boneDic = m_armature->getBoneDic();

	for (auto it = boneDic.begin(); it != boneDic.end(); ++it)
	{
		Bone *bone = it->second;
		ColliderDetector *detector = bone->getColliderDetector();

		if (!detector || it->first.find("RECT_ATK_") == std::string::npos)
			continue;

		const cocos2d::Vector<ColliderBody*>& bodyList = detector->getColliderBodyList();

		for (auto& object : bodyList)
		{
			ColliderBody *body = static_cast<ColliderBody*>(object);
			const std::vector<Vec2> &vertexList = body->getCalculatedVertexList();

			unsigned long length = vertexList.size();

			ActorRect ar;
			if (length % 4 == 0)
			{
				r = true;
				for (unsigned long i = 0; i < length; i += 4)
				{
					for (unsigned long j = 0; j < 4; ++j)
					{
						Vec2 p = vertexList.at(i + j);
						p = PointApplyAffineTransform(p, this->getNodeToParentAffineTransform());
						ar.v[j].x = p.x;
						ar.v[j].y = p.y;
					}
					actorRectVec.push_back(ar);
				}
			}
		}
	}
	return r;
}

bool GameActor::AABBTest(const Rect& r)
{
	const Rect& r1 = getAABB();
	return r1.intersectsRect(r);
}

const Rect& GameActor::getAABB()
{
	if (m_armature == NULL)
		return Rect::ZERO;
	Rect r = m_armature->getBoundingBox();
	return RectApplyTransform(r, this->getNodeToParentTransform());
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

void GameActor::registerLuaHandle(const std::string& name, const LuaFunction& handle)
{
	unregisterLuaHandle(name);

	LuaFunction* pHandle = new LuaFunction(handle);
	m_luaHandleMap.insert(std::make_pair(name, pHandle));
}

void GameActor::unregisterLuaHandle(const std::string& name)
{
	auto it = m_luaHandleMap.find(name);
	if (it != m_luaHandleMap.end())
	{
		delete it->second;
		m_luaHandleMap.erase(it);
	}
}

const Vec2& GameActor::getMapMovePos()
{
	if (m_armature == NULL)
		return getActorPosition();
	else
		return getActorPosition() + m_armature->getPosition();
}

void GameActor::clearLuaHandle()
{
	for (const auto& it : m_luaHandleMap)
		delete it.second;
	m_luaHandleMap.clear();
}

LuaFunction* GameActor::getLuaHandle(const std::string& name)
{
	auto it = m_luaHandleMap.find(name);
	if (it != m_luaHandleMap.end())
	{
		return it->second;
	}
	return NULL;
}

