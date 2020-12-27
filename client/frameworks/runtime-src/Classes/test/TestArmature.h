#pragma once

#include "cocos2d.h"
#include "ecs/system/ArmatureSystem.h"
#include "ecs/system/ArmatureRenderSystem.h"
#include "ecs/system/ArmatureDebugSystem.h"
#include "ecs/system/CollisionSystem.h"
#include "ecs/system/GlobalSystem.h"
#include "ecs/system/TransformSyncSystem.h"
#include "ecs/system/RenderSyncSystem.h"

USING_NS_CC;

class TestArmature : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(TestArmature);

protected:

	void spawnPlayer();

	void initMenu();

	void updateCMDMenu();

	void onMenuItemClickRole(Ref* sender);

	void onMenuItemClickCMD(Ref* sender);

	void logicUpdate(float);

protected:

	ArmatureSystem m_armatureSystem;
	ArmatureRenderSystem m_armatureRenderSystem;
	ArmatureDebugSystem m_armatureDebugSystem;
	CollisionSystem m_collisionSystem;
	GlobalSystem m_globalSystem;
	TransformSyncSystem m_transformSyncSystem;
	RenderSyncSystem m_renderSyncSystem;

	anax::World m_world;

	anax::Entity m_admin;
	anax::Entity m_player;

	DrawNode* m_drawNode;

	bool m_isFirst;

	std::string m_curRoleName;
	std::string m_curCMDName;
};
