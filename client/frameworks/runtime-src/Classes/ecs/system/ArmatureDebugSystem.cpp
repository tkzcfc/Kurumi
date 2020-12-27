#include "ArmatureDebugSystem.h"
#include "CollisionSystem.h"
#include "ecs/utils/CommonUtils.h"

void ArmatureDebugSystem::debugDraw()
{
#if G_TARGET_CLIENT
	auto drawNode = CommonUtils::getDebugDraw(this->getWorld());
	if (drawNode == NULL)
		return;

	CollisionSystem* system = this->getWorld().getSystem<CollisionSystem>();
	if (system == NULL)
	{
		G_ASSERT(false);
		return;
	}

	GAnimationData* data = NULL;
	Vec2 lb, rt;
	GAniRect* pRect = NULL;
	Vec2 pVertex[4];
	for (auto& entity : this->getEntities())
	{
		auto& component = entity.getComponent<ArmatureComponent>();
		auto& transform = entity.getComponent<TransformComponent>();
		data = system->getAnimData(component);
		if (data == NULL)
			continue;

		GKfAABB* aabb = data->kfaabbs[component.curFrameIndex];
		if (aabb)
		{
			lb.x = aabb->x + transform.position.x;
			lb.y = aabb->y + transform.position.y;
			rt.x = lb.x + aabb->w;
			rt.y = lb.y + aabb->h;
			drawNode->drawRect(lb, rt, cocos2d::Color4F::GRAY);
		}

		GKfCollisions* collisions = data->kfcollisions[component.curFrameIndex];
		if (collisions == NULL) continue;
		do
		{
			pRect = collisions->rect[kAniRectType::RECT_HIT];
			if (pRect == NULL) break;

			for (int32_t i = 0; i < 4; ++i)
			{
				pVertex[i].x = pRect->v[i].x + transform.position.x;
				pVertex[i].y = pRect->v[i].y + transform.position.y;
			}
			drawNode->drawPoly(pVertex, 4, true, Color4F::GREEN);

		} while (0);


		do
		{
			pRect = collisions->rect[kAniRectType::RECT_ATK_A];
			if (pRect == NULL) break;

			for (int32_t i = 0; i < 4; ++i)
			{
				pVertex[i].x = pRect->v[i].x + transform.position.x;
				pVertex[i].y = pRect->v[i].y + transform.position.y;
			}
			drawNode->drawPoly(pVertex, 4, true, Color4F::BLUE);

		} while (0);


		do
		{
			pRect = collisions->rect[kAniRectType::RECT_ATK_B];
			if (pRect == NULL) break;

			for (int32_t i = 0; i < 4; ++i)
			{
				pVertex[i].x = pRect->v[i].x + transform.position.x;
				pVertex[i].y = pRect->v[i].y + transform.position.y;
			}
			drawNode->drawPoly(pVertex, 4, true, Color4F::BLUE);

		} while (0);
	}
#endif
}
