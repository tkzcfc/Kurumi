#pragma once

#include "ThreadMsg.h"
#include "TCPSocket.h"
#include <map>
#include <queue>


class TCPClient
{
public:
	enum CONNECTSTATE
	{
		CONNECT,	//已连接
		CONNECTING,	//正在连接
		DISCONNECTING,//正在断开
		DISCONNECT,//已断开
	};
public:

	TCPClient();
	TCPClient(const TCPClient&) = delete;
	~TCPClient();

	//开始连接
	bool connect(const char* ip, int port, unsigned int key, unsigned int timeout = 3000U);

	void disconnect(unsigned int key);

	//关闭客户端，调用此函数之后客户端将准备退出线程，该类其他方法将统统无法调用
	void closeClient();
	//查询客户端是否已经关闭完毕
	//如果返回true，则可以进行该类的内存释放
	//若返回false就进行内存释放时，该类将阻塞至线程完全退出
	bool isCloseFinish();

	bool send(unsigned int key, char* data, unsigned int len);

	//是否启用TCP_NODELAY
	bool setSocketNoDelay(bool enable);

	//设置心跳
	bool setSocketKeepAlive(int enable, unsigned int delay);

	bool getAllThreadMsg(std::vector<ThreadMsg_C>* v);

	TCPSocket* getSocketByKey(unsigned int key);

	TCPClient::CONNECTSTATE checkState(unsigned int key);

	TCPClient::CONNECTSTATE checkState(const char* ip, unsigned int port);

	//设置所有socket是否自动重连
	void setAutoReconnect(bool isAuto);

	//设置所有socket自动重连时间(单位：S)
	void setAutoReconnectTime(float time);

	//是否自动重连
	void setAutoReconnectByKey(unsigned int key, bool isAuto);

	//自动重连时间(单位：S)
	void setAutoReconnectTimeByKey(unsigned int key, float time);

protected:
	
	void run();

	void pushThreadMsg(ThreadMsgType type, unsigned int key, void* data = NULL, int len = 0);

	void socketIsConnect(unsigned int key, CONNECTSTATE state);

	struct clientsocketdata;
	TCPClient::clientsocketdata* getClientSocketDataByKey(unsigned int key);

protected:
	uv_loop_t m_loop;
	uv_thread_t m_thread;
	uv_async_t* m_exitAsync;
	uv_idle_t m_idle;
	uv_timer_t m_timer;

	bool m_reconnect;
	float m_totalTime;

	bool m_enableNoDelay;
	bool m_enableKeepAlive;
	int m_keepAliveDelay;



	struct clientsocketdata
	{
		CONNECTSTATE connectState;
		bool reconnect;
		float curtime;
		float totaltime;
		char ip[TCP_IP_ADDR_LEN];
		unsigned int port;
		TCPSocket* s;
	};

	//已经连接的socket
	uv_mutex_t m_socketMutex;
	std::map<unsigned int, clientsocketdata*> m_allSocketMap;

	//消息队列
	uv_mutex_t m_msgMutex;
	std::queue<ThreadMsg_C> m_msgQue;

	//客户端所处阶段
	enum class clientStage
	{
		start,
		shall_deleteSocket,//即将销毁socket
		shall_exit,//即将退出
		exit
	};
	clientStage m_clientStage;
protected:

	static void tcp_client_socket_callback(socket_call_type type, TCPSocket* s, void* data, void* userdata);

	static void onThreadRun(void* arg);

	static void uv_timer_run(uv_timer_t* handle);
	static void uv_exit_async_callback(uv_async_t* handle);
	static void uv_exit_async_closehandle_callback(uv_handle_t* handle);
	static void uv_on_idle_run(uv_idle_t* handle);
};



