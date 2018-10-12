#include "Runnable.h"

NS_NET_UV_BEGIN

Runnable::Runnable()
	: m_thread(NULL)
{
}

Runnable::~Runnable()
{
}

void Runnable::startThread()
{
	this->join();
	m_thread = (uv_thread_t*)fc_malloc(sizeof(uv_thread_t));
	uv_thread_create(m_thread, onThreadRun, this);
}

void Runnable::join()
{
	if (m_thread == NULL)
		return;
	uv_thread_join(m_thread);
	fc_free(m_thread);
	m_thread = NULL;
}

void Runnable::onThreadRun(void* arg)
{
	Runnable* runnable = (Runnable*)arg;
	runnable->run();
}

NS_NET_UV_END