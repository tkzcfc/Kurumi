#pragma once


#include "cocos2d.h"
#include "tcp/TCPServer.h"
#include "lua_function/LuaFunction.h"
#include "lua_function/LuaFunctionBond.h"

class TCPLuaServer : public cocos2d::Ref, public LuaFunctionBond
{
public:
	TCPLuaServer();

	~TCPLuaServer();

	bool startServer(const char* ip, unsigned int port, bool isIPV6);

	bool stopServer();

	void send(net_uv::Session* session, char* data, unsigned int len);

	void disconnect(net_uv::Session* session);

	bool isCloseFinish();

	inline net_uv::TCPServer* getTCPServer();

protected:

	void update(float);
	
	void onServerCloseCall(net_uv::Server* svr);

	void onServerNewConnectCall(net_uv::Server* svr, net_uv::Session* session);

	void onServerRecvCall(net_uv::Server* svr, net_uv::Session* session, char* data, unsigned int len);

	void onServerDisconnectCall(net_uv::Server* svr, net_uv::Session* session);

protected:
	net_uv::TCPServer* m_server;
};

net_uv::TCPServer* TCPLuaServer::getTCPServer()
{
	return m_server;
}
