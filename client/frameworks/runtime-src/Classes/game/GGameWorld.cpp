#include "GGameWorld.h"
#include "ecs/utils/CommonUtils.h"

GGameWorld::GGameWorld()
{
	m_rootNode = NULL;
	m_camera = NULL;
	m_pGlobal = NULL;
}

// 更新逻辑
void GGameWorld::update(float32 dt)
{
	m_pGlobal->fAccumilatedTime += dt;
	this->updateLogic(dt);
	m_pGlobal->gameLogicFrame++;
}

void GGameWorld::input(GUUID uuid, uint32_t frame, G_BIT_TYPE keydown)
{
	m_pGlobal->inputQue.addMsg<GOPMsg>(frame, uuid, keydown);
}

void GGameWorld::updateLogic(float32 dt)
{
	m_world.refresh();

	m_buffSystem.removeInvalid();

	m_armatureSystem.update(dt);
	m_collisionSystem.update();
	m_inputSystem.update();
	m_buffSystem.update();
	m_updateSystem.update(dt);
	m_SIMPhysSystem.update(dt);
	m_skillInjurySystem.update();

	m_transformSyncSystem.sync();
}

void GGameWorld::render()
{
	m_armatureRenderSystem.render();
	m_transformSyncSystem.syncRender();

#if G_DEBUG
	auto debugDrawNode = CommonUtils::getDebugDraw(m_world);
	if (debugDrawNode)
	{
		debugDrawNode->clear();
		m_armatureDebugSystem.debugDraw();
		m_SIMPhysSystem.debugDraw();
	}
#endif
}

