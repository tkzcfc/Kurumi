#pragma once

#include "GEventFrame.h"

NS_G_BEGIN

class GAudioFrame : public GEventFrame
{
public:

	GAudioFrame();

	virtual ~GAudioFrame();


	G_SYNTHESIZE(std::string, m_audio, Audio);

	virtual void onEmit() override;

public:

	virtual void serialize(GByteBuffer& byteBuffer) override;

	virtual bool deserialize(GByteBuffer& byteBuffer) override;

};

NS_G_END

