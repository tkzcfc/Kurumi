#include "GMapLayer.h"
#include "foundation/ParticleSystemHelper.h"
#include "cocostudio/CocoStudio.h"

GMapLayer::GMapLayer()
	: m_minPosY(0.0f)
	, m_actorNode(NULL)
	, m_lockMapY(false)
	, m_fixNodeBeginX(0.0f)
	, m_save_view_x(-1.0f)
	, m_save_view_y(-1.0f)
	, m_enableViewPosLimit(false)
	, m_openAreaMinX(0)
	, m_openAreaMaxX(0)
{
	for (int i = 0; i < (int)GameMapNodeType::COUNT; ++i)
	{
		m_mapNode[i] = NULL;
	}
}

GMapLayer::~GMapLayer()
{
}

GMapLayer * GMapLayer::create()
{
	GMapLayer * ret = new (std::nothrow) GMapLayer();
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

bool GMapLayer::init()
{
	if (!Node::init())
		return false;

	m_viewSize = Director::getInstance()->getVisibleSize();
	m_halfViewSize = m_viewSize * 0.5f;

#if COCOS2D_DEBUG == 1
	m_drawNode = DrawNode::create();
	this->addChild(m_drawNode, 0xffff);
#endif
	return true;
}

void GMapLayer::loadMapFile(const std::string& filepath, const std::string& actorNodeName, const std::string& fixNodeName, float minPosY)
{
	if (m_actorNode)
		return;

	m_minPosY = minPosY;

	Node* rootNode = cocostudio::SceneReader::getInstance()->createNodeWithSceneFile(filepath);
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
	CC_ASSERT(targetNode != NULL);

	m_actorNode = Node::create();
	rootNode->addChild(m_actorNode, targetNode->getLocalZOrder());

	m_mapSize = rootNode->getContentSize();
	m_openAreaMaxX = m_mapSize.width;
	m_mapNodeSize[GameMapNodeType::STAGE_NODE] = m_mapSize;

	changeParticleSystemPositionType(rootNode, (int)ParticleSystem::PositionType::GROUPED);

	m_mapNode[GameMapNodeType::STAGE_NODE] = rootNode;

	for (int i = 0; i < (int)GameMapNodeType::COUNT; ++i)
	{
		m_mapNodeMoveSize[i].width = MAX(m_mapNodeSize[i].width, 0.0f);
		m_mapNodeMoveSize[i].height = MAX(m_mapNodeSize[i].height - m_viewSize.height, 0.0f);
	}

	//#if COCOS2D_DEBUG == 1
	//	DrawNode* draw = DrawNode::create();
	//	for (auto i = -10; i <= 50; ++i)
	//	{
	//		std::string show = StringUtils::format("(%d)", i * 100);
	//		Label* label = Label::create(show, "", 20);
	//		label->setColor(Color3B::RED);
	//		label->setPosition(i * 100, 200);
	//		rootNode->addChild(label, 0xffff);
	//
	//		draw->drawLine(Vec2(i * 100, 0), Vec2(i * 100, m_viewSize.height), Color4F::BLUE);
	//	}
	//	rootNode->addChild(draw, 0xffff);
	//#endif
}

void GMapLayer::setViewPos(float x, float y)
{
	CC_ASSERT(m_mapSize.width > 0.0f && m_mapSize.height > 0.0f);

	y = y - m_minPosY;

	if (m_enableViewPosLimit)
	{
		x = MAX(x, 0.0f);
		x = MIN(x, m_mapSize.width);
		y = MAX(y, 0.0f);
		y = MIN(y, m_mapSize.height);
	}

	if (fabs(m_save_view_x - x) < 0.0001f && fabs(m_save_view_y - y) < 0.0001f)
	{
		return;
	}

	float percent_x = 0.0f;
	float percent_y = y / m_viewSize.height;

	if (x <= m_halfViewSize.width + m_openAreaMinX)
	{
		percent_x = m_openAreaMinX / m_mapSize.width;
	}
	else if (x >= m_openAreaMaxX - m_halfViewSize.width)
	{
		percent_x = (m_openAreaMaxX - m_viewSize.width) / m_mapSize.width;
	}
	else
	{
		percent_x = (x - m_halfViewSize.width) / m_mapSize.width;
	}

	float curx, cury;
	for (int i = 0; i < (int)GameMapNodeType::COUNT; ++i)
	{
		if (m_mapNode[i] == NULL)
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
			curx = percent_x * m_mapNodeMoveSize[i].width;
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

#if COCOS2D_DEBUG == 1
	if (m_lockMapY)
	{
		m_drawNode->setPositionX(m_mapNode[GameMapNodeType::STAGE_NODE]->getPositionX());
	}
	else
	{
		m_drawNode->setPosition(m_mapNode[GameMapNodeType::STAGE_NODE]->getPosition());
	}
#endif

	m_save_view_y = y;
	m_save_view_x = x;
}

void GMapLayer::setViewSize(float width, float height)
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

float GMapLayer::getValidWorldX(float inValue, float actorRadius)
{
	float minX = MAX(m_openAreaMinX, 0);
	float maxX = MIN(m_openAreaMaxX, m_mapSize.width);

	inValue = MAX(minX + actorRadius, inValue);
	inValue = MIN(maxX - actorRadius, inValue);

	return inValue;
}

float GMapLayer::getValidWorldY(float inValue, float actorRadius)
{
	inValue = MAX(actorRadius, inValue);
	inValue = MIN(m_mapSize.height - actorRadius, inValue);
	return inValue;
}

void GMapLayer::setOpenAreaMinx(float value)
{
	m_openAreaMinX = value;
	m_save_view_x = -1000.0f;
	m_save_view_y = -1000.0f;
}

void GMapLayer::setOpenAreaMaxX(float value)
{
	m_openAreaMaxX = value;
	m_save_view_x = -1000.0f;
	m_save_view_y = -1000.0f;
}

void GMapLayer::setEnableViewPosLimit(bool enable)
{
	m_enableViewPosLimit = enable;
	m_save_view_x = -1000.0f;
	m_save_view_y = -1000.0f;
}
