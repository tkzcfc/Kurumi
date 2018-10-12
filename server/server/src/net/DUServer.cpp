#include "DUServer.h"

DUServer::DUServer()
{
	m_server = new TCPServer();

	m_server->setStartCallback(std::bind(&DUServer::onServerStartCall, this, std::placeholders::_1, std::placeholders::_2));
	m_server->setCloseCallback(std::bind(&DUServer::onServerCloseCall, this, std::placeholders::_1));
	m_server->setNewConnectCallback(std::bind(&DUServer::onServerNewConnectCall, this, std::placeholders::_1, std::placeholders::_2));
	m_server->setRecvCallback(std::bind(&DUServer::onServerRecvCall, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_server->setDisconnectCallback(std::bind(&DUServer::onServerDisconnectCall, this, std::placeholders::_1, std::placeholders::_2));

	DUScheduler::getInstance()->schedule(scheduler_selector(DUServer::update), this, 1 / 40.0f);
}

DUServer::~DUServer()
{
	delete m_server;
}

void DUServer::startServer(const char* ip, unsigned int port, bool isIPV6)
{
	m_server->startServer(ip, port, isIPV6);
}

bool DUServer::stopServer()
{
	return m_server->stopServer();
}

void DUServer::send(Session* session, char* data, unsigned int len)
{
	m_server->send(session, data, len);
}

void DUServer::disconnect(Session* session)
{
	m_server->disconnect(session);
}

bool DUServer::isCloseFinish()
{
	return m_server->isCloseFinish();
}

void DUServer::update(float d)
{
	m_server->updateFrame();

	/*m_server->getAllThreadMsg(&m_msgs);
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
					if (msg.tag == TCPMsgTag::MT_DEFAULT)
					{
						m_luaHandle.ppush();
						m_luaHandle.pusharg("recv");
						m_luaHandle.pushusertype(msg.pSocket, "TCPSocket");
						m_luaHandle.pusharg((const char*)msg.data);
						m_luaHandle.pcall();
					}
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
	}*/
}

void DUServer::onServerStartCall(Server* svr, bool success)
{
	auto handle = getLuaHandle("onServerStartCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(svr, "Server");
		handle->pusharg(success);
		handle->pcall();
	}
}

void DUServer::onServerCloseCall(Server* svr)
{
	auto handle = getLuaHandle("onServerCloseCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(svr, "Server");
		handle->pcall();
	}
}

void DUServer::onServerNewConnectCall(Server* svr, Session* session)
{
	auto handle = getLuaHandle("onServerNewConnectCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(svr, "Server");
		handle->pushusertype(session, "Session");
		handle->pcall();
	}
}

void DUServer::onServerRecvCall(Server* svr, Session* session, char* data, unsigned int len)
{
	auto handle = getLuaHandle("onServerRecvCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(svr, "Server");
		handle->pushusertype(session, "Session");
		handle->pushlstring(data, len);
		handle->pusharg(len);
		handle->pcall();
	}
}

void DUServer::onServerDisconnectCall(Server* svr, Session* session)
{
	auto handle = getLuaHandle("onServerDisconnectCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(svr, "Server");
		handle->pushusertype(session, "Session");
		handle->pcall();
	}
}

