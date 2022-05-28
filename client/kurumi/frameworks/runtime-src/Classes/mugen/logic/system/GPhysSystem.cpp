#include "GPhysSystem.h"
#include "mugen/logic/GGameWorld.h"

NS_G_BEGIN


GPhysSystem::GPhysSystem()
{
	// 重力设置
	m_gravity = GFixedVec3(0.0f, -9.8f * 3.0f, 0.0f);
	m_static_bodies.reserve(10);
	m_dynamic_bodies.reserve(10);
}

GPhysSystem::~GPhysSystem()
{}

void GPhysSystem::step()
{
	doFilter("GRigidBodyComponent");

	if (m_cacheComponents.empty()) 
		return;

	const auto& dt = LogicInterval;
	const fixedPoint one(1.0f);

	m_static_bodies.clear();
	m_dynamic_bodies.clear();

	GRigidBodyComponent* rigidBodyCom = NULL;
	for (auto& it : m_cacheComponents)
	{
		rigidBodyCom = (GRigidBodyComponent*)it;
		if (rigidBodyCom->isStatic)
			m_static_bodies.push_back(rigidBodyCom);
		else
			m_dynamic_bodies.push_back(rigidBodyCom);
	}

	for (auto b : m_dynamic_bodies)
	{
		// Integrate velocities
		b->linearVelocity += dt * b->invMass * (b->gravityScale * b->mass * m_gravity + b->force);

		// Apply damping
		b->linearVelocity *= one / (one + dt * b->linearDamping);
		
		GFixedVec3 df = b->linearVelocity;
		df = df * dt;

		df += b->offsetOneFrame;
		b->offsetOneFrame.setZero();
		
		//// Penetration correction
		//if (!df.x.isZero() && !collision(b, df.x, true))
		//{
		//	b->position.x += df.x;
		//}
		//if (!df.z.isZero() && !collision(b, df.z, false))
		//{
		//	b->position.z += df.z;
		//}

		// 直接使用map 范围来约束
		b->position.x += df.x;
		b->position.z += df.z;
		if (b->position.x < m_mapMin.x)
		{
			b->position.x = m_mapMin.x;
			b->linearVelocity.x.setZero();
		}
		if (b->position.x > m_mapMax.x - b->size.x)
		{
			b->position.x = m_mapMax.x - b->size.x;
			b->linearVelocity.x.setZero();
		}
		if (b->position.z < m_mapMin.y)
		{
			b->position.z = m_mapMin.y;
			b->linearVelocity.z.setZero();
		}
		if (b->position.z > m_mapMax.y - b->size.z)
		{
			b->position.z = m_mapMax.y - b->size.z;
			b->linearVelocity.z.setZero();
		}


		b->position.y += df.y;
		if (b->position.y < 0.0f)
		{
			b->position.y = 0.0f;
			b->linearVelocity.y.setZero();
		}

		// Clear force
		b->force.setZero();
	}
}


/*
 * 另一种方式：分轴测试
 * 原理：http://noonat.github.io/intersect/    
 * 代码：https://github.com/noonat/intersect/blob/master/src/intersect.ts intersectAABB方法,这种就不会发生错位现象但计算量更大
 * 现在实现类似于分轴测试的思想，由外部传入isx判断测试轴，暂时没有出现由于精度问题发生的错位现象
*/

bool GPhysSystem::collision(GRigidBodyComponent* component, const fixedPoint& offset, bool isx)
{
	bool negative = offset < 0.0f;

	auto minx = component->position.x;
	auto maxx = minx + component->size.x;
	auto minz = component->position.z;
	auto maxz = minz + component->size.z;

	/// 解决快速移动穿透问题 begin ///
	if (isx)
	{
		// offset < 0
		if (negative)
			minx += offset;
		else
			maxx += offset;
	}
	else
	{
		// offset < 0
		if (negative)
			minz += offset;
		else
			maxz += offset;
	}
	/// 解决快速移动穿透问题 end ///

	bool mark = false;
	for (auto& it : m_static_bodies)
	{
		const auto& x = it->position.x;
		const auto& z = it->position.z;

		bool test = maxx <= x || x + it->size.x <= minx || maxz <= z || z + it->size.z <= minz;
		if (false == test)
		{
			if (isx)
			{
				// offset < 0
				if (negative)
				{
					component->position.x = it->position.x + it->size.x;
					component->linearVelocity.x.setZero();
				}
				else
				{
					component->position.x = it->position.x - component->size.x;
					component->linearVelocity.x.setZero();
				}
			}
			else
			{
				// offset < 0
				if (negative)
				{
					component->position.z = it->position.z + it->size.z;
					component->linearVelocity.z.setZero();
				}
				else
				{
					component->position.z = it->position.z - component->size.z;
					component->linearVelocity.z.setZero();
				}
			}
			mark = true;
		}
	}

	return mark;
}

