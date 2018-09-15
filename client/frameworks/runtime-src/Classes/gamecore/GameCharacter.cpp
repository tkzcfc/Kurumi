#include "GameCharacter.h"
#include "GameWord.h"


GameCharacter::GameCharacter()
	: m_armature(NULL)
	, m_isLockOrientation(false)
	, m_curOrientation(GAME_ORI_RIGHT)
	, m_ignoreBodyRotation(false)
	, m_pB2Body(nullptr)
	, m_syncTransform(nullptr)
{
}

GameCharacter::~GameCharacter()
{
	if (m_pB2Body)
	{
		GameWord* world = getGameWord();
		if (world)
		{
			world->addDiscardB2Body(m_pB2Body);
		}
		m_pB2Body = NULL;
	}
}

GameCharacter* GameCharacter::create()
{
	GameCharacter* ret = new GameCharacter();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return NULL;
}

void GameCharacter::initCharacterByData(const std::string& filepath, const Size& characterSize, const Vec2& characterPosition)
{
	loadArmature(filepath);

	auto gameworld = getGameWord();
	CC_ASSERT(gameworld != NULL);

	m_characterSize = characterSize;

	const Rect& r = gameworld->getGameWorldValidRect();
	float minx = r.origin.x + characterSize.width;
	float maxx = r.origin.x + r.size.width - characterSize.width;
	float miny = r.origin.y;
	float maxy = r.origin.y + r.size.height - characterSize.height;
	Vec2 pos = characterPosition;
	pos.x = MAX(pos.x, minx);
	pos.x = MIN(pos.x, maxx);
	pos.y = MAX(pos.y, miny);
	pos.y = MIN(pos.y, maxy);

	b2BodyDef bodydef;
	bodydef.bullet = false;
	bodydef.allowSleep = true;
	bodydef.fixedRotation = true;
	bodydef.type = b2_dynamicBody;
	bodydef.position.x = pos.x / PIXEL_TO_METER;
	bodydef.position.y = pos.y / PIXEL_TO_METER;

	b2Body* body = gameworld->getPhysicsWorld()->CreateBody(&bodydef);
	this->setB2Body(body);

	const float box_w = characterSize.width / PIXEL_TO_METER;
	const float box_h = characterSize.height / PIXEL_TO_METER;

	b2PolygonShape shape;
	shape.SetAsBox(box_w, box_h, b2Vec2(0.0f, box_h), 0.0f);
	b2FixtureDef fixdef;
	fixdef.shape = &shape;
	fixdef.userData = this;
	b2Fixture* fixture = body->CreateFixture(&fixdef);

	LuaFunction* handle = getLuaHandle("loadActorFinish");
	if (handle)
	{
		handle->ppush();
		handle->pcall();
	}
}

bool GameCharacter::isInAir()
{
	auto gameworld = getGameWord();
	CC_ASSERT(gameworld != NULL);

	static const float deviation = 2.0f;
	const Rect& r = gameworld->getGameWorldValidRect();

	float subv = getPositionY() - r.origin.y;

	if (subv < -deviation)
		return true;

	if (subv < deviation)
		return false;
	return true;
}

void GameCharacter::setActorPositionInValidRect(const Vec2& actorPosition)
{
	auto gameworld = getGameWord();
	CC_ASSERT(gameworld != NULL);

	const Rect& r = gameworld->getGameWorldValidRect();
	float minx = r.origin.x + m_characterSize.width;
	float maxx = r.origin.x + r.size.width - m_characterSize.width;
	float miny = r.origin.y;
	float maxy = r.origin.y + r.size.height - m_characterSize.height;
	Vec2 pos = actorPosition;
	pos.x = MAX(pos.x, minx);
	pos.x = MIN(pos.x, maxx);
	pos.y = MAX(pos.y, miny);
	pos.y = MIN(pos.y, maxy);
	this->setPosition(pos);
}

void GameCharacter::setOrientation(int ori)
{
	if (m_isLockOrientation || m_curOrientation == ori)
		return;
	m_curOrientation = ori;

	updateArmatureInfo();
}

void GameCharacter::updateArmatureInfo()
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

void GameCharacter::loadArmature(const std::string& filepath)
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

bool GameCharacter::getAllDefRECT(std::vector<ActorRect>& actorRectVec)
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

bool GameCharacter::getAllAttRECT(std::vector<ActorRect>& actorRectVec)
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

const Rect& GameCharacter::getAABB()
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