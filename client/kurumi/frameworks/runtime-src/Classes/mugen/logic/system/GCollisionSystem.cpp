#include "GCollisionSystem.h"
#include "mugen/logic/GGameWorld.h"
#include "mugen/component/GActorComponent.h"
#include "mugen/component/GStaticDataComponent.h"
#include "mugen/component/GCollisionComponent.h"
#include "mugen/collision/GCollision.h"
#include "mugen/act/frame/GCollisionFrame.h"

NS_G_BEGIN

#if RUNTIME_IN_COOCS
static const Color4F Color_Att_Normal(1, 0, 0, 0.4);
static const Color4F Color_Def_Normal(0, 0, 1, 0.4);
static const Color4F Color_Att_Intersect(1, 0, 0, 1);
static const Color4F Color_Def_Intersect(0, 0, 1, 1);


static void drawCollisionFrame(cocos2d::DrawNode* render, GCollisionFrame* frame, const Color4F& color)
{
	auto shape = frame->getShape();
	switch (shape->getType())
	{
	case ECollisionType::RECT_AABB:
	case ECollisionType::POLYGON:
	{
		auto pPolygon = (GShapePolygon*)shape;

		Vec2 vertex[MAX_POLY_VERTEX_COUNT];
		GFixedVec2 tmp;
		for (auto i = 0; i < pPolygon->getVerticesCount(); ++i)
		{
			mulT_quick(pPolygon->getBody()->transform, pPolygon->getVertexs()[i], tmp);
			vertex[i].x = tmp.x.to_float();
			vertex[i].y = tmp.y.to_float();
		}

		render->drawPoly(vertex, pPolygon->getVerticesCount(), true, color);
	}break;
	case ECollisionType::CIRCLE:
	{
		auto pCircle = (GShapeCircle*)shape;

		GFixedVec2 tmp;
		mulT_quick(pCircle->getBody()->transform, pCircle->getCenter(), tmp);

		render->drawCircle(Vec2(tmp.x.to_float(), tmp.y.to_float()), pCircle->getRadius().to_float(), 0.0f, 60, false, color);
	}break;
	default:
		break;
	}
}
#endif





GCollisionSystem::GCollisionSystem()
	: m_enableDebugDraw(false)
{
}

GCollisionSystem::~GCollisionSystem()
{}

void GCollisionSystem::step()
{
	doFilter("GActorComponent");

	if (m_enableDebugDraw)
	{
		debugDraw();
	}

	for (size_t i = 0; i < m_cacheComponents.size(); ++i)
	{
		for (size_t j = i + 1; j < m_cacheComponents.size(); ++j)
		{
			test((GActorComponent*)m_cacheComponents[i], (GActorComponent*)m_cacheComponents[j]);
		}
	}
}

bool GCollisionSystem::test(GActorComponent* actorA, GActorComponent* actorB)
{
	auto pCollisionComponentA = G_GetComponent(actorA, GCollisionComponent);
	auto pCollisionComponentB = G_GetComponent(actorB, GCollisionComponent);

	if (false == pCollisionComponentA->canCollide(pCollisionComponentB))
	{
		return false;
	}

	auto& renderPosA = G_GetComponent(actorA, GActorComponent)->transform.p;
	auto& renderPosB = G_GetComponent(actorA, GActorComponent)->transform.p;
	auto& radiusA = G_GetComponent(actorA, GStaticDataComponent)->radius;
	auto& radiusB = G_GetComponent(actorA, GStaticDataComponent)->radius;


	auto minA = renderPosA.y - radiusA;
	auto maxA = renderPosA.y + radiusA;
	auto minB = renderPosB.y - radiusB;
	auto maxB = renderPosB.y + radiusB;

	if (maxA < minB || maxB < minA)
	{
		return false;
	}

	const auto& timelinesA = actorA->getCurSkill()->getTrack()->getTimelines();
	const auto& timelinesB = actorB->getCurSkill()->getTrack()->getTimelines();

	bool intersect = false;
	for (auto tla : timelinesA)
	{
		auto collisionAtk = (GCollisionFrame*)tla->getCurFrameByType(ATT_COLLISION_FRAME);
		if (collisionAtk)
		{
			for (auto tlb : timelinesB)
			{
				auto collisionDef = (GCollisionFrame*)tla->getCurFrameByType(DEF_COLLISION_FRAME);
				if (collisionDef && collisionAtk->intersects(collisionDef))
				{
					intersect = true;
					pCollisionComponentA->onCollision(pCollisionComponentB);

#if RUNTIME_IN_COOCS
					if (m_enableDebugDraw)
					{
						drawCollisionFrame(m_drawNode, collisionAtk, Color_Att_Intersect);
						drawCollisionFrame(m_drawNode, collisionDef, Color_Def_Intersect);
					}
#endif

					break;
				}
			}
		}

		G_BREAK_IF(intersect);
	}

	return intersect;
}

void GCollisionSystem::debugDraw()
{
#if RUNTIME_IN_COOCS
	m_drawNode = GGameWorld::getInstance()->getMapLayer()->getDrawNode();

	for (auto it : m_cacheComponents)
	{
		auto pActorComponent = (GActorComponent*)it;

		auto pSkill = pActorComponent->getCurSkill();
		if (pSkill)
		{
			auto& timelines = pSkill->getTrack()->getTimelines();
			for (auto timeline : timelines)
			{
				auto collisionAtk = (GCollisionFrame*)timeline->getCurFrameByType(ATT_COLLISION_FRAME);
				if (collisionAtk)
				{
					drawCollisionFrame(m_drawNode, collisionAtk, Color_Att_Normal);
				}
				auto collisionDef = (GCollisionFrame*)timeline->getCurFrameByType(DEF_COLLISION_FRAME);
				if (collisionDef)
				{
					drawCollisionFrame(m_drawNode, collisionDef, Color_Def_Normal);
				}
			}
		}
	}
#endif
}

NS_G_END
