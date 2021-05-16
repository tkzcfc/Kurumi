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
	
	void update(float dt);

public:

	G_FORCEINLINE uint32_t getGameLogicFrame() const;

public:

	// 每一帧的时间长度
	static float GGameFrameLen;

private:

	///! 帧同步相关
	// 累计运行时间
	float m_fAccumilatedTime;
	// 下一个逻辑帧时间
	float m_fNextGameTime;
	// 游戏逻辑帧数
	uint32_t m_gameLogicFrame;
};

uint32_t GGameWorld::getGameLogicFrame() const
{
	return m_gameLogicFrame;
}
