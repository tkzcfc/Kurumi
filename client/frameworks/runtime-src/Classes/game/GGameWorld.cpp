#include "GGameWorld.h"


// 每一帧的时间长度
float32 GGameWorld::GGameFrameLen = 1 / 60.0f;


GGameWorld::GGameWorld()
{
#if G_TARGET_CLIENT
	m_debugDrawNode = NULL;
#endif
	m_pGlobal = NULL;
}

// 更新逻辑
void GGameWorld::update(float32 dt)
{
	m_pGlobal->fAccumilatedTime += dt;
	while (m_pGlobal->fAccumilatedTime > m_pGlobal->fNextGameTime)
	{
		this->updateLogic();
		m_pGlobal->fNextGameTime += GGameFrameLen;
		m_pGlobal->gameLogicFrame++;
	}
}

void GGameWorld::updateLogic()
{
	m_world.refresh();

	m_SIMPhysSystem.update(GGameFrameLen);
	m_transformSyncSystem.sync();

	m_armatureSystem.update(GGameFrameLen);
	m_collisionSystem.update();

#if G_TARGET_CLIENT
	/*auto& admin = m_globalSystem.admin;
	auto& mapComponent = admin.getComponent<MapComponent>();

	const float step = 5.0f;

	auto viewPos = m_camera->getPosition();
	if (static_h_dir == MOVE_DIR::LEFT)
	{
		viewPos.x -= step;
	}
	else if (static_h_dir == MOVE_DIR::RIGHT)
	{
		viewPos.x += step;
	}
	if (static_v_dir == MOVE_DIR::TOP)
	{
		viewPos.y += step;
	}
	else if (static_v_dir == MOVE_DIR::BOTTOM)
	{
		viewPos.y -= step;
	}
	m_camera->setPosition(viewPos);*/
#endif

	m_inputSystem.beforeInput();
	if (m_inputQue.check(m_pGlobal->gameLogicFrame))
	{
		auto msg = m_inputQue.popMsg();
		m_inputSystem.input(msg);
		m_inputQue.freeMsg(msg);
	}
	m_inputSystem.afterInput();
}

void GGameWorld::render()
{
#if G_TARGET_CLIENT
	m_armatureRenderSystem.render();
	m_transformSyncSystem.syncRender();

#if G_DEBUG
	if (m_debugDrawNode)
	{
		m_debugDrawNode->clear();
		m_armatureDebugSystem.debugDraw();
		m_SIMPhysSystem.debugDraw();
	}
#endif
#endif
}

