#include "GOPMsgQue.h"


GOPMsgQue::GOPMsgQue()
{}

GOPMsgQue::~GOPMsgQue()
{
	while (!m_msgQue.empty())
	{
		freeMsg(m_msgQue.front());
		m_msgQue.pop_front();
	}
}

GOPMsg_Base* GOPMsgQue::addMsg(GOPMsg_Base* inMsg)
{
	auto msg = (GOPMsg_Base*)m_allocator.Allocate(inMsg->msgSize);
	memcpy(msg, inMsg, inMsg->msgSize);
	m_msgQue.push_back(msg);
	return msg;
}

GOPMsg_Base* GOPMsgQue::popMsg()
{
	auto msg = m_msgQue.front();
	m_msgQue.pop_front();
	return msg;
}

