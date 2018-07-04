#include "GameWord.h"
#include "GameMath.h"

static GameWord* Static__GameWord = NULL;

GameWord::GameWord()
{
	m_actorNode = NULL;
	m_player = NULL;
	m_fixNode = NULL;
	m_fixNodeBeginX = 0.0f;
	Static__GameWord = this;
}

GameWord::~GameWord()
{
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

		m_rootNode = NULL;
		m_minPosY = 0.0f;

#ifdef ENABLE_GAME_WORD_DEBUG
		m_debugDraw = DrawNode::create();
		this->addChild(m_debugDraw, 1);
#endif

		this->schedule(schedule_selector(GameWord::logicUpdate), 1 / 60.0f);

		const auto& size = Director::getInstance()->getVisibleSize();

		m_mapSize = size;

		return true;
	} while (0);
	return false;
}

void GameWord::loadMapFile(const std::string& filepath, const std::string& actorNodeName, const std::string& fixNodeName)
{
#ifdef ENABLE_GAME_WORD_DEBUG
	if (m_debugDraw)
	{
		m_debugDraw->retain();
		m_debugDraw->removeFromParent();
	}
#endif
	
	if (m_rootNode)
	{
		m_rootNode->removeFromParent();
		m_rootNode = nullptr;
	}

	m_rootNode = SceneReader::getInstance()->createNodeWithSceneFile(filepath);
	addChild(m_rootNode);

#ifdef ENABLE_GAME_WORD_DEBUG
	m_rootNode->addChild(m_debugDraw, 0xFFFF);
	m_debugDraw->release();
#endif

	if (m_actorNode && m_actorNode->getParent())
	{
		m_actorNode->removeFromParent();
		m_actorNode = NULL;
	}

	Node* targetNode = NULL;
	m_fixNode = NULL;

	auto& child = m_rootNode->getChildren();
	for (auto& it : child)
	{
		CCLOG("[T%d][Z%d][Z%d] : [%s] X[%f]Y[%f]", it->getTag(), it->getLocalZOrder(), (int)it->getGlobalZOrder(), it->getName().c_str(), it->getPositionX(), it->getPositionY());
		if(strstr(it->getName().c_str(), actorNodeName.c_str()))
		{
			targetNode = it;
		}
		if (!fixNodeName.empty() && strstr(it->getName().c_str(), fixNodeName.c_str()))
		{
			m_fixNodeBeginX = it->getPositionX();
			m_fixNode = it;
		}
	}

	m_actorNode = Node::create();
	m_rootNode->addChild(m_actorNode, targetNode->getLocalZOrder());

	CCASSERT(m_actorNode != NULL, "m_actorNode ²»ÄÜÎª¿Õ");

	m_mapSize = m_rootNode->getContentSize();

	changeParticleSystemPositionType(m_rootNode);
}

void GameWord::addActor(GameActor* actor)
{
	m_actorNode->addChild(actor, 100);
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
	GameActor* actor = dynamic_cast<GameActor*>(m_actorNode->getChildByName(name));

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

void GameWord::logicUpdate(float d)
{
	// ½ÇÉ«Âß¼­
	for (auto& it : m_allActor)
	{
		it->logicUpdate(d);
	}
	// µØÍ¼ÒÆ¶¯
	updateMapMoveLogic();
	// µØÍ¼Ô¼Êø
	updateMapCorrectActor();

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
		const Vec2& curpos = m_player->getMapMovePos();

		Size winSize = Director::getInstance()->getVisibleSize();

		// XÖá¸úËæÍæ¼ÒÒÆ¶¯
		if (m_mapSize.width > winSize.width)
		{
			float halfWidth = winSize.width * 0.5f;
			if (curpos.x <= halfWidth)
			{
				m_rootNode->setPositionX(0.0f);
			}
			else if (curpos.x >= m_mapSize.width - halfWidth)
			{
				m_rootNode->setPositionX(winSize.width - m_mapSize.width);
			}
			else
			{
				m_rootNode->setPositionX(halfWidth - curpos.x);
			}
			if (m_fixNode)
			{
				m_fixNode->setPositionX(m_fixNodeBeginX - m_rootNode->getPositionX());
			}
		}
		//// YÖá¸úËæÍæ¼ÒÒÆ¶¯
		//float subHeight = winSize.height - m_mapSize.height;
		//if (subHeight < 0.0f)
		//{
		//	float actorposY = m_player->getActorPositionY();
		//	float subposY = actorposY - curpos.y;
		//	if (subposY < 0.0f)
		//	{
		//		subposY = MAX(subposY, subHeight * 0.5f);
		//		m_rootNode->setPositionY(subposY);
		//	}
		//	else
		//	{
		//		m_rootNode->setPositionY(0.0f);
		//	}
		//}
	}
}

void GameWord::updateMapCorrectActor()
{
	Vec2 v;
	float tmp;
	for (auto& it : m_allActor)
	{
		float halfWidth = 50.0f;//it->getAABB().size.width * 0.5;
		v = it->getActorPosition();

		tmp = m_mapSize.width - halfWidth;
		v.x = MIN(v.x, tmp);

		tmp = halfWidth;
		v.x = MAX(v.x, tmp);

		v.y = MAX(v.y, m_minPosY);

		it->setActorPosition(v);
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
