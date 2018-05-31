#include "TCPClient.h"
#include "TCPCommon.h"

//断线重连定时器检测间隔
#define CLIENT_TIMER_DELAY (0.2f)

//////////////////////////////////////////////////////////////////////////////////
struct tcp_client_callbackdata
{
	TCPClient* c;
	unsigned int key;
};

void TCPClient::tcp_client_socket_callback(socket_call_type type, TCPSocket* s, void* data, void* userdata)
{
	auto calldata = (tcp_client_callbackdata*)userdata;
	
	switch (type)
	{
	case connect_suc:
		calldata->c->socketIsConnect(calldata->key, CONNECTSTATE::CONNECT);
		calldata->c->pushThreadMsg(ThreadMsgType::CONNECT, calldata->key);
		break;
	case connect_fail:
		calldata->c->socketIsConnect(calldata->key, CONNECTSTATE::DISCONNECT);
		calldata->c->pushThreadMsg(ThreadMsgType::CONNECT_FAIL, calldata->key);
		break;
	case connect_ing:
		calldata->c->socketIsConnect(calldata->key, CONNECTSTATE::CONNECTING);
		calldata->c->pushThreadMsg(ThreadMsgType::CONNECT_ING, calldata->key);
		break;
	case connect_close:
		calldata->c->socketIsConnect(calldata->key, CONNECTSTATE::DISCONNECT);
		calldata->c->pushThreadMsg(ThreadMsgType::DIS_CONNECT, calldata->key);
		break;
	case connect_timeout:
		calldata->c->socketIsConnect(calldata->key, CONNECTSTATE::DISCONNECT);
		calldata->c->pushThreadMsg(ThreadMsgType::CONNECT_TIMEOUT, calldata->key);
		break;
	default:
		break;
	}
}
//////////////////////////////////////////////////////////////////////////////////
TCPClient::TCPClient()
	: m_reconnect(false)
	, m_totalTime(5.0f)
	, m_enableNoDelay(true)
	, m_enableKeepAlive(true)
	, m_keepAliveDelay(10)
{
	uv_loop_init(&m_loop);

	uv_mutex_init(&m_socketMutex);
	uv_mutex_init(&m_msgMutex);

	m_clientStage = clientStage::start;

	m_exitAsync = (uv_async_t*)fc_malloc(sizeof(uv_async_t));
	uv_async_init(&m_loop, m_exitAsync, uv_exit_async_callback);
	m_exitAsync->data = this;

	uv_idle_init(&m_loop, &m_idle);
	m_idle.data = this;
	uv_idle_start(&m_idle, uv_on_idle_run);

	uv_timer_init(&m_loop, &m_timer);
	m_timer.data = this;
	uv_timer_start(&m_timer, uv_timer_run, (uint64_t)(CLIENT_TIMER_DELAY * 1000), (uint64_t)(CLIENT_TIMER_DELAY * 1000));

	uv_thread_create(&m_thread, onThreadRun, this);
}

TCPClient::~TCPClient()
{
	if (m_exitAsync)
	{
		uv_async_send(m_exitAsync);
		m_exitAsync = NULL;
	}

	uv_thread_join(&m_thread);

	for (auto & it : m_allSocketMap)
	{
		fc_free(it.second->s->getCallbackUserdata());
#if OPEN_TCP_UV_DEBUG == 1 
		it.second->s->~TCPSocket();
		fc_free(it.second->s);
#else
		delete it.second->s;
#endif
		fc_free(it.second);
	}

	m_allSocketMap.clear();

	uv_mutex_destroy(&m_socketMutex);
	uv_mutex_destroy(&m_msgMutex);
}


