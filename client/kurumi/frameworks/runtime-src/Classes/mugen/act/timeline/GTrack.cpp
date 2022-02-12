#include "GTrack.h"

NS_G_BEGIN


GTrack::GTrack()
	: m_skill(NULL)
{}

GTrack::~GTrack()
{
	clear();
}

void GTrack::addTimeline(GTimeline* timeline)
{
	timeline->setTrack(this);
	m_timelines.push_back(timeline);
}

void GTrack::onEnter()
{
	for (auto it : m_timelines)
	{
		it->onEnter();
	}
}

void GTrack::apply(int32_t frame)
{
	for (auto it : m_timelines)
	{
		it->apply(frame);
	}
}

void GTrack::onExit()
{
	for (auto it : m_timelines)
	{
		it->onExit();
	}
}

int32_t GTrack::getTimelineIndex(GTimeline* timeline)
{
	for (int32_t i = 0; i < (int32_t)m_timelines.size(); ++i)
	{
		if (m_timelines[i] == timeline)
			return i;
	}
	return -1;
}

void GTrack::serialize(GByteBuffer& byteBuffer)
{
	GObject::serialize(byteBuffer);
	byteBuffer.writeUint32((uint32_t)m_timelines.size());

	for (auto it : m_timelines)
	{
		it->serialize(byteBuffer);
	}
}

bool GTrack::deserialize(GByteBuffer& byteBuffer)
{
	do
	{
		G_BREAK_IF(!GObject::deserialize(byteBuffer));

		uint32_t frameNum = 0;
		G_BREAK_IF(!byteBuffer.getUint32(frameNum));

		bool bRet = true;
		for (auto i = 0U; i < frameNum; ++i)
		{
			auto timeline = new GTimeline();
			if (timeline->deserialize(byteBuffer) == false)
			{
				delete timeline;
				bRet = false;
				break;
			}
			addTimeline(timeline);
		}

		if (!bRet)
		{
			this->clear();
		}
		return bRet;
	} while (0);
	return false;
}

void GTrack::clear()
{
	for (auto it : m_timelines)
	{
		delete it;
	}
	m_timelines.clear();
}

NS_G_END
