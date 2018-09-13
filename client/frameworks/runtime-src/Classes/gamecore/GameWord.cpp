#include "GameWord.h"
#include "GameMath.h"

static GameWord* Static__GameWord = NULL;

GameWord::GameWord()
{
	m_gameMap = NULL;
	m_player = NULL;
	m_world = NULL;
	Static__GameWord = this;
	m_viewPortMinX = m_viewPortMaxX = 0.0f;
	m_minPosY = 0.0f;
}

GameWord::~GameWord()
{
	//CCLOG("GameWord::~GameWord");
	if (Static__GameWord == this)
	{
		Static__GameWord = NULL;
	}
	if (m_world)
	{
		delete m_world;
		m_world = NULL;
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

		this->schedule(schedule_selector(GameWord::logicUpdate), 1 / 60.0f);

		m_winSize = Director::getInstance()->getVisibleSize();

		return true;
	} while (0);
	return false;
}

void GameWord::setGameMap(GameMap* map)
{
	if (m_gameMap)
		return;

	this->addChild(map);
	m_gameMap = map;

	m_viewPortMinX = 0.0f;
	m_viewPortMaxX = m_gameMap->getMapWidth();

	// 初始化box2d
	m_world = new b2World(b2Vec2(0.0f, -10.0f / PIXEL_TO_METER));
	m_world->SetAllowSleeping(true);
	m_world->SetWarmStarting(true);

	b2BodyDef wallDef;   //刚体定义
	wallDef.position.Set(0, 0);  //位置

	b2Body* wallBody = m_world->CreateBody(&wallDef);   //创建一个刚体（四周墙体）

	float halfMapWidth = m_gameMap->getMapWidth();
	float halfMapHeight = m_gameMap->getMapHeight();

	b2EdgeShape wallShape;   //形状
	//下
	wallShape.Set(b2Vec2(-halfMapWidth / PIXEL_TO_METER, (-halfMapHeight + m_minPosY) / PIXEL_TO_METER), b2Vec2(halfMapWidth / PIXEL_TO_METER, (-halfMapHeight + m_minPosY) / PIXEL_TO_METER));
	wallBody->CreateFixture(&wallShape, 0.0f);
	//上
	wallShape.Set(b2Vec2(-halfMapWidth / PIXEL_TO_METER, halfMapHeight / PIXEL_TO_METER), b2Vec2(halfMapWidth / PIXEL_TO_METER, halfMapHeight / PIXEL_TO_METER));
	wallBody->CreateFixture(&wallShape, 0.0f);
	//左
	wallShape.Set(b2Vec2(-halfMapWidth / PIXEL_TO_METER, halfMapHeight / PIXEL_TO_METER), b2Vec2(-halfMapWidth / PIXEL_TO_METER, -halfMapHeight / PIXEL_TO_METER));
	wallBody->CreateFixture(&wallShape, 0.0f);
	//右
	wallShape.Set(b2Vec2(halfMapWidth / PIXEL_TO_METER, halfMapHeight / PIXEL_TO_METER), b2Vec2(halfMapWidth / PIXEL_TO_METER, -halfMapHeight / PIXEL_TO_METER));
	wallBody->CreateFixture(&wallShape, 0.0f);
	////下
	//wallShape.Set(b2Vec2(0.0f, m_minPosY / PIXEL_TO_METER), b2Vec2(m_gameMap->getMapWidth() / PIXEL_TO_METER, m_minPosY / PIXEL_TO_METER));
	//wallBody->CreateFixture(&wallShape, 0.0f);
	////上
	//wallShape.Set(b2Vec2(0.0f, m_gameMap->getMapHeight() / PIXEL_TO_METER), b2Vec2(m_gameMap->getMapWidth() / PIXEL_TO_METER, m_gameMap->getMapHeight() / PIXEL_TO_METER));
	//wallBody->CreateFixture(&wallShape, 0.0f);
	////左
	//wallShape.Set(b2Vec2(0.0f, m_gameMap->getMapHeight() / PIXEL_TO_METER), b2Vec2(0.0f, 0.0f));
	//wallBody->CreateFixture(&wallShape, 0.0f);
	////右
	//wallShape.Set(b2Vec2(m_gameMap->getMapWidth() / PIXEL_TO_METER, m_gameMap->getMapHeight() / PIXEL_TO_METER), b2Vec2(m_gameMap->getMapWidth() / PIXEL_TO_METER, 0.0f));
	//wallBody->CreateFixture(&wallShape, 0.0f);
}

void GameWord::addActor(GameActor* actor)
{
	getActorNode()->addChild(actor);
	actor->m_word = this;
	m_allActor.pushBack(actor);
}

void GameWord::removeActor(GameActor* actor)
{
	if (actor == NULL)
	{
		return;
	}
	actor->removeFromParent();
	actor->m_word = NULL;
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

	if (actor)
	{
		actor->removeFromParent();
		actor->m_word = NULL;
		m_allActor.eraseObject(actor);
	}	
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


void GameWord::setViewPortMinXValue(float InValue) 
{ 
	m_viewPortMinX = InValue;
	m_viewPortMinX = MAX(m_viewPortMinX, 0.0f);
}

void GameWord::setViewPortMaxXValue(float InValue) 
{
	m_viewPortMaxX = InValue;
	m_viewPortMaxX = MIN(m_viewPortMaxX, m_gameMap->getMapWidth());
}

void GameWord::logicUpdate(float d)
{
	m_world->Step(d, 4, 4);

	// 角色逻辑
	for (auto& it : m_allActor)
	{
		it->logicUpdate(d);
	}
	// 地图约束
	//updateMapCorrectActor();

	// 地图移动
	updateMapMoveLogic();

#ifdef ENABLE_GAME_WORD_DEBUG
	// debug
	if (m_debugDraw->isVisible())
	{
		debugDraw();
	}
#endif

	// 碰撞检测
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
	// 地图跟随玩家移动
	if (m_player)
	{
		const Vec2& v = m_player->getPosition();
		m_gameMap->setViewPos(v.x, 0.0f);
	}
}

void GameWord::updateMapCorrectActor()
{
	//Vec2 v;
	//float tmp;
	//for (auto& it : m_allActor)
	//{
	//	if(!it->isEnableMapConstraint())
	//		continue;

	//	static const float halfWidth = 50.0f;//it->getAABB().size.width * 0.5;
	//	v = it->getPosition();

	//	tmp = m_viewPortMaxX - halfWidth;
	//	v.x = MIN(v.x, tmp);

	//	tmp = m_viewPortMinX + halfWidth;
	//	v.x = MAX(v.x, tmp);

	//	v.x = MAX(v.y, m_minPosY);

	//	it->setPosition(v);
	//}
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
