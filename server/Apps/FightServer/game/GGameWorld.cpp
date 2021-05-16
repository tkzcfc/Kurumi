#include "GGameWorld.h"

// 每一帧的时间长度
float GGameWorld::GGameFrameLen = 1 / 40.0f;

GGameWorld::GGameWorld()
{
	m_fAccumilatedTime = 0.0f;
	m_fNextGameTime = GGameFrameLen;
	m_gameLogicFrame = 0U;
}
/// init
bool GGameWorld::init(const GGameWorldInitArgs& args)
{
	return true;
}

// 更新逻辑
void GGameWorld::update(float dt)
{
	m_fAccumilatedTime += dt;
	while (m_fAccumilatedTime > m_fNextGameTime)
	{
		//this->updateLogic();
		m_fNextGameTime += GGameFrameLen;
		m_gameLogicFrame++;
	}
}
