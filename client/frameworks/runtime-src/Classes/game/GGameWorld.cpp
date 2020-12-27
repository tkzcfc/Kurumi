#include "GGameWorld.h"

GGameWorld::GGameWorld()
{}

void GGameWorld::init()
{
	m_world.addSystem<ArmatureSystem>(m_armatureSystem);
	m_world.addSystem<CollisionSystem>(m_collisionSystem);
	m_world.addSystem<GlobalSystem>(m_globalSystem);
	m_world.addSystem<SIMPhysSystem>(m_SIMPhysSystem);
	m_world.addSystem<TransformSyncSystem>(m_transformSyncSystem);

	m_SIMPhysSystem.setGravity(GVec2(0.0f, -50.0f));

#if G_TARGET_CLIENT
	m_world.addSystem<ArmatureDebugSystem>(m_armatureDebugSystem);
	m_world.addSystem<ArmatureRenderSystem>(m_armatureRenderSystem);
#endif
}

#if G_TARGET_CLIENT
void GGameWorld::initRender(Node* rootNode)
{}
#endif

void GGameWorld::updateLogic(float32 dt)
{
	m_SIMPhysSystem.update(dt);
	m_transformSyncSystem.sync();

	m_armatureSystem.update(dt);
	m_collisionSystem.update();
}

void GGameWorld::render()
{
	m_armatureRenderSystem.render();
	m_armatureDebugSystem.debugDraw();
}


