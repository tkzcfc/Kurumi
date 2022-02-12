#include "GMapLayer_Parallax.h"

#include "foundation/GTools.h"
#include "cocostudio/CocoStudio.h"
#include "json/document.h"
#include "json/stringbuffer.h"

NS_G_BEGIN

GMapLayer_Parallax::GMapLayer_Parallax()
	: m_actorNode(NULL)
	, m_drawNode(NULL)
	, m_camera(NULL)
	, m_parallaxNode(NULL)
{
}

GMapLayer_Parallax::~GMapLayer_Parallax()
{
}

GMapLayer_Parallax * GMapLayer_Parallax::create(int mapId)
{
	GMapLayer_Parallax * ret = new (std::nothrow) GMapLayer_Parallax();
	if (ret && ret->init() && ret->initWithMapID(mapId))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool GMapLayer_Parallax::init()
{
	if (!Node::init())
		return false;

	return true;
}

bool GMapLayer_Parallax::initWithMapID(int mapId)
{
	auto cfgFile = StringUtils::format("json/map/mi_%d.json", mapId);
	auto mapFile = StringUtils::format("map/map%d/m.json", mapId);

	if (!FileUtils::getInstance()->isFileExist(mapFile))
		return false;

	auto content = FileUtils::getInstance()->getStringFromFile(cfgFile);
	if (content.empty())
		return false;

	rapidjson::Document json;
	rapidjson::StringStream stream(content.c_str());

	json.ParseStream<0>(stream);
	if (json.HasParseError())
	{
		CCLOG("GetParseError %d\n", json.GetParseError());
		return false;
	}

	if (json.HasMember("infos") == false)
		return false;

	auto it = json.FindMember("infos");
	auto& arr = it->value;
	if (arr.IsArray() == false)
		return false;

	auto mapRender = cocostudio::SceneReader::getInstance()->createNodeWithSceneFile(mapFile);

	if (mapRender == NULL || mapRender->getChildrenCount() <= 0)
		return false;

	m_actorNode = NULL;
	// 基准大小
	Size benchmarkSize;

	for (auto i = 0; i < arr.Size(); ++i)
	{
		auto& item = arr[i];
		std::string name = item.FindMember("name")->value.GetString();

		auto node = mapRender->getChildByName(name);
		if (node && !item.FindMember("ignore")->value.GetBool())
		{
			if (item.HasMember("actor") && item.FindMember("actor")->value.GetBool())
			{
				benchmarkSize.width = deal_float(item.FindMember("w")->value.GetFloat());
				benchmarkSize.height = deal_float(item.FindMember("h")->value.GetFloat());

				m_mapSize = benchmarkSize;

				CC_ASSERT(m_actorNode == NULL);
				m_actorNode = node;

				m_minPosY = deal_float(item.FindMember("miny")->value.GetFloat());
				m_maxPosY = deal_float(item.FindMember("maxy")->value.GetFloat());

				CCLOG("actor node: %s", name.c_str());
			}
		}
	}

	if (m_actorNode == NULL)
		return false;

#if 0
	CCLOG("---------------------------- begin");
	for (auto& it : mapRender->getChildren())
	{
		CCLOG("debug node: %s  %d", it->getName().c_str(), getNodeOrder(mapRender, it));
	}
	CCLOG("---------------------------- end");
#endif


	// 视图大小
	auto viewSize = Director::getInstance()->getVisibleSize();
	// 默认视差比
	Vec2 defaultRatio(1.0f, 1.0f);

	// 基准节点与视图大小差值
	auto bcDiffW = benchmarkSize.width - viewSize.width;
	auto bcDiffH = benchmarkSize.height - viewSize.height;

	// 创建视差节点
	m_parallaxNode = ParallaxNode::create();
	this->addChild(m_parallaxNode);

	for (auto i = 0; i < arr.Size(); ++i)
	{
		auto& item = arr[i];
		std::string name = item.FindMember("name")->value.GetString();

		auto node = mapRender->getChildByName(name);
		if (node && !item.FindMember("ignore")->value.GetBool())
		{
			auto order = getNodeOrder(mapRender, node);
			auto& curPos = node->getPosition();
			auto isActor = m_actorNode == node;

			Node* render = node;
			node->removeFromParent();

			if (isActor || ::abs(curPos.x) > 1.0 || ::fabs(curPos.y) > 1.0)
			{
				render = Node::create();
				render->addChild(node);
				render->setAnchorPoint(Vec2::ZERO);

				if (isActor)
				{
					m_actorNode = Node::create();
					render->addChild(m_actorNode, node->getLocalZOrder() + 1);
				}
			}

			// 计算节点与视图大小插值
			auto diffW = deal_float(item.FindMember("w")->value.GetFloat()) - viewSize.width;
			auto diffH = deal_float(item.FindMember("h")->value.GetFloat()) - viewSize.height;

			// 计算视差比
			auto parallaxRatio = defaultRatio;

			if (bcDiffW > 0.0)
				parallaxRatio.x = diffW / bcDiffW * defaultRatio.x;

			if (bcDiffH > 0.0)
				parallaxRatio.y = diffH / bcDiffH * defaultRatio.y;

			// 视差节点坐标
			auto pnPos = m_parallaxNode->getPosition();
			// 位置偏移
			auto positionOffset = defaultRatio - parallaxRatio;
			positionOffset.x = positionOffset.x * pnPos.x;
			positionOffset.y = positionOffset.y * pnPos.y;

			m_parallaxNode->addChild(render, order, parallaxRatio, positionOffset);

			GTools::changeParticleSystemPositionType(node, (int)ParticleSystem::PositionType::GROUPED);

			if (isActor)
			{
				m_drawNode = DrawNode::create();
				m_drawNode->setAnchorPoint(Vec2::ZERO);
				m_parallaxNode->addChild(m_drawNode, 0xffff, parallaxRatio, positionOffset);
			}
		}
	}


	// camera
	m_camera = GVirtualCamera::create();
	m_camera->setCall([=](float px, float py, float scale)
	{
		m_parallaxNode->setPosition(-px, -py);
		m_parallaxNode->setScale(scale);
	});
	m_camera->setWorldSize(m_mapSize);
	m_camera->setEnableCollision(true);
	m_camera->setViewPortSize(viewSize);
	this->addComponent(m_camera);

	return true;
}

int GMapLayer_Parallax::getNodeOrder(Node* root, Node* node)
{
	G_ASSERT(node->getLocalZOrder() < 10);

	int order = -1;

	auto& children = root->getChildren();
	for (auto i = 0; i < children.size(); ++i)
	{
		if (node == children.at(i))
		{
			order = i;
		}
	}
	G_ASSERT(order != -1);

	return node->getLocalZOrder() * 10 + order;
}

NS_G_END