void GPhysSystem::debugDraw()
{	
	auto drawNode = GGameWorld::getInstance()->getMapLayer()->getDrawNode();

	Vec2 origin(m_mapMin.x.to_float() * PHYSICS_PIXEL_TO_METER, m_mapMin.y.to_float() * PHYSICS_PIXEL_TO_METER);
	Vec2 destination(m_mapMax.x.to_float() * PHYSICS_PIXEL_TO_METER, m_mapMax.y.to_float() * PHYSICS_PIXEL_TO_METER);
	Color4F color = Color4F::MAGENTA;
	color.a = 0.3f;
	drawNode->drawSolidRect(origin, destination, color);

	for (auto it : m_static_bodies)
	{
		auto x = it->position.x.to_float() * PHYSICS_PIXEL_TO_METER;
		auto y = it->position.y.to_float() * PHYSICS_PIXEL_TO_METER;
		auto z = it->position.z.to_float() * PHYSICS_PIXEL_TO_METER;

		auto w = it->size.x.to_float() * PHYSICS_PIXEL_TO_METER;
		auto zh = it->size.z.to_float() * PHYSICS_PIXEL_TO_METER;
		auto yh = it->size.y.to_float() * PHYSICS_PIXEL_TO_METER;

		if (zh > 1.0f && w > 1.0f)
		{
			Vec2 origin(x, z);
			Vec2 destination(origin.x + w, origin.y + zh);

			drawNode->drawSolidRect(origin, destination, Color4F(1.0f, 0.0f, 0.0f, 0.2));
			drawNode->drawRect(origin, destination, Color4F(1.0f, 0.0f, 0.0f, 0.8));
		}
		if (yh > 1.0f && w > 1.0f)
		{
			Vec2 origin(x, y + z);
			Vec2 destination(origin.x + w, origin.y + yh);

			drawNode->drawSolidRect(origin, destination, Color4F(0.0f, 0.8f, 0.0f, 0.1));
			drawNode->drawRect(origin, destination, Color4F(0.0f, 0.8f, 0.0f, 0.4));
		}
	}

	for (auto it : m_dynamic_bodies)
	{
		auto x = it->position.x.to_float() * PHYSICS_PIXEL_TO_METER;
		auto y = it->position.y.to_float() * PHYSICS_PIXEL_TO_METER;
		auto z = it->position.z.to_float() * PHYSICS_PIXEL_TO_METER;

		auto w = it->size.x.to_float() * PHYSICS_PIXEL_TO_METER;
		auto zh = it->size.z.to_float() * PHYSICS_PIXEL_TO_METER;
		auto yh = it->size.y.to_float() * PHYSICS_PIXEL_TO_METER;

		if(zh > 1.0f)
		{
			Vec2 origin(x, z);
			Vec2 destination(origin.x + w, origin.y + zh);

			drawNode->drawSolidRect(origin, destination, Color4F(0.3f, 0.3f, 0.8f, 0.2));
			drawNode->drawRect(origin, destination, Color4F(0.3f, 0.3f, 0.8f, 0.8));
		}
		if (yh > 1.0f)
		{
			Vec2 origin(x, y + z);
			Vec2 destination(origin.x + w, origin.y + yh);
			drawNode->drawSolidRect(origin, destination, Color4F(0.0f, 0.8f, 0.0f, 0.1));
			drawNode->drawRect(origin, destination, Color4F(0.0f, 0.8f, 0.0f, 0.4));
		}
	}
}

void GPhysSystem::setMapBox(const GFixedVec2& min, const GFixedVec2& max)
{
	m_mapMin = min;
	m_mapMax = max;
}

NS_G_END
