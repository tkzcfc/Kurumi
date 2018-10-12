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

	void startServer(const char* ip, unsigned int port, bool isIPV6);

	bool stopServer();

	void send(Session* session, char* data, unsigned int len);

	void disconnect(Session* session);

	bool isCloseFinish();

	inline TCPServer* getTCPServer();

protected:

	void update(float d);

	void onServerStartCall(Server* svr, bool success);

	void onServerCloseCall(Server* svr);

	void onServerNewConnectCall(Server* svr, Session* session);

	void onServerRecvCall(Server* svr, Session* session, char* data, unsigned int len);

	void onServerDisconnectCall(Server* svr, Session* session);

protected:
	TCPServer* m_server;
};

TCPServer* DUServer::getTCPServer()
{
	return m_server;
}
