#include "GameWord.h"
#include "GameMath.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"

static GameWord* Static__GameWord = NULL;

GameWord::GameWord()
	: m_gameMap(NULL)
#ifdef ENABLE_GAME_WORD_DEBUG
	, m_physicsDebugDraw(NULL)
#endif
	, m_player(NULL)
	, m_world(NULL)
	, m_isUpdate(false)
{
	Static__GameWord = this;
}

GameWord::~GameWord()
{
	//CCLOG("GameWord::~GameWord");
	m_destroyActor.clear();
	m_allActor.clear();
	m_discardB2BodyList.clear();
	CC_SAFE_DELETE(m_world);

#ifdef ENABLE_GAME_WORD_DEBUG
	CC_SAFE_DELETE(m_physicsDebugDraw);
#endif
	if (Static__GameWord == this)
	{
		Static__GameWord = NULL;
	}
}

GameWord* GameWord::create()
{
	GameWord* ret = new GameWord();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return NULL;
}

bool GameWord::init()
{
	if (!Node::init())
		return false;
	do
	{
		this->setName("GameWord");

		m_defRectCache.reserve(10);
		m_attRectCache.reserve(10);
		
#ifdef ENABLE_GAME_WORD_DEBUG
		m_debugDraw = DrawNode::create();
		this->addChild(m_debugDraw, 1);
#endif

		this->schedule(schedule_selector(GameWord::logicUpdate), PHYSICS_WORLD_FPS);

		m_winSize = Director::getInstance()->getVisibleSize();

		return true;
	} while (0);
	return false;
}

void GameWord::initGameWorld(GameMap* map, float left_offset, float right_offset)
{
	this->addChild(map);
	this->m_gameMap = map;
	this->initPhysics(left_offset, right_offset, 0.0f, map->getMinPosY());
	
	m_worldValidRect.origin.x = left_offset;
	m_worldValidRect.origin.y = map->getMinPosY();
	m_worldValidRect.size.width = map->getMapWidth() - left_offset - right_offset;
	m_worldValidRect.size.height = map->getMapHeight() - map->getMinPosY();
}

void GameWord::initPhysics(float left_offset, float right_offset, float top_offset, float bottom_offset)
{
	// ³õÊ¼»¯box2d
	m_world = new b2World(b2Vec2(PHYSICS_WORLD_GRAVITY_X, PHYSICS_WORLD_GRAVITY_Y));
	m_world->SetAllowSleeping(true);
	m_world->SetWarmStarting(true);
	m_world->SetContinuousPhysics(true);

#ifdef ENABLE_GAME_WORD_DEBUG
	m_physicsDebugDraw = new GLESDebugDraw(PIXEL_TO_METER);
	m_physicsDebugDraw->AppendFlags(b2Draw::e_shapeBit);
	//m_physicsDebugDraw->AppendFlags(b2Draw::e_jointBit);
	//m_physicsDebugDraw->AppendFlags(b2Draw::e_aabbBit);
	//m_physicsDebugDraw->AppendFlags(b2Draw::e_pairBit);
	//m_physicsDebugDraw->AppendFlags(b2Draw::e_centerOfMassBit);
	m_world->SetDebugDraw(m_physicsDebugDraw);
#endif

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2EdgeShape groundBox;
	
	const float world_width = m_gameMap->getMapWidth();
	const float world_height = m_gameMap->getMapHeight();
	const float left_offsetValue = left_offset;
	const float right_offsetValue = right_offset;
	const float bottom_offsetValue = bottom_offset;
	const float top_offsetValue = top_offset;

	Vec2 LB(left_offsetValue, bottom_offsetValue);
	Vec2 LT(left_offsetValue, world_height - top_offsetValue);
	Vec2 RB(world_width - right_offsetValue, bottom_offsetValue);
	Vec2 RT(world_width - right_offsetValue, world_height - top_offsetValue);

	// bottom
	groundBox.Set(b2Vec2(LB.x / PIXEL_TO_METER, LB.y / PIXEL_TO_METER), b2Vec2(RB.x / PIXEL_TO_METER, RB.y / PIXEL_TO_METER));
	groundBody->CreateFixture(&groundBox, 0);

	// top
	groundBox.Set(b2Vec2(LT.x / PIXEL_TO_METER, LT.y / PIXEL_TO_METER), b2Vec2(RT.x / PIXEL_TO_METER, RT.y / PIXEL_TO_METER));
	groundBody->CreateFixture(&groundBox, 0);

	// left
	groundBox.Set(b2Vec2(LT.x / PIXEL_TO_METER, LT.y / PIXEL_TO_METER), b2Vec2(LB.x / PIXEL_TO_METER, LB.y / PIXEL_TO_METER));
	groundBody->CreateFixture(&groundBox, 0);

	// right
	groundBox.Set(b2Vec2(RB.x / PIXEL_TO_METER, RB.y / PIXEL_TO_METER), b2Vec2(RT.x / PIXEL_TO_METER, RT.y / PIXEL_TO_METER));
	groundBody->CreateFixture(&groundBox, 0);
}

