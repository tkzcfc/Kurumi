#pragma once

#include "ecs/anaxHelper.h"
#include "ecs/utils/opmsg/GOPMsgQue.h"
#include "foundation/GRandom.h"

#if G_TARGET_CLIENT
#include "foundation/render/GMapLayer.h"
#endif

class GlobalComponent : public BaseComponent
{
public:
	GlobalComponent()
	{
		fAccumilatedTime = 0.0f;
		gameLogicFrame = 0U;
		uuidSeed = 0;

#if G_TARGET_CLIENT
		mapRender = NULL;
		debugDrawNode = NULL;
#endif
		mapWidth = 0.0f;
		mapHeight = 0.0f;
		minPosy = 0.0f;
		maxPosy = 0.0f;
	}

#if G_TARGET_CLIENT
	GMapLayer*	mapRender;
	DrawNode* debugDrawNode;
#endif


	///! 帧同步相关
	// 累计运行时间
	float32 fAccumilatedTime;
	// 游戏逻辑帧数
	uint32_t gameLogicFrame;


	///! 地图相关
	// 地图宽/高
	float32 mapWidth;
	float32 mapHeight;
	// 地图Y轴最小/最大值
	float32 minPosy;
	float32 maxPosy;


	// 输入消息队列
	GOPMsgQue inputQue;

	// 随机数生成器
	std::unique_ptr<GRandom> random;

	// GUUID种子
	GUUID uuidSeed;
};
