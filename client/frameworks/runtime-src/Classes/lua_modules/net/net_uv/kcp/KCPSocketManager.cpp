#include "KCPSocketManager.h"
#include "KCPSocket.h"

NS_NET_UV_BEGIN

KCPSocketManager::KCPSocketManager(uv_loop_t* loop)
	: m_convCount(1000)
	, m_owner(NULL)
	, m_stop(false)
	, m_isConnectArrDirty(false)
	, m_isAwaitConnectArrDirty(false)
{
	m_loop = loop;

	m_allAwaitConnectSocket.reserve(200);
	m_allConnectSocket.reserve(200);

	m_lastUpdateClock = iclock();
}

KCPSocketManager::~KCPSocketManager()
{
}

void KCPSocketManager::push(KCPSocket* socket)
{
	for (auto& it : m_allAwaitConnectSocket)
	{
		if (it.socket == socket)
		{
			return;
		}
	}

	SMData data;
	data.invalid = false;
	data.socket = socket;
	m_allAwaitConnectSocket.push_back(data);

	socket->setConnectCallback(std::bind(&KCPSocketManager::on_socket_connect, this, std::placeholders::_1, std::placeholders::_2));
	socket->setCloseCallback(std::bind(&KCPSocketManager::on_socket_close, this, std::placeholders::_1));
}

IUINT32 KCPSocketManager::getNewConv()
{
	m_convCount++;
	return m_convCount;
}

void KCPSocketManager::remove(KCPSocket* socket)
{
	for (auto& it : m_allConnectSocket)
	{
		if (it.socket == socket)
		{
			it.invalid = true;
			m_isConnectArrDirty = true;
			break;
		}
	}
}

void KCPSocketManager::stop_listen()
{
	m_stop = true;

	for (auto& it : m_allConnectSocket)
	{
		it.socket->disconnect();
	}

	for (auto& it : m_allAwaitConnectSocket)
	{
		it.socket->disconnect();
	}
}

int32_t KCPSocketManager::isContain(const struct sockaddr* addr)
{
	std::string strip;
	uint32_t port;
	uint32_t addrlen = net_getsockAddrIPAndPort(addr, strip, port);
	if (addrlen == 0)
	{
		return -1;
	}

	for (auto& it : m_allAwaitConnectSocket)
	{
		if (!it.invalid && it.socket && it.socket->getIp() == strip && it.socket->getPort() == port)
		{
			return 1;
		}
	}

	for (auto& it : m_allConnectSocket)
	{
		if (!it.invalid && it.socket->getIp() == strip && it.socket->getPort() == port)
		{
			return 1;
		}
	}
	return 0;
}

void KCPSocketManager::on_socket_connect(Socket* socket, int32_t status)
{
	if (!m_stop && status == 1)
	{
		socket->setConnectCallback(nullptr);
		connect((KCPSocket*)socket);
	}
	else
	{
		removeAwaitConnectSocket((KCPSocket*)socket);
	}
}

void KCPSocketManager::on_socket_close(Socket* socket)
{
	removeAwaitConnectSocket((KCPSocket*)socket);
}

void KCPSocketManager::connect(KCPSocket* socket)
{
	for (auto& it : m_allConnectSocket)
	{
		if (it.socket == socket)
		{
			return;
		}
	}

	SMData data;
	data.invalid = false;
	data.socket = socket;
	m_allConnectSocket.push_back(data);

	m_owner->m_newConnectionCall(socket);

	for (auto& it : m_allAwaitConnectSocket)
	{
		if (it.socket == socket)
		{
			it.invalid = true;
			it.socket = NULL;
			m_isAwaitConnectArrDirty = true;
			break;
		}
	}
}

void KCPSocketManager::removeAwaitConnectSocket(KCPSocket* socket)
{
	for (auto& it : m_allAwaitConnectSocket)
	{
		if (it.socket == socket)
		{
			it.invalid = true;
			m_isAwaitConnectArrDirty = true;
			break;
		}
	}
}

void KCPSocketManager::clearInvalid()
{
	if (m_isAwaitConnectArrDirty)
	{
		auto it = m_allAwaitConnectSocket.begin();
		for (; it != m_allAwaitConnectSocket.end(); )
		{
			if (it->invalid)
			{
				if (it->socket != NULL)
				{
					it->socket->~KCPSocket();
					fc_free(it->socket);
				}
				it = m_allAwaitConnectSocket.erase(it);
			}
			else
			{
				it++;
			}
		}

		m_isAwaitConnectArrDirty = false;
	}

	if (m_isConnectArrDirty)
	{
		auto it = m_allConnectSocket.begin();
		for (; it != m_allConnectSocket.end(); )
		{
			if (it->invalid)
			{
				it = m_allConnectSocket.erase(it);
			}
			else
			{
				it++;
			}
		}
		m_isConnectArrDirty = false;
	}
}

void KCPSocketManager::idleRun()
{
	clearInvalid();

	m_lastUpdateClock = iclock();
	
	if (m_owner)
	{
		m_owner->socketUpdate(m_lastUpdateClock);
	}

	for (auto& it : m_allAwaitConnectSocket)
	{
		it.socket->socketUpdate(m_lastUpdateClock);
	}

	for (auto& it : m_allConnectSocket)
	{
		it.socket->socketUpdate(m_lastUpdateClock);
	}
}

bool KCPSocketManager::isAccept(const struct sockaddr* addr)
{
	std::string strip;
	uint32_t port;
	uint32_t addrlen = net_getsockAddrIPAndPort(addr, strip, port);
	if (addrlen == 0)
	{
		return false;
	}
	
	bool recessFinish = false;
	auto it_recess = m_recessTimeMap.find(strip);
	if (it_recess != m_recessTimeMap.end())
	{
		// 该IP冷却时间未到
		if (it_recess->second > m_lastUpdateClock)
		{
			return false;
		}
		else
		{
			recessFinish = true;
			m_recessTimeMap.erase(it_recess);
		}
	}

	if (recessFinish)
	{
		for (auto& it : m_allAwaitConnectSocket)
		{
			if (!it.invalid && it.socket && it.socket->getIp() == strip)
			{
				it.socket->disconnect();
			}
		}
	}
	else
	{
		uint32_t awaitCount = 0;
		for (auto& it : m_allAwaitConnectSocket)
		{
			if (!it.invalid && it.socket && it.socket->getIp() == strip)
			{
				awaitCount++;
				// 该IP、端口正在连接
				if (it.socket->getPort() == port)
				{
					return false;
				}
			}
		}

		// 该IP等待连接数量过多，暂停accept
		if (awaitCount > 500)
		{
			// 休息10S
			m_recessTimeMap[strip] = m_lastUpdateClock + 10000;
			return false;
		}
	}

	// 该IP、端口已连接成功
	for (auto& it : m_allConnectSocket)
	{
		if (!it.invalid && it.socket->getIp() == strip && it.socket->getPort() == port)
		{
			return false;
		}
	}
	return true;
}

NS_NET_UV_END