void GameWord::addActor(GameActor* actor)
{
	getActorNode()->addChild(actor);
	m_allActor.pushBack(actor);
}

void GameWord::removeActor(GameActor* actor)
{
	if (actor == NULL)
	{
		return;
	}
	if (m_isUpdate)
	{
		m_destroyActor.push_back(actor);
		return;
	}
	actor->removeFromParent();
	m_allActor.eraseObject(actor);
}

void GameWord::setLocalPlayer(GameActor* player)
{
	m_player = player;
}

int GameWord::getPlayerCount()
{
	int outCount = 0;
	for (int i = 0; i < (int)m_allActor.size(); ++i)
	{
		if (m_allActor.at(i)->getActorType() == GameActorType::AT_PLAYER)
		{
			outCount++;
		}
	}
	return outCount;
}

GameActor* GameWord::getPlayerByIndex(int index)
{
	int count = 0;
	for (int i = 0; i < (int)m_allActor.size(); ++i)
	{
		if (m_allActor.at(i)->getActorType() == GameActorType::AT_PLAYER)
		{
			count++;
			if (count == index)
				return m_allActor.at(i);
		}
	}
	return NULL;
}

void GameWord::removeActorByName(const std::string& name)
{
	GameActor* actor = dynamic_cast<GameActor*>(getActorNode()->getChildByName(name));
	removeActor(actor);
}

Node* GameWord::getChildNode(const std::string& name)
{
	return findChild(this, name);
}

Node* GameWord::findChild(Node* root, const std::string& name)
{
	Node* node = root->getChildByName(name);
	if (node != NULL)
	{
		return node;
	}
	auto& child = root->getChildren();
	for (auto& it : child)
	{
		//CCLOG("%s", it->getName().c_str());
		node = findChild(it, name);
		if (node)
			return node;
	}
	return NULL;
}

void GameWord::logicUpdate(float d)
{
	if (m_world)
	{
		m_world->Step(d, 4, 4);
		clearDiscardB2BodyList();
	}

	// ½ÇÉ«Âß¼­
	if (!m_destroyActor.empty())
	{
		for (auto& it : m_destroyActor)
		{
			removeActor(it);
		}
		m_destroyActor.clear();
	}

	m_isUpdate = true;
	for (auto& it : m_allActor)
	{
		it->logicUpdate(d);
	}
	m_isUpdate = false;

	// µØÍ¼ÒÆ¶¯
	updateMapMoveLogic();

#ifdef ENABLE_GAME_WORD_DEBUG
	// debug
	if (m_debugDraw->isVisible())
	{
		debugDraw();
	}
#endif

	// Åö×²¼ì²â
	collisionTest();
}

void GameWord::openDebugDraw(bool open)
{
#ifdef ENABLE_GAME_WORD_DEBUG
	if (m_debugDraw->isVisible() == open)
		return;
	m_debugDraw->clear();
	m_debugDraw->setVisible(open);
#endif
}

bool GameWord::isOpenDebugDraw()
{
#ifdef ENABLE_GAME_WORD_DEBUG
	return m_debugDraw->isVisible();
#else
	return false;
#endif
}

void GameWord::updateMapMoveLogic()
{
	// µØÍ¼¸úËæÍæ¼ÒÒÆ¶¯
	if (m_player)
	{
		const Vec2& v = m_player->getPosition();
		m_gameMap->setViewPos(v.x, v.y);
#ifdef ENABLE_GAME_WORD_DEBUG
		m_debugDraw->setPosition(m_gameMap->getRootNode()->getPosition());
#endif
	}
}

#ifdef ENABLE_GAME_WORD_DEBUG
void GameWord::debugDraw()
{
	m_debugDraw->clear();
	Rect rect;

	std::vector<ActorRect> V;

	for (auto& it : m_allActor)
	{
		rect = it->getAABB();

		cocos2d::Vec2 leftbottom(rect.getMinX(), rect.getMinY());
		cocos2d::Vec2 righttop(rect.getMaxX(), rect.getMaxY());
		m_debugDraw->drawRect(leftbottom, righttop, cocos2d::Color4F::WHITE);

		if (it->getAllDefRECT(V))
		{
			for (auto& v : V)
			{
				m_debugDraw->drawPoly(&v.v[0], 4U, true, Color4F::BLUE);
			}
		}
		if (it->getAllAttRECT(V))
		{
			for (auto& v : V)
			{
				m_debugDraw->drawPoly(&v.v[0], 4U, true, Color4F::GREEN);
			}
		}
	}
}

void GameWord::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
	Node::draw(renderer, transform, flags);

	if (m_world == NULL || !m_debugDraw->isVisible())
		return;

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	_modelViewMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	_customCommand.init(_globalZOrder + 1);
	_customCommand.func = CC_CALLBACK_0(GameWord::onDraw, this);
	renderer->addCommand(&_customCommand);

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void GameWord::onDraw()
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");

	auto oldMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewMV);
	director->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, m_gameMap->getRootNode()->getNodeToParentTransform());
	m_world->DrawDebugData();
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, oldMV);
}

