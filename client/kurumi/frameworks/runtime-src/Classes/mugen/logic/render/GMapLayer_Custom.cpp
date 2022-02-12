#include "GMapLayer_Custom.h"

#include "foundation/GTools.h"
#include "cocostudio/CocoStudio.h"
#include "json/document.h"
#include "json/stringbuffer.h"

NS_G_BEGIN

GMapLayer_Custom::GMapLayer_Custom()
	: m_actorNode(NULL)
	, m_drawNode(NULL)
	, m_rootNode(NULL)
	, m_camera(NULL)
{
}

GMapLayer_Custom::~GMapLayer_Custom()
{
}

GMapLayer_Custom * GMapLayer_Custom::create(int mapId)
{
	GMapLayer_Custom * ret = new (std::nothrow) GMapLayer_Custom();
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

bool GMapLayer_Custom::init()
{
	if (!Node::init())
		return false;

	m_rootNode = Node::create();
	this->addChild(m_rootNode);

	m_drawNode = DrawNode::create();
	m_rootNode->addChild(m_drawNode, 0xffff);

	return true;
}

bool GMapLayer_Custom::initWithMapID(int mapId)
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
	if (mapRender == NULL)
		return false;

	auto& child = mapRender->getChildren();
	if (child.empty())
		return false;

	m_actorNode = NULL;
	for (auto i = 0; i < arr.Size(); ++i)
	{
		auto& item = arr[i];
		std::string name = item.FindMember("name")->value.GetString();

		auto node = mapRender->getChildByName(name);

		if (node && !item.FindMember("ignore")->value.GetBool())
		{
			auto order = getNodeOrder(mapRender, node);
			node->removeFromParent();

			auto render = Node::create();
			render->addChild(node);
			render->setAnchorPoint(Vec2::ZERO);
			m_rootNode->addChild(render, order);

			SubMapNodeInfo nodeInfo;
			nodeInfo.isActor = false;
			nodeInfo.ignore = false;
			nodeInfo.node = render;
			nodeInfo.size.width = deal_float(item.FindMember("w")->value.GetFloat());
			nodeInfo.size.height = deal_float(item.FindMember("h")->value.GetFloat());

			if (item.HasMember("actor") && item.FindMember("actor")->value.GetBool())
			{
				CC_ASSERT(m_actorNode == NULL);
				m_actorNode = Node::create();
				render->addChild(m_actorNode, node->getLocalZOrder() + 1);

				m_mapSize = nodeInfo.size;
				nodeInfo.isActor = true;

				m_minPosY = deal_float(item.FindMember("miny")->value.GetFloat());
				m_maxPosY = deal_float(item.FindMember("maxy")->value.GetFloat());
			}
			m_arrSubMapNodeInfo.emplace_back(nodeInfo);
		}
	}
	if (m_actorNode == NULL)
		return false;

	m_rootNode->setContentSize(m_mapSize);

	for (auto& info : m_arrSubMapNodeInfo)
	{
		info.originPos = info.node->getPosition();
		info.diffSize = info.size - m_mapSize;
		info.ignore = std::fabsf(info.diffSize.width) < 1.0f && std::fabsf(info.diffSize.height) < 1.0f;
	}

	// camera
	m_camera = GVirtualCamera::create();
	m_camera->setCall([=](float px, float py, float scale)
	{
		m_rootNode->setPosition(-px, -py);
		m_rootNode->setScale(scale);

		float scalex = 0.0f, scaley = 0.0f;

		if (m_diffMapViewSize.width > 0.0f)
		{
			scalex = px / m_diffMapViewSize.width;
			if (scale > 1.0f)
			{
				scalex = scalex / scale;
			}
			scalex = MAX(scalex, 0.0f);
			scalex = MIN(scalex, 1.0f);
		}
		if (m_diffMapViewSize.height > 0.0f)
		{
			scaley = py / m_diffMapViewSize.height;
			if (scale > 1.0f)
			{
				scaley = scaley / scale;
			}
			scaley = MAX(scaley, 0.0f);
			scaley = MIN(scaley, 1.0f);
		}

		scalex = -scalex;
		scaley = -scaley;

		for (auto& info : m_arrSubMapNodeInfo)
		{
			if (info.ignore == false)
			{
				float tmpx = info.diffSize.width * scalex + info.originPos.x;
				float tmpy = info.diffSize.height * scaley + info.originPos.y;
				info.node->setPosition(tmpx, tmpy);
			}
		}
	});
	m_camera->setWorldSize(m_mapSize);
	m_camera->setEnableCollision(true);
	this->addComponent(m_camera);

	this->setViewSize(Director::getInstance()->getVisibleSize());

	GTools::changeParticleSystemPositionType(mapRender, (int)ParticleSystem::PositionType::GROUPED);

	return true;
}

void GMapLayer_Custom::setViewSize(const Size& size)
{
	m_diffMapViewSize = m_mapSize - size;
	if (m_camera)
	{
		m_camera->setViewPortSize(size);
	}
}

int GMapLayer_Custom::getNodeOrder(Node* root, Node* node)
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