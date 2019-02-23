#include "DUServer.h"

DUServer::DUServer()
{
	m_server = new net_uv::TCPServer();

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

bool DUServer::startServer(const char* ip, unsigned int port, bool isIPV6)
{
	return m_server->startServer(ip, port, isIPV6);
}

bool DUServer::stopServer()
{
	return m_server->stopServer();
}

void DUServer::send(net_uv::Session* session, char* data, unsigned int len)
{
	m_server->send(session->getSessionID(), data, len);
}

void DUServer::disconnect(net_uv::Session* session)
{
	m_server->disconnect(session->getSessionID());
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

void DUServer::onServerCloseCall(net_uv::Server* svr)
{
	auto handle = getLuaHandle("onServerCloseCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(svr, "net_uv::Server");
		handle->pcall();
	}
}

void DUServer::onServerNewConnectCall(net_uv::Server* svr, net_uv::Session* session)
{
	auto handle = getLuaHandle("onServerNewConnectCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(svr, "net_uv::Server");
		handle->pushusertype(session, "net_uv::Session");
		handle->pcall();
	}
}

void DUServer::onServerRecvCall(net_uv::Server* svr, net_uv::Session* session, char* data, unsigned int len)
{
	auto handle = getLuaHandle("onServerRecvCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(svr, "net_uv::Server");
		handle->pushusertype(session, "net_uv::Session");
		handle->pushlstring(data, len);
		handle->pusharg(len);
		handle->pcall();
	}
}

void DUServer::onServerDisconnectCall(net_uv::Server* svr, net_uv::Session* session)
{
	auto handle = getLuaHandle("onServerDisconnectCall");
	if (handle && handle->isvalid())
	{
		handle->ppush();
		handle->pushusertype(svr, "net_uv::Server");
		handle->pushusertype(session, "net_uv::Session");
		handle->pcall();
	}
}

