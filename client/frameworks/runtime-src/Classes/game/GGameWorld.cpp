#include "GGameWorld.h"
#include "ecs/utils/CommonUtils.h"

GGameWorld::GGameWorld()
{
	m_rootNode = NULL;
	m_camera = NULL;
	m_pGlobal = NULL;

	m_renderElapsedTime = 0.0f;
	m_lastRenderTime = 0.0f;
	m_targetRenderTime = 0.0f;
}

GGameWorld::~GGameWorld()
{
	m_world.clear();
}

// 更新逻辑
void GGameWorld::update(float dt)
{
	m_pGlobal->fAccumilatedTime += dt;
	this->updateLogic(dt);
	m_pGlobal->gameLogicFrame++;
}

void GGameWorld::input(GUUID uuid, uint32_t frame, G_BIT_TYPE keydown)
{
	m_pGlobal->inputQue.addMsg<GOPMsg>(frame, uuid, keydown);
}

void GGameWorld::updateLogic(float dt)
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

	m_lastRenderTime = m_renderElapsedTime;
	m_targetRenderTime = m_pGlobal->fAccumilatedTime;
}

void GGameWorld::render(float dt)
{
	if (m_renderElapsedTime > m_pGlobal->fAccumilatedTime)
		return;
	m_renderElapsedTime += dt;

	float percent = 1.0f;

	if (m_renderElapsedTime < m_targetRenderTime)
	{
		auto diff1 = m_targetRenderTime - m_renderElapsedTime;
		auto diff2 = m_targetRenderTime - m_lastRenderTime;
		if (diff2 > 0.0f)
		{
			percent = MIN(1.0f, diff1 / diff2);
		}
	}
	else
	{
		m_targetRenderTime = m_renderElapsedTime;
	}
	m_armatureRenderSystem.render();
	m_transformSyncSystem.syncRender(percent);

#if G_DEBUG
	auto debugDrawNode = CommonUtils::getDebugDraw(m_world);
	if (debugDrawNode)
	{
		//debugDrawNode->clear();
		//m_armatureDebugSystem.debugDraw();
		//m_SIMPhysSystem.debugDraw();
	}
#endif

	if (m_Player.isValid())
	{
		auto render = m_Player.getComponent<ArmatureRenderComponent>().render;
		auto property = m_Player.getComponent<PropertyComponent>();
		if (render)
		{
			if (G_BIT_EQUAL(property.status, G_PS_IS_FACE_R))
				m_camera->setCameraAnchorPoint(Vec2(0.3f, 0.0f));
			else
				m_camera->setCameraAnchorPoint(Vec2(0.7f, 0.0f));
			m_camera->setFocalPos(render->getPosition());
		}
	}
}

