#pragma once

#include "net_uv/net_uv.h"
#include "lua_function/LuaFunctionBond.h"

template <typename T>
class CCClient : public cocos2d::Ref, public LuaFunctionBond
{
public:

	static CCClient* create()
	{
		auto client = new(std::nothrow) CCClient();
		client->autorelease();
		return client;
	}

	virtual ~CCClient()
	{
		Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
	}

	CCClient()
	{
		m_client = std::unique_ptr<T>(new T());
		m_client->setClientCloseCallback([=](net_uv::Client* client) 
		{
			auto pHandle = this->getLuaHandle("onClientCloseCallback");
			if (pHandle && pHandle->isvalid())
			{
				pHandle->ppush();
				pHandle->pcall();
			}
		});

		m_client->setConnectCallback([=](net_uv::Client* client, net_uv::Session* session, int32_t status)
		{
			auto pHandle = this->getLuaHandle("onConnectCallback");
			if (pHandle && pHandle->isvalid())
			{
				pHandle->ppush();
				pHandle->template pushusertype<net_uv::Session>(session, "net_uv::Session");
				pHandle->pusharg(status);
				pHandle->pcall();
			}
		});

		m_client->setDisconnectCallback([=](net_uv::Client* client, net_uv::Session* session)
		{
			auto pHandle = this->getLuaHandle("onDisconnectCallback");
			if (pHandle && pHandle->isvalid())
			{
				pHandle->ppush();
				pHandle->template pushusertype<net_uv::Session>(session, "net_uv::Session");
				pHandle->pcall();
			}
		});

		m_client->setRecvCallback([=](net_uv::Client* client, net_uv::Session* session, char* data, uint32_t len)
		{
			auto pHandle = this->getLuaHandle("onRecvCallback");
			if (pHandle && pHandle->isvalid())
			{
				pHandle->ppush();
				pHandle->template pushusertype<net_uv::Session>(session, "net_uv::Session");
				pHandle->pushlstring(data, len);
				pHandle->pcall();
			}
		});
		m_client->setRemoveSessionCallback([=](net_uv::Client* client, net_uv::Session* session)
		{
			auto pHandle = this->getLuaHandle("onRemoveSessionCallback");
			if (pHandle && pHandle->isvalid())
			{
				pHandle->ppush();
				pHandle->template pushusertype<net_uv::Session>(session, "net_uv::Session");
				pHandle->pcall();
			}
		});

		Director::getInstance()->getScheduler()->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&CCClient::update), this, 0.0f, false);
	}

	/// Client
	void connect(const char* ip, uint32_t port, uint32_t sessionId)
	{
		m_client->connect(ip, port, sessionId);
	}

	void closeClient()
	{
		m_client->closeClient();
	}

	void removeSession(uint32_t sessionId)
	{
		m_client->removeSession(sessionId);
	}

	/// SessionManager
	void disconnect(uint32_t sessionId)
	{
		m_client->disconnect(sessionId);
	}

	void send(uint32_t sessionId, char* data, uint32_t len)
	{
		m_client->send(sessionId, data, len);
	}

protected:

	void update(float)
	{
		m_client->updateFrame();
	}

private:
	std::unique_ptr<T> m_client;
};

typedef CCClient<net_uv::TCPClient> TCPClient;
typedef CCClient<net_uv::KCPClient> KCPClient;

