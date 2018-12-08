#pragma once

#include "KCPCommon.h"
#include "KCPUtils.h"

NS_NET_UV_BEGIN

class KCPSocket;
class KCPSocketManager
{
public:
	KCPSocketManager(uv_loop_t* loop);

	virtual ~KCPSocketManager();
	
	IUINT32 getNewConv();

	void push(KCPSocket* socket);

	void remove(KCPSocket* socket);

	void stop_listen();

	inline void setOwner(KCPSocket* socket);

	inline KCPSocket* getOwner();
	
	inline int32_t getAwaitConnectCount();

	void idleRun();

	bool isAccept(const struct sockaddr* addr);

protected:

	int32_t isContain(const struct sockaddr* addr);

	void on_socket_connect(Socket* socket, int32_t status);

	void on_socket_close(Socket* socket);

	void connect(KCPSocket* socket);

	void removeAwaitConnectSocket(KCPSocket* socket);

	void clearInvalid();
	
protected:

	struct SMData
	{
		KCPSocket* socket;
		bool invalid;
	};

	uv_loop_t* m_loop;
	IUINT32 m_convCount;
	IUINT32 m_lastUpdateClock;
	
	bool m_isConnectArrDirty;
	bool m_isAwaitConnectArrDirty;

	std::vector<SMData> m_allConnectSocket;
	std::vector<SMData> m_allAwaitConnectSocket;

	std::map<std::string, IUINT32> m_recessTimeMap;

	KCPSocket* m_owner;
	bool m_stop;
};

void KCPSocketManager::setOwner(KCPSocket* socket)
{
	m_owner = socket;
}

KCPSocket* KCPSocketManager::getOwner()
{
	return m_owner;
}

int32_t KCPSocketManager::getAwaitConnectCount()
{
	return (int)m_allAwaitConnectSocket.size();
}

NS_NET_UV_END