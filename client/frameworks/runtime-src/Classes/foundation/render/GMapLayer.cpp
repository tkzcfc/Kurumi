#include "GMapLayer.h"

#include "foundation/ParticleSystemHelper.h"
#include "cocostudio/CocoStudio.h"
#include "json/document.h"
#include "json/stringbuffer.h"

GMapLayer::GMapLayer()
	: m_actorNode(NULL)
	, m_drawNode(NULL)
	, m_rootNode(NULL)
	, m_camera(NULL)
{
}

GMapLayer::~GMapLayer()
{
}

GMapLayer * GMapLayer::create(int mapId)
{
	GMapLayer * ret = new (std::nothrow) GMapLayer();
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

bool GMapLayer::init()
{
	if (!Node::init())
		return false;

	m_rootNode = Node::create();
	this->addChild(m_rootNode);

	m_drawNode = DrawNode::create();
	m_rootNode->addChild(m_drawNode, 0xffff);

	return true;
}

bool GMapLayer::initWithMapID(int mapId)
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

	Node* mapRender = cocostudio::SceneReader::getInstance()->createNodeWithSceneFile(mapFile);
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
			SubMapNodeInfo nodeInfo;
			nodeInfo.isActor = false;
			nodeInfo.ignore = false;
			nodeInfo.node = node;
			nodeInfo.size.width = item.FindMember("w")->value.GetDouble();
			nodeInfo.size.height = item.FindMember("h")->value.GetDouble();

			if (item.HasMember("actor") && item.FindMember("actor")->value.GetBool())
			{
				CC_ASSERT(m_actorNode == NULL);
				m_actorNode = Node::create();
				node->addChild(m_actorNode, 0xff);

				m_mapSize = nodeInfo.size;
				nodeInfo.isActor = true;
			}
			m_arrSubMapNodeInfo.emplace_back(nodeInfo);
		}
	}
	if (m_actorNode == NULL)
		return false;

	m_rootNode->setContentSize(m_mapSize);
	m_rootNode->addChild(mapRender);

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

	changeParticleSystemPositionType(mapRender, (int)ParticleSystem::PositionType::GROUPED);

	return true;
}

void GMapLayer::setViewSize(const Size& size)
{
	m_diffMapViewSize = m_mapSize - size;
	if (m_camera)
	{
		m_camera->setViewPortSize(size);
	}
}
