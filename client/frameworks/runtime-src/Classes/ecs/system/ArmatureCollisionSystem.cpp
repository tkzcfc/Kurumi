#include "ArmatureCollisionSystem.h"
#include "cocostudio/CocoStudio.h"
#include "foundation/GameMath.h"

using namespace cocostudio;

ArmatureCollisionSystem::ArmatureCollisionSystem()
{
#if ENABLE_ARMATURE_COLLISION_DRAW_DEBUG == 1 
	m_debugDraw = NULL;
#endif
}

ArmatureCollisionSystem::~ArmatureCollisionSystem()
{}

void ArmatureCollisionSystem::setDebugDrawNode(DrawNode* debugDrawNode)
{
#if ENABLE_ARMATURE_COLLISION_DRAW_DEBUG == 1 
	m_debugDraw = debugDrawNode;
#endif
}

void ArmatureCollisionSystem::collisionTest()
{
	auto& entities = getEntities();

	int entityCount = (int)entities.size();

#if ENABLE_ARMATURE_COLLISION_DRAW_DEBUG != 1
	if (entityCount < 2)
	{
		return;
	}
#endif

	for (auto& it : entities)
	{
		ArmatureCollisionComponent& component = it.getComponent<ArmatureCollisionComponent>();
		component.m_attCacheDirty = true;
		component.m_defCacheDirty = true;
	}

#if ENABLE_ARMATURE_COLLISION_DRAW_DEBUG == 1
	debugDraw();
	if (entityCount < 2)
	{
		return;
	}
#endif

	for (auto i = 0 ; i < entityCount; ++i)
	{
		for (auto j = i + 1; j < entityCount; ++j)
		{
			const anax::Entity* entityA = &entities[i];
			const anax::Entity* entityB = &entities[j];

			if (false == isCollision(entityA, entityB))
			{
				continue;
			}

			if (false == this->AABBTest(entityA, entityB))
			{
				continue;
			}

#if ENABLE_ARMATURE_COLLISION_DRAW_DEBUG == 1
			if (m_debugDraw != NULL)
			{
				Rect& r = this->getAABBBox(&entityA->getComponent<ArmatureComponent>());
				cocos2d::Vec2 leftbottom(r.getMinX(), r.getMinY());
				cocos2d::Vec2 righttop(r.getMaxX(), r.getMaxY());
				m_debugDraw->drawRect(leftbottom, righttop, cocos2d::Color4F::GRAY);

				r = this->getAABBBox(&entityB->getComponent<ArmatureComponent>());
				leftbottom = cocos2d::Vec2(r.getMinX(), r.getMinY());
				righttop = cocos2d::Vec2(r.getMaxX(), r.getMaxY());
				m_debugDraw->drawRect(leftbottom, righttop, cocos2d::Color4F::GRAY);
			}
#endif

			auto & collisionComponentA = entityA->getComponent<ArmatureCollisionComponent>();
			auto & collisionComponentB = entityB->getComponent<ArmatureCollisionComponent>();

			// A -> B
			if (this->getAllAttRECT(entityA) && this->getAllDefRECT(entityB))
			{
				for (const auto& attR : collisionComponentA.m_attRectCache)
				{
					for (const auto& defR : collisionComponentB.m_defRectCache)
					{
						if (GameMath_IsIntersect(&attR.v[0], &defR.v[0]))
						{
#if ENABLE_ARMATURE_COLLISION_DRAW_DEBUG == 1
							if (m_debugDraw != NULL)
							{
								m_debugDraw->drawPoly(&attR.v[0], 4U, true, Color4F::RED);
								m_debugDraw->drawPoly(&defR.v[0], 4U, true, Color4F::RED);
							}
#endif
							// 发生碰撞
							if (collisionComponentA.m_attCollisionCall.isvalid())
							{
								collisionComponentA.m_attCollisionCall.ppush();
								collisionComponentA.m_attCollisionCall.pcall();
							}
							if (collisionComponentB.m_defCollisionCall.isvalid())
							{
								collisionComponentB.m_defCollisionCall.ppush();
								collisionComponentB.m_defCollisionCall.pcall();
							}
						}
					}
				}
			}

			// B -> A
			if (this->getAllAttRECT(entityB) && this->getAllDefRECT(entityA))
			{
				for (const auto& attR : collisionComponentB.m_attRectCache)
				{
					for (const auto& defR : collisionComponentA.m_defRectCache)
					{
						if (GameMath_IsIntersect(&attR.v[0], &defR.v[0]))
						{
#if ENABLE_ARMATURE_COLLISION_DRAW_DEBUG == 1
							if (m_debugDraw != NULL)
							{
								m_debugDraw->drawPoly(&attR.v[0], 4U, true, Color4F::RED);
								m_debugDraw->drawPoly(&defR.v[0], 4U, true, Color4F::RED);
							}
#endif
							// 发生碰撞
							if (collisionComponentB.m_attCollisionCall.isvalid())
							{
								collisionComponentB.m_attCollisionCall.ppush();
								collisionComponentB.m_attCollisionCall.pcall();
							}
							if (collisionComponentA.m_defCollisionCall.isvalid())
							{
								collisionComponentA.m_defCollisionCall.ppush();
								collisionComponentA.m_defCollisionCall.pcall();
							}
						}
					}
				}
			}
		}
	}
}

