#include "GTimeline.h"
#include <algorithm>
#include "mugen/act/GAct.h"

NS_G_BEGIN


GTimeline::GTimeline()
	: m_sortDirty(false)
	, m_curFrame(NULL)
	, m_frame(1)
	, m_track(NULL)
{}

GTimeline::~GTimeline()
{
	clearFrame();
}

void GTimeline::serialize(GByteBuffer& byteBuffer) 
{
	GObject::serialize(byteBuffer);
	byteBuffer.writeUint32((uint32_t)m_frames.size());

	for (auto it : m_frames)
	{
		byteBuffer.writeInt32(it->getType());
		it->serialize(byteBuffer);
	}
}

bool GTimeline::deserialize(GByteBuffer& byteBuffer)
{
	do
	{
		G_BREAK_IF(!GObject::deserialize(byteBuffer));

		uint32_t frameNum = 0;
		G_BREAK_IF(!byteBuffer.getUint32(frameNum));

		bool bRet = true;
		for (auto i = 0U; i < frameNum; ++i)
		{
			int32_t type = 0;
			if (byteBuffer.getInt32(type) == false)
			{
				bRet = false;
				break;
			}

			GFrame* pFrame = NULL;

			if (type == GFrameType::ATT_COLLISION_FRAME || type == GFrameType::DEF_COLLISION_FRAME)
			{
				pFrame = new GCollisionFrame();
			}
			else if (type == GFrameType::PHYSICAL_FORCE_FRAME)
			{
				pFrame = new GPhysicalForceFrame();
			}
			else if (type == GFrameType::EVENT_FRAME)
			{
				// GEventFrame不允许实例化
				G_ASSERT(0);
				//pFrame = new GEventFrame();
			}
			else if (type == GFrameType::AUDIO_FRAME)
			{
				pFrame = new GAudioFrame();
			}
			else if (type == GFrameType::SCRIPT_FRAME)
			{
				pFrame = new GScriptFrame();
			}
			
			if (pFrame == NULL)
			{
				G_ASSERT(0);
				bRet = false;
				break;
			}

			if (false == pFrame->deserialize(byteBuffer))
			{
				delete pFrame;
				bRet = false;
				break;
			}
			addFrame(pFrame, (GFrameType)type);
		}

		if (!bRet)
		{
			this->clearFrame();
		}
		return bRet;
	} while (0);
	return false;
}

void GTimeline::addFrame(GFrame* frame, GFrameType type)
{
	frame->setTimeline(this);
	frame->setType(type);
	m_frames.push_back(frame);
	m_sortDirty = true;
}

void GTimeline::removeFrame(GFrame* frame)
{
	for (auto it = m_frames.begin(); it != m_frames.end(); ++it)
	{
		if ((*it) == frame)
		{
			delete frame;
			m_frames.erase(it);
			m_sortDirty = true;
			break;
		}
	}
}

GFrame* GTimeline::getCurFrameByType(GFrameType type)
{
	auto pFrame = getCurFrame();
	if (pFrame && pFrame->getType() == type)
	{
		return pFrame;
	}
	return NULL;
}

GSkill* GTimeline::getSkill()
{
	if (m_track)
		return m_track->getSkill();

	return NULL;
}

void GTimeline::onEnter()
{
	m_curFrame = NULL;
	m_frame = 0;
}

void GTimeline::apply(int32_t frame)
{
	if (m_sortDirty)
	{
		doSort();
	}

	m_frame = frame;

	GFrame* curFrame = NULL;
	for (auto& it : m_frames)
	{
		if (it->contain(frame))
		{
			curFrame = it;
			break;
		}
	}

	if (curFrame == NULL)
	{
		if (m_curFrame)
		{
			m_curFrame->onExit(frame);
		}
		m_curFrame = NULL;
		return;
	}

	if (m_curFrame == curFrame)
	{
		m_curFrame->onUpdate(frame);
	}
	else
	{
		if (m_curFrame)
		{
			m_curFrame->onExit(frame);
		}

		m_curFrame = curFrame;
		m_curFrame->onEnter(frame);
		m_curFrame->onUpdate(frame);
	}
}

void GTimeline::onExit()
{
	if (m_curFrame)
	{
		if (m_curFrame)
		{
			m_curFrame->onExit(m_frame);
		}
		m_curFrame = NULL;
	}
}

void GTimeline::doSort()
{
	m_sortDirty = false;
	std::sort(m_frames.begin(), m_frames.end(), [](GFrame* a, GFrame* b)->bool
	{
		return b->getStartFrame() < a->getStartFrame();
	});
}

void GTimeline::clearFrame()
{
	for (auto& it : m_frames)
	{
		delete it;
	}
	m_frames.clear();
}

int32_t GTimeline::getFrameIndex(GFrame* frame)
{
	for (int32_t i = 0; i < (int32_t)m_frames.size(); ++i)
	{
		if (m_frames[i] == frame)
			return i;
	}
	return -1;
}

NS_G_END
