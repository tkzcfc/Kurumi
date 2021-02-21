#include "CollisionSystem.h"
#include "ecs/utils/physics/GCollision.h"

void CollisionSystem::update()
{
	auto& entities = this->getEntities();

	for (int32_t i = 0; i < entities.size(); ++i)
	{
		for (int32_t j = i + 1; j < entities.size(); ++j)
		{
			test(entities[i], entities[j]);
		}
	}
}

void CollisionSystem::test(const anax::Entity& entityA, const anax::Entity& entityB)
{
	auto& propertyA = entityA.getComponent<PropertyComponent>();
	auto& propertyB = entityB.getComponent<PropertyComponent>();

	auto& armatureA = entityA.getComponent<ArmatureComponent>();
	auto& armatureB = entityB.getComponent<ArmatureComponent>();

	auto pAniDataA = getAnimData(entityA.getComponent<ArmatureComponent>());
	auto pAniDataB = getAnimData(entityB.getComponent<ArmatureComponent>());
	if (pAniDataA == NULL || pAniDataB == NULL)
		return;

	auto kfAABBA = pAniDataA->kfaabbs[armatureA.curFrameIndex];
	auto kfAABBB = pAniDataB->kfaabbs[armatureB.curFrameIndex];
	auto kfColiA = pAniDataA->kfcollisions[armatureA.curFrameIndex];
	auto kfColiB = pAniDataB->kfcollisions[armatureB.curFrameIndex];
	if (kfAABBA == NULL || kfAABBB == NULL || kfColiA == NULL || kfColiB == NULL)
		return;

	auto& transformA = entityA.getComponent<TransformComponent>();
	auto& transformB = entityB.getComponent<TransformComponent>();
	
	// 计算缩放位移后的值
	float x1a = kfAABBA->x * transformA.scale + transformA.position.x;
	float x2a = (kfAABBA->x + kfAABBA->w) * transformA.scale + transformA.position.x;
	float x1b = kfAABBB->x * transformB.scale + transformB.position.x;
	float x2b = (kfAABBB->x + kfAABBB->w) * transformB.scale + transformB.position.x;

	float minxA = x1a;
	float maxxA = x2a;
	float minxB = x1b;
	float maxxB = x2b;
	if (x1a > x2a) 
	{
		minxA = x2a;
		maxxA = x1a;
	}
	if (x1b > x2b)
	{
		minxB = x2b;
		maxxB = x1b;
	}

	// AABB测试失败
	if (maxxA < minxB || maxxB < minxA)
		return;

	//if (kfAABBA->x + kfAABBA->w < kfAABBB->x || kfAABBB->x + kfAABBB->w < kfAABBA->x)
	//{
	//	return;
	//}


	bool intersect = false;
	GAniRect aniRectA, aniRectB;
	for (auto i = 0; i < kAniRectType::RECT_COUNT; ++i)
	{
		auto rectA = kfColiA->rect[i];
		if (rectA == NULL)
			break;

		// 只计算缩放和位移
		for (auto vi = 0; vi < 4; ++vi)
		{
			aniRectA.v[vi].x = rectA->v[vi].x * transformA.scale + transformA.position.x;
			aniRectA.v[vi].y = rectA->v[vi].y * transformA.scale + transformA.position.y;
		}

		for (auto j = 0; j < kAniRectType::RECT_COUNT; ++j)
		{
			auto rectB = kfColiB->rect[j];
			if (rectB == NULL)
				break;

			// 只计算缩放和位移
			for (auto vi = 0; vi < 4; ++vi)
			{
				aniRectB.v[vi].x = rectB->v[vi].x * transformB.scale + transformB.position.x;
				aniRectB.v[vi].y = rectB->v[vi].y * transformB.scale + transformB.position.y;
			}

			if (GCollision::isRectIntersect(aniRectA.v, aniRectB.v))
			{
				intersect = true;
				break;
			}
		}

		if (intersect)
			break;
	}

	if (intersect == false)
		return;
}

GAnimationData* CollisionSystem::getAnimData(ArmatureComponent& component)
{
	if (component.roleName.empty())
		return NULL;

	auto tmp = GAnimDataCache::getInstance()->getOrCreate(component.roleName);
	if (tmp == NULL)
		return NULL;

	auto aniData = tmp->getAniData(component.curAniName);
	if (aniData == NULL)
		return NULL;

	if (component.curFrameIndex >= aniData->duration)
	{
		G_ASSERT(false);
		return NULL;
	}
	return aniData;
}


inline void transformVec4(const float* m, float x, float y, float z, float w, float* dst)
{
	dst[0] = x * m[0] + y * m[4];// + z * m[8] + w * m[12];
	dst[1] = x * m[1] + y * m[5];// + z * m[9] + w * m[13];
	//dst[2] = x * m[2] + y * m[6];// + z * m[10] + w * m[14];
}

//x 0 0 0
//0 y 0 0
//0 0 z 0
//0 0 0 0

