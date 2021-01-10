//#include "GGameLayer.h"
//
//GGameLayer::GGameLayer()
//	: m_camera(NULL)
//	, m_rootNode(NULL)
//{
//	for (int i = 0; i < (int)EMapLayerType::COUNT; i++)
//	{
//		m_mapLayerInfoArr[i].node = NULL;
//	}
//}
//
//GGameLayer::~GGameLayer()
//{
//	this->clear();
//}
//
//GGameLayer * GGameLayer::create()
//{
//	GGameLayer * ret = new (std::nothrow) GGameLayer();
//	if (ret && ret->init())
//	{
//		ret->autorelease();
//	}
//	else
//	{
//		CC_SAFE_DELETE(ret);
//	}
//	return ret;
//}
//
//void GGameLayer::initMap()
//{
//	CC_ASSERT(m_rootNode == NULL);
//
//	initMapLua();
//
//	for (int i = 0; i < (int)EMapLayerType::COUNT; i++)
//	{
//		m_mapSize.width = MAX(m_mapLayerInfoArr[i].size.width, m_mapSize.width);
//		m_mapSize.height = MAX(m_mapLayerInfoArr[i].size.height, m_mapSize.height);
//	}
//
//	CC_ASSERT(m_mapSize.width != 0.0f && m_mapSize.height != 0.0f);
//
//	m_rootNode = Node::create();
//	m_rootNode->setContentSize(m_mapSize);
//	this->addChild(m_rootNode);
//
//	for (int i = 0; i < (int)EMapLayerType::COUNT; i++)
//	{
//		if (m_mapLayerInfoArr[i].node)
//		{
//			m_mapLayerInfoArr[i].sub_node_x = m_mapLayerInfoArr[i].size.width - m_mapSize.width;
//			m_mapLayerInfoArr[i].sub_node_y = m_mapLayerInfoArr[i].size.height - m_mapSize.height;
//			m_rootNode->addChild(m_mapLayerInfoArr[i].node);
//		}
//	}
//
//	m_camera = GVirtualCamera::create();
//	m_camera->setCall([=](float px, float py, float scale)
//	{
//		//CCLOG("%f", -px);
//		m_rootNode->setPosition(-px, -py);
//		m_rootNode->setScale(scale);
//
//		float scalex = 0.0f, scaley = 0.0f;
//
//		if (m_subMapX > 0.0f)
//		{
//			scalex = px / m_subMapX;
//			if (scale > 1.0f)
//			{
//				scalex = scalex / scale;
//			}
//			scalex = MAX(scalex, 0.0f);
//			scalex = MIN(scalex, 1.0f);
//		}
//		if (m_subMapY > 0.0f)
//		{
//			scaley = py / m_subMapY;
//			if (scale > 1.0f)
//			{
//				scaley = scaley / scale;
//			}
//			scaley = MAX(scaley, 0.0f);
//			scaley = MIN(scaley, 1.0f);
//		}
//
//		for (int i = 0; i < (int)EMapLayerType::COUNT; i++)
//		{
//			if (m_mapLayerInfoArr[i].node)
//			{
//				float tmpx = scalex * m_mapLayerInfoArr[i].sub_node_x;
//				float tmpy = scaley * m_mapLayerInfoArr[i].sub_node_y;
//				m_mapLayerInfoArr[i].node->setPosition(-tmpx, -tmpy);
//			}
//		}
//	});
//	m_camera->setWorldSize(m_mapSize);
//	m_camera->setEnableCollision(false);
//	this->addComponent(m_camera);
//
//	this->setViewSize(Director::getInstance()->getVisibleSize());
//}
//
//Node* GGameLayer::getMapNode(EMapLayerType type)
//{
//	return m_mapLayerInfoArr[type].node;
//}
//
//void GGameLayer::setMapNode(EMapLayerType type, Node* node)
//{
//	if (node == NULL)
//	{
//		return;
//	}
//	CC_SAFE_RETAIN(node);
//	m_mapLayerInfoArr[type].node = node;
//	m_mapLayerInfoArr[type].size = node->getContentSize();
//}
//
//void GGameLayer::clear()
//{
//	for (auto& it : m_mapLayerInfoArr)
//	{
//		CC_SAFE_RELEASE_NULL(it.node);
//	}
//}
//
//void GGameLayer::setViewSize(const Size& size)
//{
//	m_subMapX = m_mapSize.width - size.width;
//	m_subMapY = m_mapSize.height - size.height;
//
//	m_visionSize = size * 0.5;
//	if (m_camera)
//	{
//		m_camera->setViewPortSize(size);
//	}
//}
//
//void GGameLayer::setVisionSize(const Size& visionSize)
//{
//	m_visionSize = visionSize;
//}
//
//void GGameLayer::onExit()
//{
//	this->clear();
//	Node::onExit();
//}
//
//void GGameLayer::initMapLua()
//{
//	//LuaFunction* pHandle = getLuaHandle("initMap");
//	//if (pHandle && pHandle->isvalid())
//	//{
//	//	pHandle->ppush();
//	//	pHandle->pcall();
//	//}
//}
//
//
