#pragma once

#include "P2PPipe.h"

NS_NET_UV_BEGIN

class P2PTurn : public Runnable
{
public:

	P2PTurn();

	P2PTurn(const P2PTurn&) = delete;

	virtual ~P2PTurn();

	bool start(const char* ip, uint32_t port);

	void stop();

protected:
	/// Runnable
	virtual void run()override;

	void onIdleRun();

	void onPipeRecvJsonCallback(P2PMessageID msgID, rapidjson::Document& document, uint64_t key, const struct sockaddr* addr);
	
	void onPipeRecvKcpCallback(char* data, uint32_t len, uint64_t key, const struct sockaddr* addr);
	
	void onPipeNewSessionCallback(uint64_t key);
	
	void onPipeNewKcpCreateCallback(uint64_t key);
	
	void onPipeRemoveSessionCallback(uint64_t key);

protected:

	static void uv_on_idle_run(uv_idle_t* handle);

protected:
	P2PPipe m_pipe;

	enum TurnState
	{
		STOP,
		START,
		WILL_STOP,
	};
	TurnState m_state;
	uv_loop_t m_loop;
	uv_idle_t m_idle;
};

NS_NET_UV_END
