#pragma once


#include "cocos2d.h"
#include "kcp/KCPServer.h"
#include "lua_function/LuaFunction.h"
#include "lua_function/LuaFunctionBond.h"

class KCPLuaServer : public cocos2d::Ref, public LuaFunctionBond
{
public:
	KCPLuaServer();

	~KCPLuaServer();

	void startServer(const char* ip, unsigned int port, bool isIPV6);

	bool stopServer();
		
	void send(net_uv::Session* session, char* data, unsigned int len);

	void disconnect(net_uv::Session* session);

	bool isCloseFinish();

	inline net_uv::KCPServer* getKCPServer();

protected:

	void update(float);

	void onServerStartCall(net_uv::Server* svr, bool success);

	void onServerCloseCall(net_uv::Server* svr);

	void onServerNewConnectCall(net_uv::Server* svr, net_uv::Session* session);

	void onServerRecvCall(net_uv::Server* svr, net_uv::Session* session, char* data, unsigned int len);

	void onServerDisconnectCall(net_uv::Server* svr, net_uv::Session* session);

protected:
	net_uv::KCPServer* m_server;
};

net_uv::KCPServer* KCPLuaServer::getKCPServer()
{
	return m_server;
}
