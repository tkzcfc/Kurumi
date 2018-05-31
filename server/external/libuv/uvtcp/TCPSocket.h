#pragma once

#include "TCPCommon.h"
#include "TCPBuffer.h"
#include <list>


enum socket_call_type
{
	connect_suc,	// 客户端连接服务器成功
	connect_fail,	// 客户端连接服务器失败
	connect_ing,	// 客户端正在连接服务器
	connect_timeout,// 客户端请求连接超时
	connect_new,	// 监听到有新的连接到来
	connect_close	// 连接关闭
};

class TCPSocket;
typedef void(*socket_call)(socket_call_type, TCPSocket*, void* data, void* userdata);
struct socket_call_data
{
	void* userdata;
	socket_call call;
};

struct blockdata
{
	char* data;
	unsigned int len;
};

enum tcpSocketState
{
	tcps_dis_connect,
	tcps_connecting,
	tcps_connect
};

class TCPSocket
{
public:
	TCPSocket() = delete;
	TCPSocket(const TCPSocket&) = delete;
	TCPSocket(uv_loop_t* loop, uv_tcp_t* tcp = NULL);
	
	virtual ~TCPSocket();

	void listen(const char* ip, unsigned int port);
	
	void connect(const char* ip, unsigned int port, unsigned int timeout);

	bool reconnect();

	bool isConnect();

	void disconnect();

	bool send(const char* data, unsigned int len);

	uv_tcp_t* getTcp();
	
	std::string getIp();
	
	unsigned int getPort();

	tcpSocketState getState();
	
	void setCallback(socket_call call, void* userdata);

	void* getCallbackUserdata();
	
	bool getAllRecvData(std::list<blockdata>* list);
	
	bool getRecvData(blockdata* data);

	bool setNoDelay(bool enable);

	bool setKeepAlive(int enable, unsigned int delay);

protected:
	void setTcp(uv_tcp_t* tcp);

	void setIp(const std::string ip);

	void setPort(unsigned int port);

	void setState(tcpSocketState state);

protected:

	void invokeCallback(socket_call_type type, void* data);

	void shutdownSocket();

	void clearWriteCache();

	void pushWriteData(const blockdata& data);
	
	void clearReadCache();

	void pushReadData(const blockdata& data);

	void write();

	void read(ssize_t nread, const uv_buf_t *buf);

	void resetReadBuffer();

	void stopConnectTimer();

protected:

	uv_loop_t* m_loop;
	uv_tcp_t* m_tcp;

	uv_mutex_t m_basedataMutex;
	std::string m_ip;
	unsigned int m_port;

	bool m_initConnectInfo;

	/// timeout
	unsigned int m_timeout;
	unsigned int m_curTime;
	uv_timer_t m_connectTimer;

	uv_async_t* m_writeAsync;
	uv_async_t* m_connectAsync;
	uv_async_t* m_listenAsync;
	uv_async_t* m_closeAsync;

	uv_mutex_t m_writeMutex;
	std::list<blockdata> m_writeCache;

	uv_mutex_t m_readMutex;
	std::list<blockdata> m_readCache;

	socket_call_data m_call;

	tcpSocketState m_state;

	//接收缓存
	TCPBuffer* m_recvBuffer;
protected:

	static void closeHandle(uv_handle_t* handle, uv_close_cb closecb);
	
	static void uv_close_async_callback(uv_async_t* handle);
	static void uv_write_async_callback(uv_async_t* handle);
	static void uv_connect_async_callback(uv_async_t* handle);
	static void uv_listen_async_callback(uv_async_t* handle);

	static void uv_on_close_socket(uv_handle_t* socket);
	static void uv_closehandle_defaultcallback(uv_handle_t* handle);

	static void uv_on_after_connect(uv_connect_t* handle, int status);
	static void uv_on_after_write(uv_write_t* req, int status);
	static void uv_on_after_read(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf);
	static void server_on_after_new_connection(uv_stream_t *server, int status);

	static void uv_alloc_buffer(uv_handle_t* handle, size_t  size, uv_buf_t* buf);

	static void uv_timer_run(uv_timer_t* handle);

};

