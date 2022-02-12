#pragma once

#include "mugen/base/GComponent.h"
#include "mugen/geometry/GGeometry.h"

NS_G_BEGIN

class GAvatarComponent : public GComponent
{
public:

	G_DEFINE_COMPONENT(GAvatarComponent);

	GAvatarComponent();

	virtual ~GAvatarComponent();

	virtual void onAdd() override;

	virtual void onUpdate() override;

public:

	void playAnimation(const std::string& name, int32_t frame);
	
#if RUNTIME_IN_COOCS
	G_SYNTHESIZE_READONLY(cocostudio::Armature*, m_actorRender, ActorRender);
	G_SYNTHESIZE_READONLY(cocos2d::Node*, m_rootNode, RootNode);
#endif
};

NS_G_END