void ArmatureCollisionSystem::debugDraw()
{
	if (m_debugDraw == NULL)
		return;

	auto& entities = getEntities();

	int entityCount = (int)entities.size();
	if (entityCount < 1)
	{
		return;
	}

	for (auto& it : entities)
	{
		ArmatureComponent& armatureComponent = it.getComponent<ArmatureComponent>();
		if(armatureComponent.m_armature == NULL || armatureComponent.m_owner == NULL)
			continue;

		Rect& rect = this->getAABBBox(&armatureComponent);
		cocos2d::Vec2 leftbottom(rect.getMinX(), rect.getMinY());
		cocos2d::Vec2 righttop(rect.getMaxX(), rect.getMaxY());
		m_debugDraw->drawRect(leftbottom, righttop, cocos2d::Color4F::WHITE);

		this->getAllDefRECT(&it);
		this->getAllAttRECT(&it);
		ArmatureCollisionComponent& armatureCollisionComponent = it.getComponent<ArmatureCollisionComponent>();
		
		for (auto& v : armatureCollisionComponent.m_attRectCache)
		{
			m_debugDraw->drawPoly(&v.v[0], 4U, true, Color4F::GREEN);
		}

		for (auto& v : armatureCollisionComponent.m_defRectCache)
		{
			m_debugDraw->drawPoly(&v.v[0], 4U, true, Color4F::BLUE);
		}
	}
}

bool ArmatureCollisionSystem::AABBTest(const anax::Entity* entityA, const anax::Entity* entityB)
{
	static Rect rectA, rectB;

	const ArmatureComponent& componentA = entityA->getComponent<ArmatureComponent>();
	const ArmatureComponent& componentB = entityB->getComponent<ArmatureComponent>();

	if (componentA.m_armature == NULL || 
		componentA.m_owner == NULL || 
		componentB.m_armature == NULL || 
		componentB.m_owner == NULL)
	{
		return false;
	}

	rectA = componentA.m_armature->getBoundingBox();
	rectA = RectApplyTransform(rectA, componentA.m_owner->getNodeToParentTransform());
	rectA.origin.x = rectA.origin.x - rectA.size.width * 0.5f;
	rectA.size.width *= 2;

	rectB = componentB.m_armature->getBoundingBox();
	rectB = RectApplyTransform(rectB, componentB.m_owner->getNodeToParentTransform());
	rectB.origin.x = rectB.origin.x - rectB.size.width * 0.5f;
	rectB.size.width *= 2;

	return rectA.intersectsRect(rectB);
}

Rect& ArmatureCollisionSystem::getAABBBox(ArmatureComponent* component)
{
	static Rect rectA;

	rectA = component->m_armature->getBoundingBox();
	rectA = RectApplyTransform(rectA, component->m_owner->getNodeToParentTransform());
	rectA.origin.x = rectA.origin.x - rectA.size.width * 0.5f;
	rectA.size.width *= 2;

	return rectA;
}

