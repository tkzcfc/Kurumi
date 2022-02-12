#include "GAudioFrame.h"

NS_G_BEGIN


GAudioFrame::GAudioFrame()
{
	m_type = GFrameType::AUDIO_FRAME;
}

GAudioFrame::~GAudioFrame()
{}

void GAudioFrame::onEmit()
{
}

void GAudioFrame::serialize(GByteBuffer& byteBuffer)
{
	GEventFrame::serialize(byteBuffer);

	byteBuffer.writeString(m_audio);
}

bool GAudioFrame::deserialize(GByteBuffer& byteBuffer)
{
	do
	{
		G_BREAK_IF(!GEventFrame::deserialize(byteBuffer));

		G_BREAK_IF(!byteBuffer.getString(m_audio));

		return true;
	} while (0);
	return false;
}


NS_G_END
