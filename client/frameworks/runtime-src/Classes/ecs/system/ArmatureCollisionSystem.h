#pragma once

#include "ecs/components/ArmatureComponent.h"
#include "foundation/GameMacro.h"
#include "cocos2d.h"

using namespace cocos2d;


class ArmatureCollisionSystem : public anax::System<anax::Requires<ArmatureComponent, ArmatureCollisionComponent, CollisionFilterComponent>>, public Ref
{
public:

	ArmatureCollisionSystem();

	virtual ~ArmatureCollisionSystem();

	void setDebugDrawNode(DrawNode* debugDrawNode);

	void collisionTest();

protected:

	void debugDraw();

	bool AABBTest(const anax::Entity* entityA, const anax::Entity* entityB);

	Rect& getAABBBox(ArmatureComponent* component);

	bool getAllAttRECT(const anax::Entity* entity);

	bool getAllDefRECT(const anax::Entity* entity);

	bool isCollision(const anax::Entity* entityA, const anax::Entity* entityB);

protected:

#if ENABLE_ARMATURE_COLLISION_DRAW_DEBUG == 1
	DrawNode* m_debugDraw;
#endif
};


DEFINE_SYSTEM(ArmatureCollisionSystem);
