#pragma once

#include "Common.h"

NS_NET_UV_BEGIN

class Mutex
{
public:
	Mutex();
	Mutex(const Mutex&) = delete;

	~Mutex();

	void lock();

	void unlock();

	int trylock();

protected:
	uv_mutex_t m_uv_mutext;
	int count;
};


NS_NET_UV_END

