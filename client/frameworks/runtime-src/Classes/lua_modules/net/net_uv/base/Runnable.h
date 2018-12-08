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

	inline void* getUserData();

	inline void setUserData(void* userData);

protected:

	static void onThreadRun(void* arg);

protected:
	uv_thread_t* m_thread;
	void* m_userData;
};

void* Runnable::getUserData()
{
	return m_userData;
}

void Runnable::setUserData(void* userData)
{
	m_userData = userData;
}


NS_NET_UV_END