bool TCPClient::connect(const char* ip, int port, unsigned int key, unsigned int timeout)
{
	if (m_clientStage != clientStage::start)
		return false;

	assert(ip != NULL);

	uv_mutex_lock(&m_socketMutex);

	auto it = m_allSocketMap.find(key);
	if (it != m_allSocketMap.end())
	{
		//对比端口和IP是否一致
		if (strcmp(ip, it->second->ip) != 0 && port != it->second->port)
		{
			uv_mutex_unlock(&m_socketMutex);
			assert(0);
			return false;
		}

		if (it->second->connectState != CONNECTSTATE::CONNECT)
		{
			it->second->connectState = CONNECTSTATE::CONNECTING;
			it->second->s->connect(ip, port, timeout);
		}

		uv_mutex_unlock(&m_socketMutex);
		return true;
	}
	else
	{
		uv_mutex_unlock(&m_socketMutex);

		tcp_client_callbackdata* calldata = (tcp_client_callbackdata*)fc_malloc(sizeof(tcp_client_callbackdata));
		calldata->c = this;
		calldata->key = key;

#if OPEN_TCP_UV_DEBUG == 1
		TCPSocket* s = (TCPSocket*)fc_malloc(sizeof(TCPSocket));
		new (s) TCPSocket(&m_loop);
#else
		TCPSocket* s = new TCPSocket(&m_loop);
#endif
		s->setCallback(tcp_client_socket_callback, calldata);
		s->connect(ip, port, timeout);

		clientsocketdata* cs = (clientsocketdata*)fc_malloc(sizeof(clientsocketdata));
		strcpy(cs->ip, ip);
		cs->port = port;
		cs->s = s;
		cs->curtime = 0;
		cs->reconnect = m_reconnect;
		cs->totaltime = m_totalTime;
		cs->connectState = CONNECTSTATE::CONNECTING;

		uv_mutex_lock(&m_socketMutex);
		m_allSocketMap.insert(std::make_pair(key, cs));
		uv_mutex_unlock(&m_socketMutex);
	}
	return true;
}

void TCPClient::disconnect(unsigned int key)
{
	if (m_clientStage != clientStage::start)
		return;
	uv_mutex_lock(&m_socketMutex);
	auto it = m_allSocketMap.find(key);
	if (it == m_allSocketMap.end())
	{
		uv_mutex_unlock(&m_socketMutex);
		return;
	}
	if (it->second->connectState == CONNECTSTATE::CONNECT)
	{
		it->second->connectState = CONNECTSTATE::DISCONNECTING;
	}
	it->second->s->disconnect();
	uv_mutex_unlock(&m_socketMutex);
}

void TCPClient::closeClient()
{
	if (m_clientStage != clientStage::start)
		return;
	//关闭自动连接
	setAutoReconnect(false);
	//断开所有
	uv_mutex_lock(&m_socketMutex);
	for (auto& it : m_allSocketMap)
	{
		if (it.second->connectState == CONNECTSTATE::CONNECT)
		{
			it.second->connectState = CONNECTSTATE::DISCONNECTING;
		}
		it.second->s->disconnect();
	}
	uv_mutex_unlock(&m_socketMutex);

	if (m_exitAsync)
	{
		uv_async_send(m_exitAsync);
		m_exitAsync = NULL;
	}
	else
	{
		assert(0);
	}

	m_clientStage = clientStage::shall_deleteSocket;
}

bool TCPClient::isCloseFinish()
{
	return (m_clientStage == clientStage::exit);
}

bool TCPClient::send(unsigned int key, char* data, unsigned int len)
{
	if (m_clientStage != clientStage::start)
		return false;

	if (data == 0 || len <= 0)
		return false;

	uv_mutex_lock(&m_socketMutex);

	auto it = m_allSocketMap.find(key);
	if (it == m_allSocketMap.end())
	{
		uv_mutex_unlock(&m_socketMutex);
		return false;
	}
	auto s = it->second;

	uv_mutex_unlock(&m_socketMutex);

	if(s->connectState == CONNECTSTATE::CONNECT)
		return s->s->send(data, len);

	return false;
}

bool TCPClient::setSocketNoDelay(bool enable)
{
	if (m_clientStage != clientStage::start)
		return false;

	m_enableNoDelay = enable;

	uv_mutex_lock(&m_socketMutex);

	for (auto& it : m_allSocketMap)
	{
		if(it.second->connectState == CONNECTSTATE::CONNECT)
			it.second->s->setNoDelay(enable);
	}

	uv_mutex_unlock(&m_socketMutex);

	return true;
}


