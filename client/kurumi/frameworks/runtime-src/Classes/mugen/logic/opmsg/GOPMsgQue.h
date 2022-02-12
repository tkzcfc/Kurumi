#pragma once

#include "GOPMsg.h"
#include "mugen/allocator/GBlockAllocator.h"
#include <deque>


NS_G_BEGIN

// 游戏操作消息队列
class GOPMsgQue
{
public:

	GOPMsgQue();

	virtual ~GOPMsgQue();

	template<class T>
	T* addMsg(uint32_t logicFrame, uint32_t uuid, G_BIT_TYPE cmd);

	GOPMsg* addMsg(GOPMsg* inMsg);
	
	G_FORCEINLINE void freeMsg(GOPMsg* msg);

	// 外部使用完毕之后必须调用 freeMsg
	GOPMsg* popMsg();

	G_FORCEINLINE bool empty() const;

	G_FORCEINLINE bool check(uint32_t frame) const;

private:

	GBlockAllocator m_allocator;
	std::deque<GOPMsg*> m_msgQue;
};

template<class T>
T* GOPMsgQue::addMsg(uint32_t logicFrame, uint32_t uuid, G_BIT_TYPE keydown)
{
	T* msg = (T*)m_allocator.Allocate(sizeof(T));
	msg->logicFrame = logicFrame;
	msg->uuid = uuid;
	msg->keydown = keydown;
	m_msgQue.push_back(msg);
	return msg;
}

void GOPMsgQue::freeMsg(GOPMsg* msg)
{
	m_allocator.Free(msg, sizeof(GOPMsg));
}

bool GOPMsgQue::empty() const
{
	return m_msgQue.empty();
}

bool GOPMsgQue::check(uint32_t frame) const
{
	return !m_msgQue.empty() && m_msgQue.front()->logicFrame <= frame;
}


NS_G_END