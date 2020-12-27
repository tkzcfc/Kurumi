#pragma once


#include "cocos2d.h"
#include "ecs/system/PhysicsSystem.h"
#include "ecs/system/GlobalSystem.h"

USING_NS_CC;

class TestPhysics : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	TestPhysics();

	virtual ~TestPhysics();

	virtual bool init();

	CREATE_FUNC(TestPhysics);


	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

	virtual void onTouchMoved(Touch *touch, Event *unused_event);

	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	virtual void onTouchCancelled(Touch *touch, Event *unused_event);


protected:

	void spawnCircle(const Vec2& pos);

	void spawnPolygon(const Vec2& pos);


	void logicUpdate(float);

protected:

	PhysicsSystem* m_physicsSystem;
	GlobalSystem m_globalSystem;

	anax::World m_world;

	DrawNode* m_drawNode;

	bool m_createCircle;
};
