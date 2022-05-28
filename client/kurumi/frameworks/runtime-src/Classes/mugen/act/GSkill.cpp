#include "GSkill.h"
#include "mugen/component/GActorComponent.h"

NS_G_BEGIN


GSkill::GSkill()
	: m_curAction(NULL)
	, m_curActionIdx(-1)
	, m_curLoopCount(0)
	, m_totalLoopCount(1)
	, m_curFrame(0)
	, m_totalFrame(0)
	, m_actorComponent(NULL)
	, m_id(-1)
	, m_actionDelegate(NULL)
	, m_interrupt(GInterruptType::NONE_INTERRUPT)
{
	m_track = new GTrack();
	m_track->setSkill(this);
}

GSkill::~GSkill()
{
	delete m_track;
	clearAction();
	clearChannel();
}

void GSkill::serialize(GByteBuffer& byteBuffer)
{
	GObject::serialize(byteBuffer);
	m_track->serialize(byteBuffer);

	byteBuffer.writeString(m_name);
	byteBuffer.writeInt32(m_id);

	byteBuffer.writeInt32(m_totalFrame);

	byteBuffer.writeInt32(m_totalLoopCount);

	byteBuffer.writeInt32(m_actions.size());
	for (auto it : m_actions)
	{
		it->serialize(byteBuffer);
	}

	byteBuffer.writeInt32(m_channels.size());
	for (auto it : m_channels)
	{
		it->serialize(byteBuffer);
	}
}

bool GSkill::deserialize(GByteBuffer& byteBuffer)
{
	do
	{
		G_BREAK_IF(!GObject::deserialize(byteBuffer));
		G_BREAK_IF(!m_track->deserialize(byteBuffer));

		G_BREAK_IF(!byteBuffer.getString(m_name));
		G_BREAK_IF(!byteBuffer.getInt32(m_id));

		G_BREAK_IF(!byteBuffer.getInt32(m_totalFrame));

		G_BREAK_IF(!byteBuffer.getInt32(m_totalLoopCount));

		int32_t count = 0;
		G_BREAK_IF(!byteBuffer.getInt32(count));

		bool bRet = true;
		int32_t frameLength = 0;

		for (auto i = 0; i < count; ++i)
		{
			auto act = new GAction();
			if (!act->deserialize(byteBuffer))
			{
				delete act;
				clearAction();
				bRet = false;
				break;
			}
			frameLength += act->getFrameLength();
			addAction(act);
		}

		G_ASSERT(frameLength == m_totalFrame);


		G_BREAK_IF(!byteBuffer.getInt32(count));
		for (auto i = 0; i < count; ++i)
		{
			auto channel = new GChannel();
			if (!channel->deserialize(byteBuffer))
			{
				delete channel;
				clearChannel();
				bRet = false;
				break;
			}
			addChannel(channel);
		}

		return bRet;
	} while (false);
	
	return false;
}

void GSkill::reset()
{
	if (false == m_channels.empty())
	{
		for (auto it : m_channels)
		{
			it->reset();
		}
	}
	onEnter();
}

bool GSkill::step()
{
	if (m_actions.empty())
		return true;

	if (m_curAction == NULL)
	{
		m_curAction = m_actions[m_curActionIdx];
		m_curAction->reset();
	}

	m_curFrame = 0;
	for (auto i = 0; i < m_curActionIdx; ++i)
	{
		m_curFrame += m_actions[i]->getFrameLength();
	}
	m_curFrame += m_curAction->getElapsed();
	m_curFrame++;

	// update
	m_track->apply(m_curFrame);

	if (m_curAction->step())
	{
		m_curAction = NULL;
		m_curActionIdx++;

		// 播放完毕
		if (m_curActionIdx >= (int32_t)m_actions.size())
		{
			m_curActionIdx = 0;

			G_ASSERT(m_curFrame == m_totalFrame);
			m_curLoopCount++;

			if (m_interrupt == GInterruptType::DELAY)
			{
				this->interrupt(GInterruptType::PROMPTLY);
			}
			// 有限循环次数且循环次数达到上限,播放完毕
			else if (m_totalLoopCount > 0 && m_curLoopCount >= m_totalLoopCount)
			{
				this->interrupt(GInterruptType::PROMPTLY);
			}
		}
	}

	if (false == m_channels.empty())
	{
		for (auto it : m_channels)
		{
			if (it->check())
			{
				this->interrupt(it->getInterruptType());
				this->m_actorComponent->setNextSkillId(it->getNextSkillId());
				break;
			}
		}
	}

	if (m_interrupt == GInterruptType::PROMPTLY)
	{
		onExit();
		return true;
	}
	return false;
}

void GSkill::interrupt(GInterruptType type)
{
	m_interrupt = type;
}

void GSkill::onEnter()
{
	m_curFrame = 0;
	m_curLoopCount = 0;
	m_interrupt = GInterruptType::NONE_INTERRUPT;

	m_curAction = NULL;
	m_curActionIdx = 0;

	m_track->onEnter();
}

void GSkill::onExit()
{
	m_curFrame = 0;
	m_curLoopCount = 0;
	m_interrupt = GInterruptType::NONE_INTERRUPT;

	m_curAction = NULL;
	m_curActionIdx = 0;

	m_track->onExit();
}

void GSkill::addAction(GAction* action)
{
	action->setActionDelegate(m_actionDelegate);
	m_actions.push_back(action);
}

void GSkill::clearAction()
{
	for (auto it : m_actions)
	{
		delete it;
	}
	m_actions.clear();
}

void GSkill::addChannel(GChannel* channel)
{
	channel->setSkill(this);
	m_channels.push_back(channel);
}

void GSkill::clearChannel()
{
	for (auto it : m_channels)
	{
		delete it;
	}
	m_channels.clear();
}

void GSkill::setActionDelegate(GActionDelegate* delegate)
{
	for (auto it : m_actions)
	{
		it->setActionDelegate(delegate);
	}
	m_actionDelegate = delegate;
}

int32_t GSkill::getChannelIndex(GChannel* channel)
{
	for (int32_t i = 0; i < (int32_t)m_channels.size(); ++i)
	{
		if (m_channels[i] == channel)
			return i;
	}
	G_ASSERT(false);
	return -1;
}

GEntity* GSkill::getEntity()
{
	return m_actorComponent->getEntity();
}

NS_G_END
