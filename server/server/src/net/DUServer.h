#pragma once

#include "tcp/TCPServer.h"
#include "DUObject.h"
#include "DUScheduler.h"
#include "lua_function/LuaFunctionBond.h"

class DUServer : public DUObject, public LuaFunctionBond
{
public:
	DUServer();
	~DUServer();

	bool startServer(const char* ip, unsigned int port, bool isIPV6);

	bool stopServer();

	void send(net_uv::Session* session, char* data, unsigned int len);

	void disconnect(net_uv::Session* session);

	bool isCloseFinish();

	inline net_uv::TCPServer* getTCPServer();

protected:

	void update(float d);

	void onServerCloseCall(net_uv::Server* svr);

	void onServerNewConnectCall(net_uv::Server* svr, net_uv::Session* session);

	void onServerRecvCall(net_uv::Server* svr, net_uv::Session* session, char* data, unsigned int len);

	void onServerDisconnectCall(net_uv::Server* svr, net_uv::Session* session);

protected:
	net_uv::TCPServer* m_server;
};

net_uv::TCPServer* DUServer::getTCPServer()
{
	return m_server;
}
