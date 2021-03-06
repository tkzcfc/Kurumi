#include "GGameWorld.h"


// 每一帧的时间长度
float32 GGameWorld::GGameFrameLen = 1 / 40.0f;


GGameWorld::GGameWorld()
{
#if G_TARGET_CLIENT
	m_rootNode = NULL;
	m_camera = NULL;
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

void GGameWorld::input(const std::string& data)
{
	GOPMsg_Base* msgBase = (GOPMsg_Base*)data.c_str();
	m_pGlobal->inputQue.addMsg(msgBase);
}

void GGameWorld::updateLogic()
{
	m_world.refresh();

	m_buffSystem.removeInvalid();

	m_armatureSystem.update(GGameFrameLen);
	m_collisionSystem.update();
	m_inputSystem.update();
	m_buffSystem.update();
	m_updateSystem.update(GGameFrameLen);
	m_SIMPhysSystem.update(GGameFrameLen);
	m_skillInjurySystem.update();

	m_transformSyncSystem.sync();

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
}

void GGameWorld::render()
{
#if G_TARGET_CLIENT
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
#endif
}

