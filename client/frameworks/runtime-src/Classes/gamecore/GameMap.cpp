#include "GameMap.h"



GameMap::GameMap()
{
	m_lockMapY = false;
	for (int i = 0; i < (int)GameMapNodeType::COUNT; i++)
	{
		m_mapWidgetInfoArr[i].reserve(100);
	}
	m_save_view_x = m_save_view_y = -1.0f;
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

	for (int i = 0; i < (int)GameMapNodeType::COUNT; ++i)
	{
		m_mapNode[i] = Node::create();
		this->addChild(m_mapNode[i]);
	}
	m_viewSize = Director::getInstance()->getVisibleSize();

	initMap();

	return true;
}

Node* GameMap::getMapNode(GameMapNodeType type)
{
	return m_mapNode[type];
}

void GameMap::setMapNodeSize(GameMapNodeType type, float width, float height)
{
	m_mapNodeSize[type].width = width;
	m_mapNodeSize[type].height = height;
	m_mapNodeMoveSize[type].width = MAX(width - m_viewSize.width, 0.0f);
	m_mapNodeMoveSize[type].height = MAX(height - m_viewSize.height, 0.0f);

	m_mapSize.width = MAX(m_mapSize.width, width);
	m_mapSize.height = MAX(m_mapSize.height, height);
}

void GameMap::addMapWidgetData(GameMapNodeType type, int widgetKey, float begin_x, float end_x)
{
	MapWidgetInfo info;
	info.isload = false;
	info.node = NULL;
	info.widgetKey = widgetKey;
	info.begin_x = begin_x;
	info.end_x = end_x;
	m_mapWidgetInfoArr[type].emplace_back(info);
}

void GameMap::initMap()
{
	LuaFunction* pHandle = getLuaHandle("initMap");
	if (pHandle)
	{
		pHandle->ppush();
		pHandle->pcall();
	}
}

void GameMap::setViewPos(float x, float y)
{
	x = MAX(x, 0.0f);
	x = MIN(x, m_mapSize.width);
	y = MAX(y, 0.0f);
	y = MIN(y, m_mapSize.height);
	if (fabs(m_save_view_x - x) < 0.0001f && fabs(m_save_view_y - y) < 0.0001f)
	{
		return;
	}

	float percent_x = x / m_mapSize.width;
	float percent_y = y / m_mapSize.height;

	for (int i = 0; i < (int)GameMapNodeType::COUNT; ++i)
	{
		float curx = percent_x * m_mapNodeMoveSize[i].width;
		if (m_lockMapY)
		{
			m_mapNode[i]->setPositionX(-curx);
		}
		else
		{
			float cury = percent_y * m_mapNodeMoveSize[i].height;
			m_mapNode[i]->setPosition(-curx, -cury);
		}
	}
	m_save_view_y = y;
	if (fabs(m_save_view_x - x) < 0.0001f)
	{
		m_save_view_x = x;
		return;
	}
	m_save_view_x = x;

	LuaFunction* pHandle = getLuaHandle("LoadMapWidgetCallFunc");

	if (pHandle == NULL)
		return;

	for (int i = 0; i < (int)GameMapNodeType::COUNT; ++i)
	{
		float cur_x = percent_x * m_mapNodeSize[i].width;
		float beginx = cur_x - m_viewSize.width * 1.0f;
		float endx = cur_x + m_viewSize.width * 1.0f;

		for (auto & it : m_mapWidgetInfoArr[i])
		{
			if (it.end_x < beginx || endx < it.begin_x)
			{
				if (it.isload)
				{
					//CCLOG("\n[%d]remove widget key: %d", i, it.widgetKey);
					if (it.node)
					{
						it.node->removeFromParent();
						it.node = NULL;
					}
					it.isload = false;
				}
			}
			else
			{
				if (!it.isload)
				{
					//CCLOG("\n[%d]load widget key: %d", i, it.widgetKey);
					pHandle->ppush();
					pHandle->pusharg(i);
					pHandle->pusharg(it.widgetKey);
					pHandle->pushusertype(m_mapNode[i], "cc.Node");
					pHandle->pcall(1);
					it.node = static_cast<Node*>(pHandle->retuserdata());
					it.isload = true;
					if (it.node)
					{
						m_mapNode[i]->addChild(it.node);
					}
				}
			}
		}
	}
}

void GameMap::setViewSize(float width, float height)
{
	m_viewSize.width = width;
	m_viewSize.height = height;

	for (int i = 0; i < (int)GameMapNodeType::COUNT; ++i)
	{
		m_mapNodeMoveSize[i].width = m_mapNodeSize[i].width - width;
		m_mapNodeMoveSize[i].height = m_mapNodeSize[i].height - height;
		m_mapNodeMoveSize[i].width = MAX(m_mapNodeMoveSize[i].width, 0.0f);
		m_mapNodeMoveSize[i].height = MAX(m_mapNodeMoveSize[i].height, 0.0f);
	}
}



