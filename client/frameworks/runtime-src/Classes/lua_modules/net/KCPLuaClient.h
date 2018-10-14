#pragma once

#include "cocos2d.h"
#include "kcp/KCPClient.h"
#include "lua_function/LuaFunction.h"
#include "lua_function/LuaFunctionBond.h"

class KCPLuaClient : public cocos2d::Ref, public LuaFunctionBond
{
	static KCPLuaClient* Instance;

	KCPLuaClient();
	virtual ~KCPLuaClient();
public:

	static KCPLuaClient* getInstance();

	static void destroy();

	void connect(const char* ip, unsigned int port, unsigned int sessionId);

	void disconnect(unsigned int sessionId);

	void closeClient();

	void send(unsigned int sessionId, char* data, unsigned int len);

	void removeSession(unsigned int sessionId);

	void send(net_uv::Session* session, char* data, unsigned int len);

	void disconnect(net_uv::Session* session);

	bool isCloseFinish();

	//设置所有socket是否自动重连
	void setAutoReconnect(bool isAuto);

	//设置所有socket自动重连时间(单位：S)
	void setAutoReconnectTime(float time);

	//是否自动重连
	void setAutoReconnectBySessionID(unsigned int sessionID, bool isAuto);

	//自动重连时间(单位：S)
	void setAutoReconnectTimeBySessionID(unsigned int sessionID, float time);

	inline net_uv::KCPClient* getKCPClient();

protected:

	void update(float);

	void onClientConnectCall(net_uv::Client* client, net_uv::Session* session, int status);

	void onClientDisconnectCall(net_uv::Client* client, net_uv::Session* session);

	void onClientRecvCall(net_uv::Client* client, net_uv::Session* session, char* data, unsigned int len);

	void onClientCloseCall(net_uv::Client* client);

	void onClientRemoveSessionCall(net_uv::Client* client, net_uv::Session* session);

protected:

	net_uv::KCPClient* m_client;
};

net_uv::KCPClient* KCPLuaClient::getKCPClient()
{
	return m_client;
}

