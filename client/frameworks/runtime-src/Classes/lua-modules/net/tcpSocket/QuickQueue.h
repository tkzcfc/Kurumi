//#pragma once
//
//#include <queue>
//#include "TCPCommon.h"
//
//template <typename T>
//class QuickQueue
//{
//public:
//
//	QuickQueue()
//	{
//		m_lockWrite = false;
//		m_lockRead = false;
//		uv_mutex_init(&m_lockMut);
//		m_writeQue = new std::queue<T>();
//		m_readQue = new std::queue<T>();
//	}
//
//	~QuickQueue()
//	{
//		uv_mutex_destroy(&m_lockMut);
//		delete m_writeQue;
//		delete m_readQue;
//	}
//
//	inline void lockWrite()
//	{
//		m_lockWrite = true;
//	}
//
//	inline void unlockWrite()
//	{
//		m_lockWrite = false;
//	}
//
//	inline void lockRead()
//	{
//		m_lockRead = true;
//	}
//
//	inline void unlockRead()
//	{
//		m_lockRead = false;
//	}
//
//	inline std::queue<T>* getWriteQueue()
//	{
//		return m_writeQue;
//	}
//
//	inline std::queue<T>* getReadQueue()
//	{
//		return m_readQue;
//	}
//
//	void swap()
//	{
//		//if()
//
//		//uv_mutex_lock(&m_lockMut);
//		std::queue<T>* tmp = m_writeQue;
//		m_writeQue = m_readQue;
//		m_readQue = tmp;
//		//uv_mutex_unlock(&m_lockMut);
//	}
//
//private:
//	bool			m_lockWrite;
//	bool			m_lockRead;
//	std::queue<T>*	m_writeQue;
//	std::queue<T>*	m_readQue;
//	uv_mutex_t		m_lockMut;
//};
