#include "GOPMsgQue.h"

NS_G_BEGIN

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

GOPMsg* GOPMsgQue::addMsg(GOPMsg* inMsg)
{
	auto msg = (GOPMsg*)m_allocator.Allocate(sizeof(GOPMsg));
	memcpy(msg, inMsg, sizeof(GOPMsg));
	m_msgQue.push_back(msg);
	return msg;
}

GOPMsg* GOPMsgQue::popMsg()
{
	auto msg = m_msgQue.front();
	m_msgQue.pop_front();
	return msg;
}


NS_G_END