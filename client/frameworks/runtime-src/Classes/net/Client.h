#pragma once

#include "cocos2d.h"
#include "tcpSocket/TCPClient.h"
#include "lua_function/LuaFunction.h"

typedef std::function<void(const ThreadMsg_C&)> netClientCallFunc;

class Client : public cocos2d::Ref
{
	static Client* Instance;

	Client();
	~Client();
public:

	static Client* getInstance();

	static void destroy();

	void setCallFunc(const netClientCallFunc& func);

	void setCallFunc(const LuaFunction& handle);

	//开始连接
	bool connect(const char* ip, int port, unsigned int key);

	void disconnect(unsigned int key);

	//关闭客户端，调用此函数之后客户端将准备退出线程，该类其他方法将统统无法调用
	void closeClient();
	//查询客户端是否已经关闭完毕
	//如果返回true，则可以进行该类的内存释放
	//若返回false就进行内存释放时，该类将阻塞至线程完全退出
	bool isCloseFinish();

	bool send(unsigned int key, char* data, unsigned int len);

	bool send(unsigned int key, char* data);

	//是否启用TCP_NODELAY
	bool setNoDelay(bool enable);

	//设置心跳
	bool setKeepAlive(int enable, unsigned int delay);

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

	void update(float);

protected:

	TCPClient* m_client;
	netClientCallFunc m_func;
	std::vector<ThreadMsg_C> m_threadMsg;

	LuaFunction m_luaHandle;
	bool m_luaHandleInvalid;
};
