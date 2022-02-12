#include "GEventFrame.h"

NS_G_BEGIN


GEventFrame::GEventFrame()
	: m_triggerMaxCount(0)
	, m_triggerInterval(0)
	, m_curTriggerCount(0)
	, m_lastTriggerFrameIndex(-1)
{
	m_type = GFrameType::EVENT_FRAME;
}

GEventFrame::~GEventFrame()
{}

void GEventFrame::onEnter(int32_t currentFrameIndex)
{
	GFrame::onEnter(currentFrameIndex);

	m_curTriggerCount = 0;
	m_lastTriggerFrameIndex = -1;
}

void GEventFrame::onUpdate(int32_t currentFrameIndex)
{
	GFrame::onUpdate(currentFrameIndex);

	if (canTrigger(currentFrameIndex))
	{
		onEmit();
		m_lastTriggerFrameIndex = currentFrameIndex;
		m_curTriggerCount++;
	}
}

void GEventFrame::onExit(int32_t currentFrameIndex)
{
	GFrame::onExit(currentFrameIndex);
}

bool GEventFrame::canTrigger(int32_t currentFrameIndex)
{
	// 有次数限制
	if (m_triggerMaxCount > 0)
	{
		// 达到次数限制
		if (m_curTriggerCount >= m_triggerMaxCount)
			return false;
	}

	// 已经触发过了才判断间隔
	if (m_curTriggerCount > 0 && m_triggerInterval > 0)
	{
		// 间隔时间未到
		if (currentFrameIndex - m_lastTriggerFrameIndex <= m_triggerInterval)
			return false;
	}

	return true;
}

void GEventFrame::serialize(GByteBuffer& byteBuffer)
{
	GFrame::serialize(byteBuffer);

	byteBuffer.writeInt32(m_triggerMaxCount);
	byteBuffer.writeInt32(m_triggerInterval);
}

bool GEventFrame::deserialize(GByteBuffer& byteBuffer)
{
	do
	{
		G_BREAK_IF(!GFrame::deserialize(byteBuffer));

		G_BREAK_IF(!byteBuffer.getInt32(m_triggerMaxCount));
		G_BREAK_IF(!byteBuffer.getInt32(m_triggerInterval));

		return true;
	} while (0);
	return false;
}

NS_G_END
