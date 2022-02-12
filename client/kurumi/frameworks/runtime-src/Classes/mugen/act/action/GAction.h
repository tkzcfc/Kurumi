#pragma once

#include "mugen/base/GObject.h"

NS_G_BEGIN

class GActionDelegate
{
public:
	
	virtual void onPlayAnimation(const std::string& name, int32_t frame) = 0;
};

// 中断类型
enum class GInterruptType
{
	DELAY, // 延迟中断等待本次循环执行完毕
	PROMPTLY, // 立即中断

	NONE,	// 不中断
};

class GAction : public GObject
{
public:

	GAction();

	virtual ~GAction();

	virtual void serialize(GByteBuffer& byteBuffer) override;

	virtual bool deserialize(GByteBuffer& byteBuffer) override;

	virtual void reset();
	
	virtual bool step();

	int32_t getElapsed();

	int32_t getFrameLength();

	// @brief 中断
	void interrupt(GInterruptType type);

private:

	GInterruptType m_interrupt;

	G_SYNTHESIZE(int32_t, m_curLoopCount, CurLoopCount);
	
	G_SYNTHESIZE(int32_t, m_startFrame, StartFrame);
	G_SYNTHESIZE(int32_t, m_endFrame, EndFrame);
	G_SYNTHESIZE(int32_t, m_maxLoopCount, MaxLoopCount);
	G_SYNTHESIZE(int32_t, m_id, Id);
	G_SYNTHESIZE(std::string, m_name, Name);
	G_SYNTHESIZE(std::string, m_playName, PlayName);

	G_SYNTHESIZE(GActionDelegate*, m_delegate, ActionDelegate);

	G_SYNTHESIZE_READONLY(int32_t, m_curFrame, CurFrame);
};

NS_G_END
