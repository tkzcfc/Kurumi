#pragma once


#include "TCPSocket.h"
#include "ThreadMsg.h"
#include <list>
#include <map>
#include <vector>
#include <queue>


class TCPServer
{
	//服务器所处阶段
	enum ServerStage
	{
		listen,//监听
		shall_disconnect,//即将断开
		shall_deleteSocket,//即将销毁socket
		shall_exit,//即将退出
		exit//退出
	};

public:

	TCPServer();
	TCPServer(const TCPServer&) = delete;

	~TCPServer();

	bool startServer(const char* ip, int port);

	bool getThreadMsg(ThreadMsg_S* msg);

	bool getAllThreadMsg(std::vector<ThreadMsg_S>* v);

	bool closeServer();

	//查询服务端是否已经关闭完毕
	//如果返回true，则可以进行该类的内存释放
	//若该函数返回false就进行内存释放，该类将阻塞至线程完全退出
	bool isCloseFinish();

protected:

	void pushThreadMsg(ThreadMsgType type, void* psocket, void* data = NULL, const int& len = 0, const TCPMsgTag& tag = TCPMsgTag::MT_DEFAULT);

	void addNewSocket(TCPSocket* s);

	void removeSocket(TCPSocket* s);

	void idleRun();

	void exitStart();

	void exitStep();

#if OPEN_UV_THREAD_HEARTBEAT == 1
	void heartRun();
#endif

protected:
	bool m_start;

	std::string m_ip;
	int m_port;

	TCPSocket* m_server;

	uv_idle_t* m_idle;
	uv_loop_t m_loop;
	uv_thread_t* m_thread;
	uv_async_t* m_eixtAsync;
	uv_timer_t* m_exitTimer;

	uv_mutex_t m_msgMutex;
	std::queue<ThreadMsg_S> m_msgQue;

	ServerStage m_serverStage;

#if OPEN_UV_THREAD_HEARTBEAT == 1
	uv_timer_t* m_heartTimer;
#endif

	struct tcpSocketData
	{
		tcpSocketData()
		{
#if OPEN_UV_THREAD_HEARTBEAT == 1
			curHeartTime = 0;
			curHeartCount = 0;
#endif
			isInvalid = false;
			releaseCount = 0;
			s = NULL;
		}
		TCPSocket* s;
		bool isInvalid;
		int releaseCount;
#if OPEN_UV_THREAD_HEARTBEAT == 1
		int curHeartTime;
		int curHeartCount;
#endif
	};

	std::list<tcpSocketData> allSocket;
protected:

	static void socket_callback(socket_call_type type, TCPSocket* s, void* data, void* userdata);

	static void thread_run(void* data);

	static void uv_on_idle_run(uv_idle_t* handle);

	static void uv_exit_async_callback(uv_async_t* handle);

	static void uv_exit_timer_callback(uv_timer_t* handle);

#if OPEN_UV_THREAD_HEARTBEAT == 1
	static void uv_heart_timer_callback(uv_timer_t* handle);
#endif
};
