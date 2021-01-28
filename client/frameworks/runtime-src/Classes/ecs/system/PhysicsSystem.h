#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/components/BodyComponent.h"


/// Original Author: 
/// https://github.com/RandyGaul/ImpulseEngine
class PhysicsSystem : public anax::System<anax::Requires<BodyComponent>>
{
public:
	PhysicsSystem() = delete;
	PhysicsSystem(uint32_t iterations);

	virtual ~PhysicsSystem();

	void update(float32 dt);

	void debugDraw();

private:

	class GManifold* get();

	void revert(class GManifold*);

private:

	std::vector<BodyComponent*> m_bodies;
	std::vector<class GManifold*> m_contacts;
	uint32_t m_iterations;

	struct CacheInfo 
	{
		class GManifold* m;
		bool free;
	};
	std::vector<CacheInfo> m_contactsPool;
public:

	// @brief 施加力
	static void applyForce(anax::Entity& entity, const GVec2& f);
	static void applyForce(BodyComponent* body, const GVec2& f);

	// @brief 施加冲力
	static void applyImpulse(anax::Entity& entity, const GVec2& impulse, const GVec2& contactVector);
	static void applyImpulse(BodyComponent* body, const GVec2& impulse, const GVec2& contactVector);

	// @brief 设置物体为静态物体
	static void setStatic(anax::Entity& entity);
	static void setStatic(BodyComponent* body);

	// @brief 旋转设置
	static void setRotation(anax::Entity& entity, real radians);
	static void setRotation(BodyComponent* body, real radians);

	// @brief 位置设置
	static void setPosition(anax::Entity& entity, real posx, real posy);
	static void setPosition(BodyComponent* body, real posx, real posy);

	// @param density 密度
	static void createCircleBody(anax::Entity& entity, real radius, real density  = 1.0f);

	static void createPolygonBody(anax::Entity& entity, GVec2 *vertices, uint32_t count, real density = 1.0f);

	static void createBoxBody(anax::Entity& entity, real halfWidth, real halfHeight, real density = 1.0f);

	static void computeMass(GCircle* shape, BodyComponent* body, real density);

	static void computeMass(GPolygonShape* shape, BodyComponent* body, real density);

	static GVec2 Gravity;
};
