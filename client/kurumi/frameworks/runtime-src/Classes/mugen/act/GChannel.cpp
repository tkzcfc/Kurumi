#include "GChannel.h"
#include "mugen/GGameDef.h"
#include "condition/GScriptCondition.h"

NS_G_BEGIN


GChannel::GChannel()
	: m_nextSkillId(INVALID_SKILL_ID)
	, m_interruptType(GInterruptType::PROMPTLY)
	, m_checkType(CheckType::Once)
	, m_triggerTag(false)
	, m_skill(NULL)
{
	m_conditions.reserve(4);
}

GChannel::~GChannel()
{
	clear();
}

bool GChannel::check()
{
	if (m_triggerTag && m_checkType == CheckType::Once)
		return false;

	for (auto it : m_conditions)
	{
		if (!it->check())
			return false;
	}

	m_triggerTag = true;
	return true;
}

void GChannel::addCondition(GCondition* pCondition)
{
	pCondition->m_pChannel = this;
	m_conditions.push_back(pCondition);
}

void GChannel::clear()
{
	for (auto it : m_conditions)
	{
		delete it;
	}
	m_conditions.clear();
}

void GChannel::reset()
{
	m_triggerTag = false;
}

int32_t GChannel::getConditionIndex(GCondition* condition)
{
	for (int32_t i = 0; i < (int32_t)m_conditions.size(); ++i)
	{
		if (m_conditions[i] == condition)
			return i;
	}
	G_ASSERT(false);
	return -1;
}

void GChannel::serialize(GByteBuffer& byteBuffer)
{
	GObject::serialize(byteBuffer);

	
	byteBuffer.writeInt32(m_nextSkillId);
	byteBuffer.writeInt32((int32_t)m_interruptType);
	byteBuffer.writeInt32((int32_t)m_checkType);
	byteBuffer.writeInt32(m_conditions.size());
	for (auto it : m_conditions)
	{
		byteBuffer.writeInt32((int32_t)it->getType());
		it->serialize(byteBuffer);
	}
}

bool GChannel::deserialize(GByteBuffer& byteBuffer)
{
	do
	{
		G_BREAK_IF(!GObject::deserialize(byteBuffer));

		G_BREAK_IF(!byteBuffer.getInt32(m_nextSkillId));

		m_interruptType = (GInterruptType)byteBuffer.readInt32();
		m_checkType = (CheckType)byteBuffer.readInt32();


		int32_t count = 0;
		G_BREAK_IF(!byteBuffer.getInt32(count));

		bool bRet = true;
		for (auto i = 0; i < count; ++i)
		{
			int32_t type;
			if (!byteBuffer.getInt32(type))
			{
				bRet = false;
				break;
			}

			GCondition* ptr = NULL;

			if (type == (int32_t)GConditionType::SCRIPT_CONDITION)
			{
				ptr = new GScriptCondition();
			}


			if (ptr == NULL || ptr->deserialize(byteBuffer) == false)
			{
				G_ASSERT(false);
				bRet = false;
				break;
			}
			
			this->addCondition(ptr);
		}

		if (!bRet)
		{
			this->clear();
		}

		return bRet;
	} while (false);

	return false;
}

NS_G_END