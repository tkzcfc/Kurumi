#include "GGameLayer.h"
#if G_TARGET_CLIENT

bool GGameLayer::init()
{
	if (Node::init() == false)
		return false;

	m_world = new GGameWorld();
	// 6 9  14
	m_world->init(6, this);

	this->scheduleUpdate();

	return true;
}

void GGameLayer::update(float delta)
{
	Node::update(delta);
	m_world->update(delta);
	m_world->render();
}

#endif