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
			float x1 = aabb->x * transform.scale + transform.position.x;
			float y1 = aabb->y * transform.scale + transform.position.y;
			float x2 = (aabb->x + aabb->w) * transform.scale + transform.position.x;
			float y2 = (aabb->y + aabb->h) * transform.scale + transform.position.y;

			lb.x = MIN(x1, x2);
			lb.y = MIN(y1, y2);
			rt.x = MAX(x1, x2);
			rt.y = MAX(y1, y2);
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
				pVertex[i].x = pRect->v[i].x * transform.scale + transform.position.x;
				pVertex[i].y = pRect->v[i].y * transform.scale + transform.position.y;
			}
			drawNode->drawPoly(pVertex, 4, true, Color4F::GREEN);

		} while (0);


		do
		{
			pRect = collisions->rect[kAniRectType::RECT_ATK_A];
			if (pRect == NULL) break;

			for (int32_t i = 0; i < 4; ++i)
			{
				pVertex[i].x = pRect->v[i].x * transform.scale + transform.position.x;
				pVertex[i].y = pRect->v[i].y * transform.scale + transform.position.y;
			}
			drawNode->drawPoly(pVertex, 4, true, Color4F::BLUE);

		} while (0);


		do
		{
			pRect = collisions->rect[kAniRectType::RECT_ATK_B];
			if (pRect == NULL) break;

			for (int32_t i = 0; i < 4; ++i)
			{
				pVertex[i].x = pRect->v[i].x * transform.scale + transform.position.x;
				pVertex[i].y = pRect->v[i].y * transform.scale + transform.position.y;
			}
			drawNode->drawPoly(pVertex, 4, true, Color4F::BLUE);

		} while (0);
	}
#endif
}
