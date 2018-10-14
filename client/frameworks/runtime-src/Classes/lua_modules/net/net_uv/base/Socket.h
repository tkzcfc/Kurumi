#pragma once


#include "Common.h"
#include "uv.h"
#include "Buffer.h"

NS_NET_UV_BEGIN

class Socket;
using SocketConnectCall = std::function<void(Socket*,int)>;	//0Ê§°Ü 1³É¹¦ 2³¬Ê±
using SocketCloseCall = std::function<void(Socket*)>; 
using SocketRecvCall = std::function<void(char*, ssize_t)>;

class Socket
{
public:
	Socket();
	virtual ~Socket();
	
	virtual bool bind(const char* ip, unsigned int port) = 0;

	virtual bool bind6(const char* ip, unsigned int port) = 0;

	virtual bool listen() = 0;

	virtual bool connect(const char* ip, unsigned int port) = 0;

	virtual bool send(char* data, int len) = 0;

	virtual void disconnect() = 0;

	inline void setConnectCallback(const SocketConnectCall& call);

	inline void setCloseCallback(const SocketCloseCall& call);

	inline void setRecvCallback(const SocketRecvCall& call);
public:

	inline const std::string& getIp();

	inline unsigned int getPort();

	inline bool isIPV6();

	inline void setIp(const std::string& ip);

	inline void setPort(unsigned int port);

	inline void setIsIPV6(bool isIPV6);

	inline void setUserdata(void* userdata);

	inline void* getUserdata();

	inline uv_loop_t* getLoop();

protected:

	static void uv_on_alloc_buffer(uv_handle_t* handle, size_t  size, uv_buf_t* buf);

protected:
	uv_loop_t* m_loop;
	uv_buf_t m_uvReadBuf;
	
	std::string m_ip;
	unsigned int m_port;
	bool m_isIPV6;

	void* m_userdata;

	SocketConnectCall m_connectCall;
	SocketCloseCall m_closeCall;
	SocketRecvCall m_recvCall;
};

const std::string& Socket::getIp()
{
	return m_ip;
}

void Socket::setIp(const std::string& ip)
{
	m_ip = ip;
}

unsigned int Socket::getPort()
{
	return m_port;
}

void Socket::setPort(unsigned int port)
{
	m_port = port;
}

bool Socket::isIPV6()
{
	return m_isIPV6;
}

void Socket::setIsIPV6(bool isIPV6)
{
	m_isIPV6 = isIPV6;
}

void Socket::setConnectCallback(const SocketConnectCall& call)
{
	m_connectCall = std::move(call);
}

void Socket::setCloseCallback(const SocketCloseCall& call)
{
	m_closeCall = std::move(call);
}

void Socket::setRecvCallback(const SocketRecvCall& call)
{
	m_recvCall = std::move(call);
}

void Socket::setUserdata(void* userdata)
{
	m_userdata = userdata;
}

void* Socket::getUserdata()
{
	return m_userdata;
}

uv_loop_t* Socket::getLoop()
{
	return m_loop;
}

NS_NET_UV_END