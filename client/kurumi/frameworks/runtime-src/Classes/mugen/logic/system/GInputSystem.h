#pragma once

#include "GSystem.h"
#include "mugen/logic/opmsg/GOPMsgQue.h"

NS_G_BEGIN

class GInputSystem : public GSystem
{
public:

	GInputSystem();

	~GInputSystem();

	void step();

	// 操作消息队列
	G_SYNTHESIZE_REF_PTR(GOPMsgQue, m_inputQue, OPMsgQue);

};

NS_G_END
