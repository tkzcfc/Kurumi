#include "GAction.h"

NS_G_BEGIN


GAction::GAction()
	: m_delegate(NULL)
	, m_curFrame(-1)
	, m_startFrame(0)
	, m_endFrame(0)
	, m_id(-1)
	, m_curLoopCount(0)
	, m_maxLoopCount(1)
	, m_interrupt(GInterruptType::NONE)
{}

GAction::~GAction()
{}

void GAction::serialize(GByteBuffer& byteBuffer) 
{
	GObject::serialize(byteBuffer);

	byteBuffer.writeInt32(m_startFrame);
	byteBuffer.writeInt32(m_endFrame);
	byteBuffer.writeInt32(m_maxLoopCount);
	byteBuffer.writeInt32(m_id);
	byteBuffer.writeString(m_name);
	byteBuffer.writeString(m_playName);
}

bool GAction::deserialize(GByteBuffer& byteBuffer)
{
	if (!GObject::deserialize(byteBuffer))
		return false;

	do
	{
		G_BREAK_IF(!byteBuffer.getInt32(m_startFrame));
		G_BREAK_IF(!byteBuffer.getInt32(m_endFrame));
		G_BREAK_IF(!byteBuffer.getInt32(m_maxLoopCount));
		G_BREAK_IF(!byteBuffer.getInt32(m_id));
		G_BREAK_IF(!byteBuffer.getString(m_name));
		G_BREAK_IF(!byteBuffer.getString(m_playName));

		return true;
	} while (false);

	return false;
}

void GAction::reset()
{
	m_curLoopCount = 0;
	m_interrupt = GInterruptType::NONE;
	m_curFrame = m_startFrame;
	if (m_delegate)
	{
		m_delegate->onPlayAnimation(m_playName, m_curFrame);
	}
}

bool GAction::step()
{
	m_curFrame++;

	if (m_interrupt == GInterruptType::PROMPTLY)
	{
		return true;
	}

	if (m_curFrame > m_endFrame)
	{
		if (m_interrupt == GInterruptType::DELAY)
		{
			return true;
		}
		m_curLoopCount++;
		// 有限循环次数且循环次数达到上限,播放完毕
		if (m_maxLoopCount > 0 && m_curLoopCount >= m_maxLoopCount)
		{
			return true;
		}

		auto temp = m_curLoopCount;
		reset();
		m_curLoopCount = temp;
	}
	return false;
}

int32_t GAction::getElapsed()
{
	return m_curFrame - m_startFrame;
}

int32_t GAction::getFrameLength()
{
	return m_endFrame - m_startFrame + 1;
}

void GAction::interrupt(GInterruptType type)
{
	m_interrupt = type;
}

NS_G_END
