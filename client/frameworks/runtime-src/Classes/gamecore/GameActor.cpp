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
{
	m_word = NULL;
	m_armature = NULL;
	m_actorType = GameActorType::AT_NONE;
	m_isLockOrientation = false;
	m_isMapConstraintEnable = true;
	m_curOrientation = GAME_ORI_RIGHT;
}

GameActor::~GameActor()
{
	//if (m_pB2Body)
	//{
	//	m_pB2Body->GetWorld()->DestroyBody(m_pB2Body);
	//	m_pB2Body = NULL;
	//}
}

bool GameActor::init()
{
	if (!Node::init())
		return false;
	
	b2BodyDef bodydef;
	bodydef.bullet = false;
	bodydef.allowSleep = true;
	bodydef.fixedRotation = true;
	bodydef.type = b2_dynamicBody;

	this->setPTMRatio(PIXEL_TO_METER);

	auto gameworld = ::getGameWord();
	b2Body* body = gameworld->getPhysicsWorld()->CreateBody(&bodydef);
	this->setB2Body(body);

	return true;
}

void GameActor::logicUpdate(float d)
{
	//syncPhysicsTransform();
	LuaFunction* handle = getLuaHandle("logicUpdate");
	if (handle)
	{
		handle->ppush();
		handle->pusharg(d);
		handle->pcall();
	}
}

void GameActor::setOrientation(int ori)
{
	if (m_isLockOrientation || m_curOrientation == ori)
		return;
	m_curOrientation = ori;
	
	updateArmatureInfo();
}

void GameActor::updateArmatureInfo()
{
	if (m_armature)
	{
		if (m_curOrientation == GAME_ORI_RIGHT)
			m_armature->setScaleX(1.0);
		else
			m_armature->setScaleX(-1.0);
	}

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

	m_curOrientation = GAME_ORI_RIGHT;

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
	if (m_word)
	{
		m_word->updateActors();
	}
}

/// Åö×²Ïà¹Ø
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
	static Rect r;
	r = m_armature->getBoundingBox();
	r = RectApplyTransform(r, this->getNodeToParentTransform());
	r.origin.x = r.origin.x - r.size.width * 0.5f;
	r.size.width *= 2;
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

void GameActor::createPhysicsBox()
{
	if (m_word == NULL)
		return;

	b2World* world = m_word->getPhysicsWorld();

	b2PolygonShape shape;
	shape.SetAsBox(100.0f / m_PTMRatio, 200.0f / m_PTMRatio);
	b2FixtureDef fixdef;
	fixdef.shape = &shape;
	fixdef.userData = this;
	b2Fixture* fixture = m_pB2Body->CreateFixture(&fixdef);
}

