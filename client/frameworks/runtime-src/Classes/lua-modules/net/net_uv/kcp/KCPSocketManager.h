#pragma once

#include "KCPCommon.h"
#include "KCPUtils.h"

class KCPSocket;
class KCPSocketManager
{
public:
	KCPSocketManager(uv_loop_t* loop);

	virtual ~KCPSocketManager();

	KCPSocket* accept(uv_udp_t* handle, const struct sockaddr* addr);

	void push(KCPSocket* socket, IUINT32 conv);

	void remove(IUINT32 conv);

	void resetLastPacketRecvTime(IUINT32 conv);

	void input(IUINT32 conv, const char* data, long size);

	void disconnect(IUINT32 conv);

	void stop_listen();

	inline void setOwner(KCPSocket* socket);

protected:

	void idleRun();

protected:

	static void uv_on_idle_run(uv_idle_t* handle);

protected:
	uv_loop_t* m_loop;
	uv_idle_t m_idle;
	IUINT32 m_convCount;
	std::map<IUINT32, KCPSocket*> m_allSocket;

	KCPSocket* m_owner;
};

void KCPSocketManager::setOwner(KCPSocket* socket)
{
	m_owner = socket;
}
