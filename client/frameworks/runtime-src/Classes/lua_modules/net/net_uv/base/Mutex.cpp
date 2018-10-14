#include "Mutex.h"


NS_NET_UV_BEGIN

Mutex::Mutex()
{
	count = 0;
	uv_mutex_init(&m_uv_mutext);
}

Mutex::~Mutex()
{
	uv_mutex_destroy(&m_uv_mutext);
}

void Mutex::lock()
{
	uv_mutex_lock(&m_uv_mutext);
	//assert(count == 0);
	//count++;
}

void Mutex::unlock()
{
	uv_mutex_unlock(&m_uv_mutext);
	//assert(count == 1);
	//count--;
}

int Mutex::trylock()
{
	//if (uv_mutex_trylock(&m_uv_mutext) == 0)
	//{
	//	//assert(count == 0);
	//	//count++;
	//	return 0;
	//}
	//else
	//	return 1;
	return uv_mutex_trylock(&m_uv_mutext);
}

NS_NET_UV_END