#include "GameMap.h"
#include "GameWord.h"


GameMap::GameMap()
	: m_minPosY(0.0f)
	, m_actorNode(NULL)
	, m_lockMapY(false)
	, m_fixNodeBeginX(0.0f)
	, m_save_view_x(-1.0f)
	, m_save_view_y(-1.0f)
{
	for (int i = 0; i < (int)GameMapNodeType::COUNT; ++i)
	{
		m_mapNode[i] = NULL;
	}
}

GameMap::~GameMap()
{
}

GameMap * GameMap::create()
{
	GameMap * ret = new (std::nothrow) GameMap();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool GameMap::init()
{
	if (!Node::init())
		return false;

	m_viewSize = Director::getInstance()->getVisibleSize();
	m_halfViewSize = m_viewSize * 0.5f;

	return true;
}

void GameMap::loadMapFile(const std::string& filepath, const std::string& actorNodeName, const std::string& fixNodeName, float minPosY)
{
	if (m_actorNode)
		return;

	m_minPosY = minPosY;

	Node* rootNode = SceneReader::getInstance()->createNodeWithSceneFile(filepath);
	addChild(rootNode);

	if (m_actorNode && m_actorNode->getParent())
	{
		m_actorNode->removeFromParent();
		m_actorNode = NULL;
	}

	Node* targetNode = NULL;

	auto& child = rootNode->getChildren();
	for (auto& it : child)
	{
		//CCLOG("[T%d][Z%d][Z%d] : [%s] X[%f]Y[%f]", it->getTag(), it->getLocalZOrder(), (int)it->getGlobalZOrder(), it->getName().c_str(), it->getPositionX(), it->getPositionY());
		if (!actorNodeName.empty() && strstr(it->getName().c_str(), actorNodeName.c_str()))
		{
			targetNode = it;
		}
		if (!fixNodeName.empty() && strstr(it->getName().c_str(), fixNodeName.c_str()))
		{
			m_fixNodeBeginX = it->getPositionX();
			m_mapNode[GameMapNodeType::FIX_NODE] = it;
			m_mapNodeSize[GameMapNodeType::FIX_NODE] = it->getContentSize();
		}
	}
	CCASSERT(targetNode != NULL, "targetNode ²»ÄÜÎª¿Õ");

	m_actorNode = Node::create();
	rootNode->addChild(m_actorNode, targetNode->getLocalZOrder());	

	m_mapSize = rootNode->getContentSize();
	m_mapNodeSize[GameMapNodeType::STAGE_NODE] = m_mapSize;

	changeParticleSystemPositionType(rootNode);

	m_mapNode[GameMapNodeType::STAGE_NODE] = rootNode;

	for (int i = 0; i < (int)GameMapNodeType::COUNT; ++i)
	{
		m_mapNodeMoveSize[i].width = MAX(m_mapNodeSize[i].width - m_viewSize.width, 0.0f);
		m_mapNodeMoveSize[i].height = MAX(m_mapNodeSize[i].height - m_viewSize.height, 0.0f);
	}
}

void GameMap::setViewPos(float x, float y)
{
	y = y - m_minPosY;
	x = MAX(x, 0.0f);
	x = MIN(x, m_mapSize.width);
	y = MAX(y, 0.0f);
	y = MIN(y, m_mapSize.height);
	if (fabs(m_save_view_x - x) < 0.0001f && fabs(m_save_view_y - y) < 0.0001f)
	{
		return;
	}

	float percent_x = 0.0f;
	float percent_y = y / m_mapSize.height;

	bool fix_player_to_center_x = false;
	if (x <= m_halfViewSize.width)
	{
		percent_x = 0.0f;
	}
	else if(x >= m_mapSize.width - m_halfViewSize.width)
	{
		percent_x = 1.0f;
	}
	else
	{
		fix_player_to_center_x = true;
		percent_x = x / m_mapSize.width;;
	}

	float curx, cury;
	for (int i = 0; i < (int)GameMapNodeType::COUNT; ++i)
	{
		if(m_mapNode[i] == NULL)
			continue;
		curx = 0.0f;
		if (i == GameMapNodeType::FIX_NODE)
		{
			curx = percent_x * m_mapNodeMoveSize[i].width;
			curx = curx + m_mapNode[GameMapNodeType::STAGE_NODE]->getPositionX();
			curx = curx - m_fixNodeBeginX;
		}
		else
		{
			if (fix_player_to_center_x)
			{
				curx = x - m_halfViewSize.width;
			}
			else
			{
				curx = percent_x * m_mapNodeMoveSize[i].width;
			}
		}
		if (m_lockMapY)
		{
			m_mapNode[i]->setPositionX(-curx);
		}
		else
		{
			cury = percent_y * m_mapNodeMoveSize[i].height;
			m_mapNode[i]->setPosition(-curx, -cury);
		}
	}
	m_save_view_y = y;
	m_save_view_x = x;
}

void GameMap::setViewSize(float width, float height)
{
	m_viewSize.width = width;
	m_viewSize.height = height;
	m_halfViewSize = m_viewSize * 0.5f;

	for (int i = 0; i < (int)GameMapNodeType::COUNT; ++i)
	{
		m_mapNodeMoveSize[i].width = MAX(m_mapNodeMoveSize[i].width - m_viewSize.width, 0.0f);
		m_mapNodeMoveSize[i].height = MAX(m_mapNodeMoveSize[i].height - m_viewSize.height, 0.0f);
	}
}



