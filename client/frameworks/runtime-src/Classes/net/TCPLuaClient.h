#pragma once

#include "cocos2d.h"
#include "tcp/TCPClient.h"
#include "lua_function/LuaFunction.h"
#include "lua_function/LuaFunctionBond.h"

class TCPLuaClient : public cocos2d::Ref, public LuaFunctionBond
{
	static TCPLuaClient* Instance;

	TCPLuaClient();
	~TCPLuaClient();
public:

	static TCPLuaClient* getInstance();

	static void destroy();

	void connect(const char* ip, unsigned int port, unsigned int sessionId);

	void disconnect(unsigned int sessionId);

	void closeClient();

	void send(unsigned int sessionId, char* data, unsigned int len);

	void removeSession(unsigned int sessionId);

	void send(Session* session, char* data, unsigned int len);

	void disconnect(Session* session);

	bool isCloseFinish();

	//是否启用TCP_NODELAY
	bool setSocketNoDelay(bool enable);

	//设置心跳
	bool setSocketKeepAlive(int enable, unsigned int delay);

	//设置所有socket是否自动重连
	void setAutoReconnect(bool isAuto);

	//设置所有socket自动重连时间(单位：S)
	void setAutoReconnectTime(float time);

	//是否自动重连
	void setAutoReconnectBySessionID(unsigned int sessionID, bool isAuto);

	//自动重连时间(单位：S)
	void setAutoReconnectTimeBySessionID(unsigned int sessionID, float time);

	inline TCPClient* getTCPClient();

protected:

	void update(float);

	void onClientConnectCall(Client* client, Session* session, int status);

	void onClientDisconnectCall(Client* client, Session* session);

	void onClientRecvCall(Client* client, Session* session, char* data, unsigned int len);

	void onClientCloseCall(Client* client);

	void onClientRemoveSessionCall(Client* client, Session* session);

protected:

	TCPClient* m_client;
};

TCPClient* TCPLuaClient::getTCPClient()
{
	return m_client;
}

