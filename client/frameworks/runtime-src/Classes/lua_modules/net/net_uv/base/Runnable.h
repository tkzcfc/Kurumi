#pragma once

#include "Common.h"

NS_NET_UV_BEGIN

class Runnable
{
public:
	Runnable();

	virtual ~Runnable();

	void startThread();

	void join();

	virtual void run() = 0;

protected:

	static void onThreadRun(void* arg);

protected:
	uv_thread_t* m_thread;
};


NS_NET_UV_END

