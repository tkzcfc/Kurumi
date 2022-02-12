#pragma once

#include "GSystem.h"
#include "mugen/component/GActorComponent.h"

NS_G_BEGIN

class GCollisionSystem : public GSystem
{
public:

	GCollisionSystem();

	~GCollisionSystem();

	void step();

private:

	bool test(GActorComponent* actorA, GActorComponent* actorB);

	void debugDraw();

private:

	G_SYNTHESIZE(bool, m_enableDebugDraw, EnableDebugDraw);
#if RUNTIME_IN_COOCS
	cocos2d::DrawNode* m_drawNode;
#endif
};

NS_G_END
