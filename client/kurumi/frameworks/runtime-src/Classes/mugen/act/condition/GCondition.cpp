#include "GCondition.h"
#include "mugen/act/GSkill.h"

NS_G_BEGIN


GCondition::GCondition()
	: m_pChannel(NULL)
{
	m_type = GConditionType::NONE;
}

GCondition::~GCondition()
{}

bool GCondition::doCheck()
{
	auto curFrame = this->m_pChannel->getSkill()->getCurFrame();
	if (curFrame < m_beginFrame)
		return false;

	if (m_frameLen > 0 && curFrame > m_beginFrame + m_frameLen)
		return false;

	return check();
}

void GCondition::serialize(GByteBuffer& byteBuffer)
{
	GObject::serialize(byteBuffer);

	byteBuffer.writeInt32(m_beginFrame);
	byteBuffer.writeInt32(m_frameLen);
}


bool GCondition::deserialize(GByteBuffer& byteBuffer)
{
	do
	{
		G_BREAK_IF(!GObject::deserialize(byteBuffer));

		G_BREAK_IF(!byteBuffer.getInt32(m_beginFrame));
		G_BREAK_IF(!byteBuffer.getInt32(m_frameLen));

		return true;
	} while (false);
	return false;
}

GEntity* GCondition::getEntity()
{
	return this->getChannel()->getSkill()->getEntity();
}

NS_G_END