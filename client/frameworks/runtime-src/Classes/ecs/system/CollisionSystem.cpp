#include "CollisionSystem.h"
#include "ecs/utils/physics/GCollision.h"
#include "ecs/utils/CommonUtils.h"
#include "ecs/system/SkillInjurySystem.h"

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
	auto propertyA = entityB.getComponent<PropertyComponent>();
	auto propertyB = entityB.getComponent<PropertyComponent>();

	auto& injuryListA = entityA.getComponent<InjuryListComponent>();
	auto& injuryListB = entityB.getComponent<InjuryListComponent>();

	bool intersect = false;
	if (G_BIT_NO_EQUAL(propertyA.status, G_PS_IS_DEATH) && G_BIT_NO_EQUAL(propertyB.status, G_PS_IS_DEATH))
	{
		intersect = collision(entityA, entityB);
	}

	if (intersect)
	{
		// 攻击碰撞开始
		if (false == SkillInjurySystem::contain(injuryListA.victims, propertyB.uuid))
		{
			auto logicFrame = CommonUtils::getGlobalComponent(this->getWorld()).gameLogicFrame;
			SkillInjurySystem::add(injuryListA.victims, propertyB.uuid, logicFrame);
			SkillInjurySystem::add(injuryListB.attacker, propertyA.uuid, logicFrame);
		}
	}
	else
	{
		// 攻击碰撞结束
		if (SkillInjurySystem::contain(injuryListA.victims, propertyB.uuid))
		{
			SkillInjurySystem::remove(injuryListA.victims, propertyB.uuid);
			SkillInjurySystem::remove(injuryListB.attacker, propertyA.uuid);
		}
	}
}

bool CollisionSystem::collision(const anax::Entity& entityA, const anax::Entity& entityB)
{
	auto& filterBitsA = entityA.getComponent<FilterBitsComponent>();
	auto& filterBitsB = entityB.getComponent<FilterBitsComponent>();

	// 相同组,不进行碰撞判断
	if (filterBitsA.group == filterBitsB.group)
		return false;

	auto pAniDataA = getAnimData(entityA.getComponent<ArmatureComponent>());
	auto pAniDataB = getAnimData(entityB.getComponent<ArmatureComponent>());
	if (pAniDataA == NULL || pAniDataB == NULL)
		return false;

	auto& armatureA = entityA.getComponent<ArmatureComponent>();
	auto& armatureB = entityB.getComponent<ArmatureComponent>();

	auto kfAABBA = pAniDataA->kfaabbs[armatureA.curFrameIndex];
	auto kfAABBB = pAniDataB->kfaabbs[armatureB.curFrameIndex];
	auto kfColiA = pAniDataA->kfcollisions[armatureA.curFrameIndex];
	auto kfColiB = pAniDataB->kfcollisions[armatureB.curFrameIndex];
	if (kfAABBA == NULL || kfAABBB == NULL || kfColiA == NULL || kfColiB == NULL)
		return false;

	auto& transformA = entityA.getComponent<TransformComponent>();
	auto& transformB = entityB.getComponent<TransformComponent>();

	// 计算缩放位移后的值
	float x1a = kfAABBA->x * transformA.scaleX + transformA.position.x;
	float x2a = (kfAABBA->x + kfAABBA->w) * transformA.scaleX + transformA.position.x;
	float x1b = kfAABBB->x * transformB.scaleX + transformB.position.x;
	float x2b = (kfAABBB->x + kfAABBB->w) * transformB.scaleX + transformB.position.x;

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

	//! 此处只检测X轴相交
	// AABB测试失败
	if (maxxA < minxB || maxxB < minxA)
		return false;

	bool intersect = false;
	GAniRect aniRectA, aniRectB;
	//! 只计算A的攻击区域与B的防御区域的碰撞
	for (auto i = (int32_t)kAniRectType::RECT_ATK_A; i <= kAniRectType::RECT_ATK_B; ++i)
	{
		auto rectA = kfColiA->rect[i];
		if (rectA == NULL)
			continue;

		// 只计算缩放和位移
		for (auto vi = 0; vi < 4; ++vi)
		{
			aniRectA.v[vi].x = rectA->v[vi].x * transformA.scaleX + transformA.position.x;
			aniRectA.v[vi].y = rectA->v[vi].y * transformA.scaleY + transformA.position.y;
		}

		//! 获取B的防御区域
		auto rectB = kfColiB->rect[kAniRectType::RECT_HIT];
		if (rectB == NULL)
			break;

		// 只计算缩放和位移
		for (auto vi = 0; vi < 4; ++vi)
		{
			aniRectB.v[vi].x = rectB->v[vi].x * transformB.scaleX + transformB.position.x;
			aniRectB.v[vi].y = rectB->v[vi].y * transformB.scaleY + transformB.position.y;
		}
		// 碰撞检测
		if (GCollision::isRectIntersect(aniRectA.v, aniRectB.v))
		{
			///! 客户端debug
#if G_DEBUG
			//! 客户端绘制相应的攻击区域和防御区域
			auto drawNode = CommonUtils::getDebugDraw(this->getWorld());
			if (drawNode != NULL)
			{
				Vec2 pVertex[4];
				// 攻击区域绘制
				for (int32_t i = 0; i < 4; ++i)
				{
					pVertex[i].x = aniRectA.v[i].x;
					pVertex[i].y = aniRectA.v[i].y;
				}
				drawNode->drawPoly(pVertex, 4, true, Color4F::RED);
				// 防御区域绘制
				for (int32_t i = 0; i < 4; ++i)
				{
					pVertex[i].x = aniRectB.v[i].x;
					pVertex[i].y = aniRectB.v[i].y;
				}
				drawNode->drawPoly(pVertex, 4, true, Color4F::RED);
			}
#endif
			intersect = true;
			break;
		}
	}

	return intersect;
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


