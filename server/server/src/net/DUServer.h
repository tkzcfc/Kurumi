#pragma once

#include "uvtcp/TCPServer.h"
#include "DUObject.h"
#include "LuaFunction.hpp"
#include "DUScheduler.h"

typedef std::function<void(const ThreadMsg_S&)> netServerCallFunc;

class DUServer : public DUObject
{
public:
	DUServer();
	~DUServer();

	bool startServer(const char* ip, int port);

	bool closeServer();

	bool isCloseFinish();

	void setCallFunc(const LuaFunction& handle);

	void setCallFunc(const netServerCallFunc& func);

protected:

	void update(float d);

protected:
	TCPServer* m_server;
	
	std::vector<ThreadMsg_S> m_msgs;

	LuaFunction m_luaHandle;
	
	bool m_luaHandleInvalid;

	netServerCallFunc m_callFunc;
};