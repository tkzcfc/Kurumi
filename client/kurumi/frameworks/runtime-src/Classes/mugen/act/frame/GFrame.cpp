#include "GFrame.h"
#include "mugen/act/GAct.h"
#include "mugen/component/GActorComponent.h"

NS_G_BEGIN


GFrame::GFrame()
	: m_startFrame(0)
	, m_frameLen(0)
	, m_timeline(NULL)
	, m_pEntity(NULL)
	, m_type(GFrameType::UNKNOWN_FRAME)
{}

GFrame::~GFrame()
{}

void GFrame::serialize(GByteBuffer& byteBuffer)
{
	GObject::serialize(byteBuffer);
	byteBuffer.writeInt32(m_type);
	byteBuffer.writeInt32(m_startFrame);
	byteBuffer.writeInt32(m_frameLen);
}

bool GFrame::deserialize(GByteBuffer& byteBuffer)
{
	do
	{
		G_BREAK_IF(!GObject::deserialize(byteBuffer));
		
		
		G_BREAK_IF(!byteBuffer.getInt32(m_type));
		G_BREAK_IF(!byteBuffer.getInt32(m_startFrame));
		G_BREAK_IF(!byteBuffer.getInt32(m_frameLen));

		return true;
	} while (0);
	return false;
}

bool GFrame::contain(int32_t frame)
{
	if (m_frameLen < 0)
	{
		return m_startFrame <= frame;
	}

	if (frame < m_startFrame || frame > m_startFrame + m_frameLen)
		return false;
	return true;
}
GComponent* GFrame::getComponent(const std::string& name)
{
	G_ASSERT(m_pEntity != NULL);
	return m_pEntity->getComponent(name);
}

GSkill* GFrame::getSkill()
{
	return m_timeline->getSkill();
}

void GFrame::onEnter(int32_t currentFrameIndex)
{
	if (m_pEntity == NULL)
	{
		m_pEntity = m_timeline->getSkill()->getActorComponent()->getEntity();
	}
}

void GFrame::onUpdate(int32_t currentFrameIndex)
{}

void GFrame::onExit(int32_t currentFrameIndex)
{}

NS_G_END

