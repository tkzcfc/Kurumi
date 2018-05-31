#include "DUServer.h"

DUServer::DUServer()
{
	m_luaHandleInvalid = false;
	m_server = new TCPServer();

	DUScheduler::getInstance()->schedule(scheduler_selector(DUServer::update), this, 1 / 40.0f);
}

DUServer::~DUServer()
{
	delete m_server;
}


bool DUServer::startServer(const char* ip, int port)
{
	return m_server->startServer(ip, port);
}

bool DUServer::closeServer()
{
	return m_server->closeServer();
}

bool DUServer::isCloseFinish()
{
	return m_server->isCloseFinish();
}

void DUServer::setCallFunc(const LuaFunction& handle)
{
	m_luaHandle = handle;
	m_luaHandleInvalid = true;
}

void DUServer::setCallFunc(const netServerCallFunc& func)
{
	m_callFunc = func;
}

void DUServer::update(float d)
{
	m_server->getAllThreadMsg(&m_msgs);
	if (!m_msgs.empty())
	{
		if (m_callFunc)
		{
			for (auto& it : m_msgs)
			{
				m_callFunc(it);
			}
		}
		if (m_luaHandleInvalid)
		{
			for (auto& msg : m_msgs)
			{
				switch (msg.msgType)
				{
				case CONNECT:
				{
					m_luaHandle.ppush();
					m_luaHandle.pusharg("connect");
					m_luaHandle.pushusertype(msg.pSocket, "TCPSocket");
					m_luaHandle.pcall();

				}break;
				case DIS_CONNECT:
				{
					m_luaHandle.ppush();
					m_luaHandle.pusharg("disconnect");
					m_luaHandle.pushusertype(msg.pSocket, "TCPSocket");
					m_luaHandle.pcall();
				}break;
				case EXIT_LOOP:
				{
					m_luaHandle("loopexit");
				}break;
				case RECV_DATA:
				{
					m_luaHandle.ppush();
					m_luaHandle.pusharg("recv");
					m_luaHandle.pushusertype(msg.pSocket, "TCPSocket");
					m_luaHandle.pusharg((const char*)msg.data);
					m_luaHandle.pcall();
				}break;
				default:
					break;
				}
			}
		}

		for (auto& it : m_msgs)
		{
			fc_free(it.data);
		}
	}
}