bool TCPClient::setSocketKeepAlive(int enable, unsigned int delay)
{
	if (m_clientStage != clientStage::start)
		return false;

	m_enableKeepAlive = enable;
	m_keepAliveDelay = delay;

	uv_mutex_lock(&m_socketMutex);

	for (auto& it : m_allSocketMap)
	{
		if (it.second->connectState == CONNECTSTATE::CONNECT)
			it.second->s->setKeepAlive(enable, delay);
	}

	uv_mutex_unlock(&m_socketMutex);

	return true;
}

void TCPClient::run()
{
	m_loop.data = NULL;

	uv_run(&m_loop, UV_RUN_DEFAULT);

	uv_loop_close(&m_loop);

	m_clientStage = clientStage::exit;

	this->pushThreadMsg(ThreadMsgType::EXIT_LOOP, NULL);
}

bool TCPClient::getAllThreadMsg(std::vector<ThreadMsg_C>* v)
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

void TCPClient::pushThreadMsg(ThreadMsgType type, unsigned int key, void* data, int len)
{
	ThreadMsg_C msg;
	msg.msgType = type;
	msg.data = data;
	msg.dataLen = len;
	msg.key = key;

	uv_mutex_lock(&m_msgMutex);
	m_msgQue.push(msg);
	uv_mutex_unlock(&m_msgMutex);
}

TCPSocket* TCPClient::getSocketByKey(unsigned int key)
{
	if (m_clientStage != clientStage::start)
		return NULL;

	TCPSocket* s = NULL;

	uv_mutex_lock(&m_socketMutex);

	auto it = m_allSocketMap.find(key);
	if (it != m_allSocketMap.end())
	{
		s = it->second->s;
		uv_mutex_unlock(&m_socketMutex);
		return s;
	}

	uv_mutex_unlock(&m_socketMutex);
	return s;
}

TCPClient::CONNECTSTATE TCPClient::checkState(unsigned int key)
{
	TCPClient::CONNECTSTATE rs = TCPClient::CONNECTSTATE::DISCONNECT;

	uv_mutex_lock(&m_socketMutex);

	auto it = m_allSocketMap.find(key);
	if (it != m_allSocketMap.end())
	{
		rs = it->second->connectState;
	}

	uv_mutex_unlock(&m_socketMutex);

	return rs;
}

TCPClient::CONNECTSTATE TCPClient::checkState(const char* ip, unsigned int port)
{
	TCPClient::CONNECTSTATE rs = TCPClient::CONNECTSTATE::DISCONNECT;

	uv_mutex_lock(&m_socketMutex);
	
	auto it = m_allSocketMap.begin();
	for (; it != m_allSocketMap.end(); ++it)
	{
		if (strcmp(it->second->ip, ip) == 0 && it->second->port == port)
		{
			rs = it->second->connectState;
			uv_mutex_unlock(&m_socketMutex);
			return rs;
		}
	}

	uv_mutex_unlock(&m_socketMutex);
	return rs;
}

void TCPClient::socketIsConnect(unsigned int key, CONNECTSTATE state)
{
	uv_mutex_lock(&m_socketMutex);

	auto it = m_allSocketMap.find(key);
	if (it != m_allSocketMap.end())
	{
		it->second->connectState = state;

		if (state == CONNECTSTATE::CONNECT)
		{
			it->second->s->setNoDelay(m_enableNoDelay);
			it->second->s->setKeepAlive(m_enableKeepAlive, m_keepAliveDelay);
		}
	}

	uv_mutex_unlock(&m_socketMutex);
}

TCPClient::clientsocketdata* TCPClient::getClientSocketDataByKey(unsigned int key)
{
	TCPClient::clientsocketdata* r = NULL;

	uv_mutex_lock(&m_socketMutex);

	auto it = m_allSocketMap.find(key);
	if (it != m_allSocketMap.end())
	{
		r = it->second;
	}

	uv_mutex_unlock(&m_socketMutex);
	return r;
}

void TCPClient::setAutoReconnect(bool isAuto)
{
	if (m_clientStage != clientStage::start)
		return;

	m_reconnect = isAuto;

	uv_mutex_lock(&m_socketMutex);

	auto it = m_allSocketMap.begin();
	for (; it != m_allSocketMap.end(); ++it)
	{
		it->second->reconnect = isAuto;
	}

	uv_mutex_unlock(&m_socketMutex);
}

