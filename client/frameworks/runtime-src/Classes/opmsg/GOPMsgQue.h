#pragma once

#include "GOPMsg.h"
#include "foundation/allocator/GBlockAllocator.h"

// 游戏操作消息队列
class GOPMsgQue
{
public:

	GOPMsgQue();

	virtual ~GOPMsgQue();

	template<class T>
	T* addMsg(uint32_t logicFrame, int32_t uuid, G_BIT_TYPE cmd);

	GOPMsg_Base* addMsg(GOPMsg_Base* inMsg);
	
	G_FORCEINLINE void freeMsg(GOPMsg_Base* msg);

	// 外部使用完毕之后必须调用 freeMsg
	GOPMsg_Base* popMsg();

	G_FORCEINLINE bool empty() const;

	G_FORCEINLINE bool check(uint32_t frame) const;

private:

	GBlockAllocator m_allocator;
	std::deque<GOPMsg_Base*> m_msgQue;
};

template<class T>
T* GOPMsgQue::addMsg(uint32_t logicFrame, int32_t uuid, G_BIT_TYPE cmd)
{
	T* msg = (T*)m_allocator.Allocate(sizeof(T));
	msg->logicFrame = logicFrame;
	msg->uuid = uuid;
	msg->cmd = cmd;
	msg->msgSize = sizeof(T);
	m_msgQue.push_back(msg);
	return msg;
}


void GOPMsgQue::freeMsg(GOPMsg_Base* msg)
{
	m_allocator.Free(msg, msg->msgSize);
}

bool GOPMsgQue::empty() const
{
	return m_msgQue.empty();
}

bool GOPMsgQue::check(uint32_t frame) const
{
	return !m_msgQue.empty() && m_msgQue.front()->logicFrame <= frame;
}