#endif

void GameWord::collisionTest()
{
#ifdef ENABLE_GAME_WORD_DEBUG
	bool debug = m_debugDraw->isVisible();
#endif

	Rect r;
	GameActor* A, *B;

	int count = m_allActor.size();
	for (int i = 0; i < count; ++i)
	{
		A = m_allActor.at(i);
		r = A->getAABB();
		for (int j = i + 1; j < count; ++j)
		{
			B = m_allActor.at(j);
			if (A->isRunAABB(B) && B->AABBTest(r))
			{
				A->AABBCallback(B);
				B->AABBCallback(A);
#ifdef ENABLE_GAME_WORD_DEBUG
				if (debug)
				{
					cocos2d::Vec2 leftbottom(r.getMinX(), r.getMinY());
					cocos2d::Vec2 righttop(r.getMaxX(), r.getMaxY());
					m_debugDraw->drawRect(leftbottom, righttop, cocos2d::Color4F::GRAY);

					r = B->getAABB();
					leftbottom = cocos2d::Vec2(r.getMinX(), r.getMinY());
					righttop = cocos2d::Vec2(r.getMaxX(), r.getMaxY());
					m_debugDraw->drawRect(leftbottom, righttop, cocos2d::Color4F::GRAY);
				}
#endif

				GameActor* att = B;
				GameActor* def = A;
				if (A->attLevelTest(B))
				{
					att = A;
					def = B;
				}

				att->getAllAttRECT(m_attRectCache);
				def->getAllDefRECT(m_defRectCache);

				bool breakCollision = false;
				for (const auto& attR : m_attRectCache)
				{
					for(const auto& defR : m_defRectCache)
					{
						if (GameMath_IsIntersect(&attR.v[0], &defR.v[0]))
						{
#ifdef ENABLE_GAME_WORD_DEBUG
							if (debug)
							{
								m_debugDraw->drawPoly(&attR.v[0], 4U, true, Color4F::RED);
								m_debugDraw->drawPoly(&defR.v[0], 4U, true, Color4F::RED);
							}
#endif

							breakCollision = att->attOtherActorCallback(def);
						}
					}
				}

				if(breakCollision)
					continue;

				att = (att == A) ? B : A;
				def = (def == A) ? B : A;

				att->getAllAttRECT(m_attRectCache);
				def->getAllDefRECT(m_defRectCache);

				for (const auto& attR : m_attRectCache)
				{
					for (const auto& defR : m_defRectCache)
					{
						if (GameMath_IsIntersect(&attR.v[0], &defR.v[0]))
						{
#ifdef ENABLE_GAME_WORD_DEBUG
							if (debug)
							{
								m_debugDraw->drawPoly(&attR.v[0], 4U, true, Color4F::RED);
								m_debugDraw->drawPoly(&defR.v[0], 4U, true, Color4F::RED);
							}
#endif
							att->attOtherActorCallback(def);
						}
					}
				}
			}
		}
	}
}

void GameWord::updateActors()
{
	for (size_t i = 0; i < m_allActor.size(); i++)
	{
		if (m_allActor.at(i)->getActorType() == GameActorType::AT_PLAYER)
		{
			m_allActor.at(i)->setLocalZOrder(10);
		}
		else
		{
			m_allActor.at(i)->setLocalZOrder(0);
		}
	}
}

void GameWord::addDiscardB2Body(b2Body* body)
{
	auto it = std::find(m_discardB2BodyList.begin(), m_discardB2BodyList.end(), body);
	if (it == m_discardB2BodyList.end())
	{
		m_discardB2BodyList.push_back(body);
	}
}

void GameWord::clearDiscardB2BodyList()
{
	for (auto& it : m_discardB2BodyList)
	{
		m_world->DestroyBody(it);
	}
	m_discardB2BodyList.clear();
}


//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////
GameWord* getGameWord()
{
	return Static__GameWord;
}

void __changeParticleSystemPositionType(Node* root)
{
	if (root == NULL)
		return;

	auto particleSys = dynamic_cast<ParticleSystem*>(root);
	if (particleSys)
	{
		particleSys->setPositionType(ParticleSystem::PositionType::GROUPED);
	}

	auto& child = root->getChildren();
	for (auto& it : child)
	{
		__changeParticleSystemPositionType(it);
	}
}

void changeParticleSystemPositionType(Node* root)
{
	if (root == NULL)
		return;

	auto armature = dynamic_cast<Armature*>(root);
	if (armature)
	{
		//CCLOG("armature name = [%s]", armature->getName().c_str());
		auto& boneDic = armature->getBoneDic();
		for (auto& it : boneDic)
		{
			__changeParticleSystemPositionType(it.second->getDisplayRenderNode());
		}
	}

	auto& child = root->getChildren();
	for (auto& it : child)
	{
		changeParticleSystemPositionType(it);
	}
}
