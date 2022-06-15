#pragma once

#include "mugen/base/GObject.h"

NS_G_BEGIN

class GChannel;
class GEntity;

enum class GConditionType
{
	SCRIPT_CONDITION,

	NONE,
};

/// 条件
class GCondition : public GObject
{
public:
	
	GCondition();
	
	virtual ~GCondition();

	bool doCheck();

	virtual bool check() = 0;

	virtual void reset() {}

	virtual void serialize(GByteBuffer& byteBuffer);

	virtual bool deserialize(GByteBuffer& byteBuffer);

	GEntity* getEntity();

	G_SYNTHESIZE(int32_t, m_beginFrame, BeginFrame);
	G_SYNTHESIZE(int32_t, m_frameLen, FrameLen);
	G_SYNTHESIZE_READONLY(GChannel*, m_pChannel, Channel);
	G_SYNTHESIZE(GConditionType, m_type, Type);

private:
	friend class GChannel;


};

NS_G_END