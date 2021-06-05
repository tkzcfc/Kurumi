#pragma once

#include "GameMacro.h"
#include "GOPMsg.h"

struct GGameWorldInitArgs
{
	// 地图id
	int32_t mapId;
	// 随机数种子
	uint32_t randomSeed;
	// uuid种子
	GUUID uuidSeed;
};

class GGameWorld
{
public:

	GGameWorld();

	bool init(const GGameWorldInitArgs& args);
	
	void updateFrame();

public:

	G_FORCEINLINE uint32_t getGameLogicFrame() const;

private:

	// 游戏逻辑帧数
	uint32_t m_gameLogicFrame;
};

uint32_t GGameWorld::getGameLogicFrame() const
{
	return m_gameLogicFrame;
}
