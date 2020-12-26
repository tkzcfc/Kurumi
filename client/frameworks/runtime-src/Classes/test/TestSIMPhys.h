#pragma once


#include "cocos2d.h"
#include "ecs/system/SIMPhysSystem.h"

USING_NS_CC;

class TestSIMPhys : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	TestSIMPhys();

	virtual ~TestSIMPhys();

	virtual bool init();

	CREATE_FUNC(TestSIMPhys);


	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

	virtual void onTouchMoved(Touch *touch, Event *unused_event);

	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	virtual void onTouchCancelled(Touch *touch, Event *unused_event);

	void logicUpdate(float);

protected:

	SIMPhysSystem* m_physicsSystem;

	anax::World m_world;
	anax::Entity m_player;

	enum MoveDir
	{
		MOVE_TO_LEFT,
		MOVE_TO_RIGHT,
		STOP
	};

	MoveDir m_moveDir;

	DrawNode* m_drawNode;
};
