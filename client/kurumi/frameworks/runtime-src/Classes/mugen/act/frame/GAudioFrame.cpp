#include "GAudioFrame.h"
#if RUNTIME_IN_COOCS
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#endif

NS_G_BEGIN


GAudioFrame::GAudioFrame()
{
	m_type = GFrameType::AUDIO_FRAME;
}

GAudioFrame::~GAudioFrame()
{}

void GAudioFrame::onEmit()
{
#if RUNTIME_IN_COOCS
	cocos2d::LuaEngine::getInstance()->getLuaStack()->executeGlobalFunctionWithString("onMugenAudioPlay", m_audio.c_str());
#endif
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
