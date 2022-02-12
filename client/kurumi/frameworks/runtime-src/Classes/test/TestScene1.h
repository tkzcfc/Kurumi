#pragma once

#include "mugen/logic/GGameWorld.h"

USING_NS_G;

class TestScene1 : public Node
{
public:
	
	static Scene* createScene();

	static TestScene1* create();

	TestScene1();

	virtual ~TestScene1();

	virtual bool init() override;

	virtual void update(float dt) override;

private:

	GGameWorld* m_pWorld;

	G_BIT_TYPE m_input;

	GEntity* m_player;

	//struct Box
	//{
	//	GRigidBodyComponent* component;
	//	float waitTime;
	//};
	//std::vector<Box> m_otherBox;


	//float m_delayTime;
	//float m_lastPosx;
};