void TCPClient::setAutoReconnectTime(float time)
{
	if (m_clientStage != clientStage::start)
		return;

	m_totalTime = time;

	uv_mutex_lock(&m_socketMutex);

	auto it = m_allSocketMap.begin();
	for (; it != m_allSocketMap.end(); ++it)
	{
		it->second->totaltime = time;
	}

	uv_mutex_unlock(&m_socketMutex);
}

void TCPClient::setAutoReconnectByKey(unsigned int key, bool isAuto)
{
	if (m_clientStage != clientStage::start)
		return;

	auto s = getClientSocketDataByKey(key);
	if (s)
	{
		s->reconnect = isAuto;
	}
}

void TCPClient::setAutoReconnectTimeByKey(unsigned int key, float time)
{
	if (m_clientStage != clientStage::start)
		return;

	auto s = getClientSocketDataByKey(key);
	if (s)
	{
		s->totaltime = time;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TCPClient::onThreadRun(void* arg)
{
	TCPClient* pClient = (TCPClient*)(arg);

	pClient->run();
}

void TCPClient::uv_timer_run(uv_timer_t* handle)
{
	TCPClient* c = (TCPClient*)handle->data;

	if (c->m_clientStage == clientStage::start)
	{
		uv_mutex_lock(&c->m_socketMutex);

		clientsocketdata* data = NULL;

		for (auto& it : c->m_allSocketMap)
		{
			data = it.second;

			if (data->connectState == CONNECTSTATE::DISCONNECT && data->reconnect)
			{
				data->curtime = data->curtime + CLIENT_TIMER_DELAY;

				if (data->curtime >= data->totaltime)
				{
					data->curtime = 0.0f;
					data->connectState = CONNECTSTATE::CONNECTING;
					data->s->reconnect();
				}
			}
		}

		uv_mutex_unlock(&c->m_socketMutex);
	}
	else if(c->m_clientStage == clientStage::shall_deleteSocket)
	{
		//检测所有是否已经断开
		bool isConnect = false;

		uv_mutex_lock(&c->m_socketMutex);

		for (auto& it : c->m_allSocketMap)
		{
			if (it.second->connectState != CONNECTSTATE::DISCONNECT)
			{
				isConnect = true;
				if (it.second->connectState == CONNECTSTATE::CONNECT)
				{
					it.second->s->disconnect();
				}
			}
		}
		
		if (!isConnect)
		{
			for (auto & it : c->m_allSocketMap)
			{
				fc_free(it.second->s->getCallbackUserdata());
#if OPEN_TCP_UV_DEBUG == 1 
				it.second->s->~TCPSocket();
				fc_free(it.second->s);
#else
				delete it.second->s;
#endif
				fc_free(it.second);
			}

			c->m_allSocketMap.clear();
			c->m_clientStage = clientStage::shall_exit;
		}

		uv_mutex_unlock(&c->m_socketMutex);
	}
	else if (c->m_clientStage == clientStage::shall_exit)
	{
		uv_stop(&c->m_loop);
	}
}

void TCPClient::uv_exit_async_callback(uv_async_t* handle)
{
	auto c = (TCPClient*)handle->data;

	uv_timer_stop(&c->m_timer);

	uv_timer_start(&c->m_timer, uv_timer_run, 1000, 1000);

	uv_close((uv_handle_t*)handle, uv_exit_async_closehandle_callback);
}

void TCPClient::uv_exit_async_closehandle_callback(uv_handle_t* handle)
{
	fc_free(handle);
}

void TCPClient::uv_on_idle_run(uv_idle_t* handle)
{
	TCPClient* c = (TCPClient*)handle->data;

	std::list<blockdata> list;

	uv_mutex_lock(&c->m_socketMutex);

	auto it = c->m_allSocketMap.begin();
	for (; it != c->m_allSocketMap.end(); ++it)
	{
		list.clear();
		it->second->s->getAllRecvData(&list);

		if (!list.empty())
		{
			for (auto & d : list)
			{
				c->pushThreadMsg(ThreadMsgType::RECV_DATA, it->first, d.data, d.len);
			}
		}
	}

	uv_mutex_unlock(&c->m_socketMutex);
	ThreadSleep(2);
}
