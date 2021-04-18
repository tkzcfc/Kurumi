#pragma once

#include "lua_function/LuaFunctionBond.h"
#include "net_uv/net_uv.h"

class CCNetClient : public cocos2d::Ref, public LuaFunctionBond
{
public:

	static CCNetClient* create(bool useKcp);

	CCNetClient(bool useKcp);

	virtual ~CCNetClient();

	void connect(const char* ip, uint32_t port, uint32_t sessionId);

	void removeSession(uint32_t sessionId);

	void disconnect(uint32_t sessionId);

	void sendMsg(uint32_t sessionID, uint32_t msgID, char* data, uint32_t len);

	void setHeartBeatTime(uint32_t value);

	void setHeartBeatLoseMaxCount(uint32_t value);

	void closeClient();

protected:

	void update(float);

private:

	std::unique_ptr<net_uv::NetMsgMgr> m_msgMgr;
	std::unique_ptr<net_uv::Client> m_client;
};
