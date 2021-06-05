#include "GGameWorld.h"

GGameWorld::GGameWorld()
{
	m_gameLogicFrame = 0U;
}
/// init
bool GGameWorld::init(const GGameWorldInitArgs& args)
{
	return true;
}

// 更新逻辑
void GGameWorld::updateFrame()
{
	m_gameLogicFrame++;
}
