#pragma once

#include "GameMacro.h"
#include "GOPMsg.h"

struct GGameWorldInitArgs
{
	GGameWorldInitArgs() 
	{
		::memset(this, 0, sizeof(GGameWorldInitArgs));
	}

	// 地图id
	int32_t mapId;
	// 随机数种子
	uint32_t randomSeed;
	// uuid种子
	GUUID uuidSeed;
	// 是否是离线模式
	bool isOfflineMode;
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
