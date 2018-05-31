#include "TCPServer.h"
#include <list>
#include <map>

#define TCP_SOCKET_DATD_RELEASE_COUNT 120

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TCPServer::socket_callback(socket_call_type type, TCPSocket* s, void* data, void* userdata)
{
	TCPServer* server = (TCPServer*)userdata;

	switch (type)
	{
		case connect_new:
		{
			auto ns = ((TCPSocket*)data);
			ns->setCallback(socket_callback, server);

			server->addNewSocket(ns);
			server->pushThreadMsg(ThreadMsgType::CONNECT, ns, NULL, NULL);
		}
		break;

		case connect_close:
		{
			if (s == server->m_server)
			{
				uv_async_send(server->m_eixtAsync);
				return;
			}
			server->pushThreadMsg(ThreadMsgType::DIS_CONNECT, s, NULL, NULL);
			server->removeSocket(s);
		}
		break;

		default:
			break;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

TCPServer::TCPServer()
	: m_start(false)
	, m_port(0)
	, m_server(NULL)
	, m_thread(NULL)
{
	m_serverStage = ServerStage::exit;

	uv_mutex_init(&m_msgMutex);

	m_idle = (uv_idle_t*)fc_malloc(sizeof(uv_idle_t));
	m_eixtAsync = (uv_async_t*)fc_malloc(sizeof(uv_async_t));
	m_exitTimer = (uv_timer_t*)fc_malloc(sizeof(uv_timer_t));

	UV_LOG("alloc server");
}

TCPServer::~TCPServer()
{
	closeServer();

	if (m_thread)
	{
		uv_thread_join(m_thread);
		fc_free(m_thread);
		m_thread = NULL;
	}

	fc_free(m_eixtAsync);
	fc_free(m_idle);
	fc_free(m_exitTimer);

	uv_mutex_destroy(&m_msgMutex);
	UV_LOG("destroy server");
}

bool TCPServer::startServer(const char* ip, int port)
{
	if (m_server) return false;

	m_ip = ip;
	m_port = port;

	int r = uv_loop_init(&m_loop);
	CHECK_UV_ERROR(r);

	r = uv_idle_init(&m_loop, m_idle);
	m_idle->data = this;
	CHECK_UV_ERROR(r);

	uv_idle_start(m_idle, uv_on_idle_run);
	
	m_eixtAsync->data = this;
	uv_async_init(&m_loop, m_eixtAsync, uv_exit_async_callback);

	m_exitTimer->data = this;
	uv_timer_init(&m_loop, m_exitTimer);

#if OPEN_TCP_UV_DEBUG == 1
	m_server = (TCPSocket*)fc_malloc(sizeof(TCPSocket));
	new (m_server) TCPSocket(&m_loop);
#else
	m_server = new TCPSocket(&m_loop);
#endif

	m_server->setCallback(socket_callback, this);
	m_server->listen(ip, port);	

	m_thread = (uv_thread_t*)fc_malloc(sizeof(uv_thread_t));
	r = uv_thread_create(m_thread, thread_run, this);
	CHECK_UV_ERROR(r);
	
	m_start = true;
	m_serverStage = ServerStage::listen;

	UV_LOG("satrt...");
	return true;
}

bool TCPServer::closeServer()
{
	if (!m_start)
		return false;

	m_start = false;

	m_server->disconnect();

	uv_async_send(m_eixtAsync);

	m_serverStage = ServerStage::shall_disconnect;

	UV_LOG("close...");
	return true;
}

bool TCPServer::isCloseFinish()
{
	return (m_serverStage == ServerStage::exit);
}

bool TCPServer::getThreadMsg(ThreadMsg_S* msg)
{
	uv_mutex_lock(&m_msgMutex);
	if (m_msgQue.empty())
	{
		uv_mutex_unlock(&m_msgMutex);
		return false;
	}

	auto curMsg = m_msgQue.front();
	m_msgQue.pop();
	uv_mutex_unlock(&m_msgMutex);

	msg->msgType = curMsg.msgType;
	msg->dataLen = curMsg.dataLen;
	msg->data = curMsg.data;
	msg->pSocket = curMsg.pSocket;

	return true;
}

bool TCPServer::getAllThreadMsg(std::vector<ThreadMsg_S>* v)
{
	v->clear();

	if (uv_mutex_trylock(&m_msgMutex) != 0)
	{
		return false;
	}

	if (m_msgQue.empty())
	{
		uv_mutex_unlock(&m_msgMutex);
		return false;
	}

	v->reserve(m_msgQue.size());

	while (!m_msgQue.empty())
	{
		v->push_back(m_msgQue.front());
		m_msgQue.pop();
	}
	uv_mutex_unlock(&m_msgMutex);

	return true;
}

void TCPServer::pushThreadMsg(ThreadMsgType type, void* psocket, void* data, int len)
{
	ThreadMsg_S msg;
	msg.msgType = type;
	msg.data = data;
	msg.dataLen = len;
	msg.pSocket = psocket;

	uv_mutex_lock(&m_msgMutex);
	m_msgQue.push(msg);
	uv_mutex_unlock(&m_msgMutex);
}

void TCPServer::addNewSocket(TCPSocket* s)
{
	if (s == NULL)
	{
		assert(0);
		return;
	}

	UV_LOG("insert [%p]:[%p] ip = [%s]", s, s->getTcp(), s->getIp().c_str());

	bool find = false;
	for (auto it = allSocket.begin(); it != allSocket.end(); ++it)
	{
		if (it->s == s)
		{
			find = true;
			break;
		}
	}

	if (!find)
	{
		tcpSocketData data;
		data.s = s;
		data.isInvalid = false;
		data.releaseCount = TCP_SOCKET_DATD_RELEASE_COUNT;
		allSocket.push_back(data);
	}
}

void TCPServer::removeSocket(TCPSocket* s)
{
	if (s == NULL)
	{
		return;
	}

	for (auto it = allSocket.begin(); it != allSocket.end(); ++it)
	{
		if (it->s == s)
		{
			UV_LOG("delete [%p]: ip = [%s]", s, s->getIp().c_str());
			it->isInvalid = true;
			return;
		}
	}
}

void TCPServer::idleRun()
{
	std::list<blockdata> list;

	auto it = allSocket.begin();
	for (; it != allSocket.end(); )
	{
		if (!it->isInvalid)
		{
			list.clear();
			(it->s)->getAllRecvData(&list);

			if (!list.empty())
			{
				for (auto & d : list)
				{
					pushThreadMsg(ThreadMsgType::RECV_DATA, it->s, d.data, d.len);
				}
			}
			it++;
		}
		else
		{
			it->releaseCount--;
			if (it->releaseCount < 0)
			{
#if OPEN_TCP_UV_DEBUG == 1 
				it->s->~TCPSocket();
				fc_free(it->s);
#else
				delete it->s;
#endif
				it = allSocket.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	ThreadSleep(2);
}


void TCPServer::exitStart()
{
	auto it = allSocket.begin();
	for (; it != allSocket.end(); ++it)
	{
		if (!it->isInvalid)
		{
			it->s->disconnect();
		}
	}

	m_server->disconnect();

	uv_timer_start(m_exitTimer, uv_exit_timer_callback, 2000, 1000);
}

void TCPServer::exitStep()
{
	switch (m_serverStage)
	{
	case ServerStage::shall_disconnect:
	{
		if (allSocket.size() <= 0)
		{
			UV_LOG("disconnect finish");
			m_serverStage = ServerStage::shall_deleteSocket;
		}
	}break;

	case ServerStage::shall_deleteSocket:
	{
		if (m_server)
		{
#if OPEN_TCP_UV_DEBUG == 1 
			m_server->~TCPSocket();
			fc_free(m_server);
#else
			delete m_server;
#endif
			m_server = NULL;
		}
		UV_LOG("delete server socekt finish");
		m_serverStage = ServerStage::shall_exit;
	}break;

	case ServerStage::shall_exit:
	{
		UV_LOG("loop stop finish");
		uv_stop(&m_loop);
		m_serverStage = ServerStage::exit;
	}break;

	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TCPServer::thread_run(void* data)
{
	TCPServer* pServer = (TCPServer*)data;

	uv_run(&pServer->m_loop, UV_RUN_DEFAULT);

	uv_loop_close(&pServer->m_loop);

	UV_LOG("exit loop");
	pServer->pushThreadMsg(ThreadMsgType::EXIT_LOOP, NULL);
}

void TCPServer::uv_on_idle_run(uv_idle_t* handle)
{
	TCPServer* s = (TCPServer*)handle->data;
	s->idleRun();
}

void TCPServer::uv_exit_async_callback(uv_async_t* handle)
{
	TCPServer* s = (TCPServer*)handle->data;
	s->exitStart();
}

void TCPServer::uv_exit_timer_callback(uv_timer_t* handle)
{
	TCPServer* s = (TCPServer*)handle->data;
	s->exitStep();
}
