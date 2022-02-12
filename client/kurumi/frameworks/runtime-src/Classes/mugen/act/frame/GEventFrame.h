#pragma once

#include "GFrame.h"

NS_G_BEGIN

class GEventFrame : public GFrame
{
public:

	GEventFrame();

	virtual ~GEventFrame();

	// 最大触发次数,0为一直触发
	G_SYNTHESIZE(int32_t, m_triggerMaxCount, TriggerMaxCount);
	// 触发间隔,默认0
	G_SYNTHESIZE(int32_t, m_triggerInterval, TriggerInterval);


	// 当前触发次数
	G_SYNTHESIZE_READONLY(int32_t, m_curTriggerCount, CurTriggerCount);
	// 最后一次触发帧数
	G_SYNTHESIZE_READONLY(int32_t, m_lastTriggerFrameIndex, LastTriggerFrameIndex);

	virtual void onEnter(int32_t currentFrameIndex) override;

	virtual void onUpdate(int32_t currentFrameIndex) override;

	virtual void onExit(int32_t currentFrameIndex) override;

public:

	virtual bool canTrigger(int32_t currentFrameIndex);

	virtual void onEmit() = 0;

public:

	virtual void serialize(GByteBuffer& byteBuffer) override;

	virtual bool deserialize(GByteBuffer& byteBuffer) override;

};

NS_G_END

