#include "GAvatarComponent.h"
#include "GRigidBodyComponent.h"
#include "GStaticDataComponent.h"
#include "GActorComponent.h"
#include "mugen/base/GEntity.h"

#if RUNTIME_IN_COOCS
#include "mugen/logic/GGameWorld.h"
#endif

NS_G_BEGIN

// 获取动画名称
static std::string getArmatureName(std::string armatureFile)
{
	auto pos = armatureFile.find_last_of('/');
	if (pos == std::string::npos)
	{
		return "";
	}

	auto str = armatureFile.substr(pos + 1);
	str = str.substr(0, str.find_first_of('.'));
	return str;
}

GAvatarComponent::GAvatarComponent()
{
#if RUNTIME_IN_COOCS
	m_actorRender = NULL;
	m_rootNode = NULL;
#endif
}

GAvatarComponent::~GAvatarComponent()
{
}

void GAvatarComponent::onAdd()
{
#if RUNTIME_IN_COOCS
	m_rootNode = cocos2d::Node::create();
	m_rootNode->setScheduler(GGameWorld::getInstance()->getScheduler());
	GGameWorld::getInstance()->getMapLayer()->getActorNode()->addChild(m_rootNode);

	// 获取静态数据组件
	auto pStaticDataCom = G_GetComponent(this, GStaticDataComponent);
	cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo(pStaticDataCom->armatureFile);

	// 创建动画对象
	m_actorRender = cocostudio::Armature::create();
	m_actorRender->setScheduler(GGameWorld::getInstance()->getScheduler());
	m_actorRender->init(getArmatureName(pStaticDataCom->armatureFile));
	m_rootNode->addChild(m_actorRender);
#endif
}

void GAvatarComponent::playAnimation(const std::string& name, int32_t frame)
{
#if RUNTIME_IN_COOCS
	auto animation = m_actorRender->getAnimation();
	animation->play(name, -1, 0);
	if (frame > 0)
	{
		animation->gotoAndPlay(frame);
	}
#endif
}

void GAvatarComponent::onUpdate()
{
#if RUNTIME_IN_COOCS
	auto& offset = G_GetComponent(this, GStaticDataComponent)->offset;
	auto& transform = G_GetComponent(this, GActorComponent)->transform;

	auto rx = transform.p.x + offset.x;
	auto ry = transform.p.y + offset.y;
	m_rootNode->setPosition(rx.to_float(), ry.to_float());
	m_rootNode->setScaleX(transform.s.x.to_float());
#endif
}

NS_G_END

