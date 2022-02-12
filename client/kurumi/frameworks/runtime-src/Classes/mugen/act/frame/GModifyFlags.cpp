#include "GModifyFlags.h"
#include "mugen/component/GActorComponent.h"

NS_G_BEGIN

GModifyFlags::GModifyFlags()
{
	m_actorComponent = NULL;
	m_type = GFrameType::MODIFY_FLAGS_FRAME;
	setTriggerMaxCount(0);
	setTriggerInterval(0);
	m_modifyType = ModifyFlagsType::ADD_FLAGS;
	m_flags = 0;
}

GModifyFlags::~GModifyFlags()
{}

void GModifyFlags::onEnter(int32_t currentFrameIndex)
{
	GEventFrame::onEnter(currentFrameIndex);
}

void GModifyFlags::onEmit()
{
	if (m_flags != 0)
	{
		if (m_actorComponent == NULL)
		{
			m_actorComponent = G_GetComponent(this, GActorComponent);
		}
		switch (m_modifyType)
		{
		case ng::GModifyFlags::ModifyFlagsType::ADD_FLAGS:
			//m_actorComponent->addFlags();
			break;
		case ng::GModifyFlags::ModifyFlagsType::REMOVE_FLAGS:
			break;
		default:
			G_ASSERT(false);
			break;
		}
	}
}

void GModifyFlags::serialize(GByteBuffer& byteBuffer)
{
	GEventFrame::serialize(byteBuffer);

	byteBuffer.writeInt32((int32_t)m_modifyType);
	byteBuffer.writeUint32(m_flags);
}

bool GModifyFlags::deserialize(GByteBuffer& byteBuffer)
{
	do
	{
		G_BREAK_IF(!GEventFrame::deserialize(byteBuffer));

		auto value = byteBuffer.readInt32();
		if (value <= (int32_t)ModifyFlagsType::BEGIN || value >= (int32_t)ModifyFlagsType::MAX)
		{
			G_ASSERT(false);
			break;
		}
		m_modifyType = (ModifyFlagsType)value;

		G_BREAK_IF(!byteBuffer.getUint32(m_flags));

		return true;
	} while (0);
	return false;
}

NS_G_END