bool ArmatureCollisionSystem::getAllAttRECT(const anax::Entity* entity)
{
	ArmatureCollisionComponent& collisionComponent = entity->getComponent<ArmatureCollisionComponent>();

	if (!collisionComponent.m_attCacheDirty)
	{
		return collisionComponent.m_attRectCache.size() > 0;
	}

	collisionComponent.m_attCacheDirty = false;
	collisionComponent.m_attRectCache.clear();

	ArmatureComponent& armatureComponent = entity->getComponent<ArmatureComponent>();

	ArmatureCollisionRect ar;
	const auto& boneDic = armatureComponent.m_armature->getBoneDic();

	for (auto it = boneDic.begin(); it != boneDic.end(); ++it)
	{
		Bone *bone = it->second;
		ColliderDetector *detector = bone->getColliderDetector();

		if (!detector || it->first.find("RECT_ATK_") == std::string::npos)
			continue;

		const cocos2d::Vector<ColliderBody*>& bodyList = detector->getColliderBodyList();

		for (auto& object : bodyList)
		{
			ColliderBody *body = static_cast<ColliderBody*>(object);
			const std::vector<Vec2> &vertexList = body->getCalculatedVertexList();

			unsigned long length = vertexList.size();

			if (length % 4 == 0)
			{
				for (unsigned long i = 0; i < length; i += 4)
				{
					for (unsigned long j = 0; j < 4; ++j)
					{
						Vec2 p = vertexList.at(i + j);
						p = PointApplyAffineTransform(p, armatureComponent.m_owner->getNodeToParentAffineTransform());
						ar.v[j].x = p.x;
						ar.v[j].y = p.y;
					}
					collisionComponent.m_attRectCache.push_back(ar);
				}
			}
		}
	}
	return collisionComponent.m_attRectCache.size() > 0;
}

bool ArmatureCollisionSystem::getAllDefRECT(const anax::Entity* entity)
{
	ArmatureCollisionComponent& collisionComponent = entity->getComponent<ArmatureCollisionComponent>();

	if (!collisionComponent.m_defCacheDirty)
	{
		return collisionComponent.m_defRectCache.size() > 0;
	}

	collisionComponent.m_defCacheDirty = false;
	collisionComponent.m_defRectCache.clear();

	ArmatureComponent& armatureComponent = entity->getComponent<ArmatureComponent>();

	ArmatureCollisionRect ar;
	const auto& boneDic = armatureComponent.m_armature->getBoneDic();

	for (auto it = boneDic.begin(); it != boneDic.end(); ++it)
	{
		Bone *bone = it->second;
		ColliderDetector *detector = bone->getColliderDetector();

		if (!detector || it->first.find("RECT_HIT") == std::string::npos)
			continue;

		const cocos2d::Vector<ColliderBody*>& bodyList = detector->getColliderBodyList();

		for (auto& object : bodyList)
		{
			ColliderBody *body = static_cast<ColliderBody*>(object);
			const std::vector<Vec2> &vertexList = body->getCalculatedVertexList();

			unsigned long length = vertexList.size();

			if (length % 4 == 0)
			{
				for (unsigned long i = 0; i < length; i += 4)
				{
					for (unsigned long j = 0; j < 4; ++j)
					{
						Vec2 p = vertexList.at(i + j);
						p = PointApplyAffineTransform(p, armatureComponent.m_owner->getNodeToParentAffineTransform());
						ar.v[j].x = p.x;
						ar.v[j].y = p.y;
					}
					collisionComponent.m_defRectCache.push_back(ar);
				}
			}
		}
	}

	return collisionComponent.m_defRectCache.size() > 0;
}

bool ArmatureCollisionSystem::isCollision(const anax::Entity* entityA, const anax::Entity* entityB)
{
	CollisionFilterComponent& comA = entityA->getComponent<CollisionFilterComponent>();
	CollisionFilterComponent& comB = entityB->getComponent<CollisionFilterComponent>();

	if (comA.m_collisionEnable == false || comB.m_collisionEnable == false)
	{
		return false;
	}

	return comA.m_groupIndex != comB.m_groupIndex;
}

