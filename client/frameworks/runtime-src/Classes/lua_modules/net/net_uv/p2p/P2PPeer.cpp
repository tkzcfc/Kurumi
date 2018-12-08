#include "P2PPeer.h"

NS_NET_UV_BEGIN


enum P2POperationCMD
{
	/// input
	P2P_CONNECT_TO_PEER,
	P2P_CONNECT_TO_TURN,
	P2P_SEND_TO_PEER,
	P2P_DISCONNECT_TO_PEER,

	/// output
	P2P_START_FAIL,
	P2P_START_SUC,
	P2P_CONNECT_TURN_SUC,
	P2P_CONNECT_TURN_FAIL,
	P2P_DISCONNECT_TURN,
	P2P_CONNECT_PEER_SUC,
	P2P_CONNECT_PEER_TIMEOUT,
	P2P_DISCONNECT_PEER,
	P2P_RECV_KCP_DATA,
	P2P_NEWCONNECT,
	P2P_STOP,
};

P2PPeer::P2PPeer()
	: m_state(PeerState::STOP)
	, m_turnPort(0)
	, m_tryConnectTurnCount(0)
	, m_isConnectTurn(false)
	, m_isStopConnectToTurn(true)
	, m_startCallback(nullptr)
	, m_newConnectCallback(nullptr)
	, m_connectToPeerCallback(nullptr)
	, m_connectToTurnCallback(nullptr)
	, m_disConnectToPeerCallback(nullptr)
	, m_disConnectToTurnCallback(nullptr)
	, m_recvCallback(nullptr)
{
	memset(&m_loop, 0, sizeof(m_loop));
	memset(&m_idle, 0, sizeof(m_idle));
	memset(&m_timer, 0, sizeof(m_timer));

	m_pipe.setRecvJsonCallback(std::bind(&P2PPeer::onPipeRecvJsonCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_pipe.setRecvKcpCallback(std::bind(&P2PPeer::onPipeRecvKcpCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_pipe.setNewSessionCallback(std::bind(&P2PPeer::onPipeNewSessionCallback, this, std::placeholders::_1));
	m_pipe.setNewKcpCreateCallback(std::bind(&P2PPeer::onPipeNewKcpCreateCallback, this, std::placeholders::_1));
	m_pipe.setRemoveSessionCallback(std::bind(&P2PPeer::onPipeRemoveSessionCallback, this, std::placeholders::_1));
}

P2PPeer::~P2PPeer()
{
	stop();
	this->join();
}

bool P2PPeer::start(const char* ip, uint32_t port)
{
	if (m_state != PeerState::STOP)
	{
		return false;
	}

	assert(m_startCallback != nullptr);
	assert(m_newConnectCallback != nullptr);
	assert(m_connectToPeerCallback != nullptr);
	assert(m_connectToTurnCallback != nullptr);
	assert(m_disConnectToPeerCallback != nullptr);
	assert(m_disConnectToTurnCallback != nullptr);
	assert(m_recvCallback != nullptr);
	assert(m_closeCallback != nullptr);

	uv_loop_init(&m_loop);

	if (m_pipe.bind("0.0.0.0", 0, &m_loop) == false)
	{
		startFailureLogic();
		return false;
	}
	m_turnIP = ip;
	m_turnPort = port;
	m_state = PeerState::START;

	restartConnectTurn();

	startThread();
	return true;
}

void P2PPeer::stop()
{
	if (m_state != PeerState::START)
	{
		return;
	}
	m_state = PeerState::WILL_STOP;
}

void P2PPeer::restartConnectTurn()
{
	if (m_state != PeerState::START)
	{
		return;
	}
	pushInputOperation(0, P2POperationCMD::P2P_CONNECT_TO_TURN, NULL, 0);
}

bool P2PPeer::connectToPeer(uint64_t key)
{
	if (m_state != PeerState::START)
	{
		return false;
	}

	if (key == m_selfAddrInfo.key)
	{
		return false;
	}

	pushInputOperation(key, P2POperationCMD::P2P_CONNECT_TO_PEER, NULL, 0);
	return true;
}

void P2PPeer::updateFrame()
{
	if (m_outputLock.trylock() != 0)
	{
		return;
	}

	if (m_outputQue.empty())
	{
		m_outputLock.unlock();
		return;
	}

	while (!m_outputQue.empty())
	{
		m_outputQueCache.push(m_outputQue.front());
		m_outputQue.pop();
	}

	m_outputLock.unlock();
	bool isStopCMD = false;;

	while (!m_outputQueCache.empty())
	{
		auto& opData = m_outputQueCache.front();
		switch (opData.what)
		{
		case P2POperationCMD::P2P_START_FAIL:
		{
			m_startCallback(false);
		}break;
		case P2POperationCMD::P2P_START_SUC:
		{
			m_startCallback(true);
		}break;
		case P2POperationCMD::P2P_CONNECT_TURN_SUC:
		{
			m_connectToTurnCallback(true, m_selfAddrInfo.key);
		}break;
		case P2POperationCMD::P2P_CONNECT_TURN_FAIL:
		{
			m_connectToTurnCallback(false, 0);
		}break;
		case P2POperationCMD::P2P_DISCONNECT_TURN:
		{
			m_disConnectToTurnCallback();
		}break;
		case P2POperationCMD::P2P_CONNECT_PEER_SUC:
		{
			m_connectToPeerCallback(opData.key, true);
		}break;
		case P2POperationCMD::P2P_CONNECT_PEER_TIMEOUT:
		{
			m_connectToPeerCallback(opData.key, false);
		}break;
		case P2POperationCMD::P2P_DISCONNECT_PEER:
		{
			m_disConnectToPeerCallback(opData.key);
		}break;
		case P2POperationCMD::P2P_RECV_KCP_DATA:
		{
			m_recvCallback(opData.key, (char*)opData.data, opData.datalen);
			fc_free(opData.data);
		}break;
		case P2POperationCMD::P2P_NEWCONNECT:
		{
			m_newConnectCallback(opData.key);
		}break;
		case P2POperationCMD::P2P_STOP:
		{
			isStopCMD = true;
		}
		default:
			break;
		}

		m_outputQueCache.pop();
	}
	if (isStopCMD)
	{
		m_closeCallback();
	}
}

void P2PPeer::send(uint64_t key, char* data, uint32_t len)
{
	char* sendData = (char*)fc_malloc(len);
	memcpy(sendData, data, len);
	pushInputOperation(key, P2POperationCMD::P2P_SEND_TO_PEER, sendData, len);
}

void P2PPeer::disconnect(uint64_t key)
{
	pushInputOperation(key, P2POperationCMD::P2P_DISCONNECT_TO_PEER, NULL, 0);
}

/// Runnable
void P2PPeer::run()
{
	struct sockaddr* turnAddr = net_getsocketAddr(m_turnIP.c_str(), m_turnPort, NULL);
	// 域名解析失败或解析出来为IPV6
	if (turnAddr == NULL || turnAddr->sa_family != AF_INET)
	{
		startFailureLogic();
		pushOutputOperation(0, P2POperationCMD::P2P_START_FAIL, NULL, 0);
		return;
	}
	pushOutputOperation(0, P2POperationCMD::P2P_START_SUC, NULL, 0);

	struct sockaddr_in* addr4 = (struct sockaddr_in*)turnAddr;

	m_turnAddrInfo.ip = addr4->sin_addr.s_addr;
	m_turnAddrInfo.port = ntohs(addr4->sin_port);

	fc_free(turnAddr);

	uv_idle_init(&m_loop, &m_idle);
	m_idle.data = this;
	uv_idle_start(&m_idle, P2PPeer::uv_on_idle_run);

	uv_timer_init(&m_loop, &m_timer);
	m_timer.data = this;
	uv_timer_start(&m_timer, P2PPeer::uv_on_timer_run, 200, 200);

	uv_run(&m_loop, UV_RUN_DEFAULT);
	uv_loop_close(&m_loop);

	m_state = PeerState::STOP;
	clearData();

	pushOutputOperation(0, P2POperationCMD::P2P_STOP, NULL, 0);
}

void P2PPeer::onIdleRun()
{
	runInputOperation();

	m_pipe.update(iclock());

	if (m_state == PeerState::WILL_STOP)
	{
		m_pipe.close();
		uv_timer_stop(&m_timer);
		uv_idle_stop(&m_idle);
	}

	ThreadSleep(1);
}

void P2PPeer::onTimerRun()
{
	doConnectToTurn();

	if (m_burrowManager.empty() == false)
	{
		for (auto it = m_burrowManager.begin(); it != m_burrowManager.end(); )
		{
			// 打洞数据发送次数超过40次，则停止发送
			if (it->second.sendCount >= 40)
			{
				it = m_burrowManager.erase(it);
			}
			else
			{
				m_pipe.send(P2PMessageID::P2P_MSG_ID_C2C_HELLO, P2P_NULL_JSON, P2P_NULL_JSON_LEN, (const struct sockaddr*)&it->second.targetAddr);
				it->second.sendCount++;
				it++;
			}
		}
	}

	if (m_sessionManager.empty() == false)
	{
		for (auto it = m_sessionManager.begin(); it != m_sessionManager.end(); )
		{
			if (!it->second.isClient)
			{
				it++;
				continue;
			}

			if (it->second.state != SessionState::CONNECT)
			{
				// 连接超过最大尝试次数
				if (it->second.tryConnectCount > 10)
				{
					pushOutputOperation(it->first, P2POperationCMD::P2P_CONNECT_PEER_TIMEOUT, NULL, 0);
					it = m_sessionManager.erase(it);
					continue;
				}
				else
				{
					it->second.tryConnectCount++;
					if (m_isConnectTurn)
					{
						m_pipe.send(P2PMessageID::P2P_MSG_ID_C2T_WANT_TO_CONNECT, it->second.sendData.c_str(), it->second.sendData.length(), m_turnAddrInfo.ip, m_turnAddrInfo.port);
					}
				}
			}
			it++;
		}
	}
}

void P2PPeer::startFailureLogic()
{
	m_pipe.close();
	uv_run(&m_loop, UV_RUN_DEFAULT);
	uv_loop_close(&m_loop);
	m_state = PeerState::STOP;
}

void P2PPeer::onPipeRecvJsonCallback(P2PMessageID msgID, rapidjson::Document& document, uint64_t key, const struct sockaddr* addr)
{
	switch (msgID)
	{
	case P2PMessageID::P2P_MSG_ID_T2C_CLIENT_LOGIN_RESULT:
	{
		if (document.HasMember("key"))
		{
			rapidjson::Value& key_value = document["key"];
			if (key_value.IsUint64())
			{
				m_selfAddrInfo.key = key_value.GetUint64();
			}
			m_isConnectTurn = true;
			m_isStopConnectToTurn = true;
			pushOutputOperation(0, P2POperationCMD::P2P_CONNECT_TURN_SUC, NULL, 0);
		}
	}
	break;
	case P2PMessageID::P2P_MSG_ID_T2C_START_BURROW:
	{
		if (document.HasMember("key"))
		{
			rapidjson::Value& key_value = document["key"];
			if (key_value.IsUint64())
			{
				startBurrow(key_value.GetUint64());
			}
		}
	}
	case P2PMessageID::P2P_MSG_ID_C2C_HELLO:
	{
		auto it = m_sessionManager.find(key);
		if (it != m_sessionManager.end() && it->second.isClient && it->second.state != SessionState::CONNECT)
		{
			doSendCreateKcp(key);
		}
	}
	break;
	default:
		break;
	}
}

void P2PPeer::onPipeRecvKcpCallback(char* data, uint32_t len, uint64_t key, const struct sockaddr* addr)
{
	char* pData = (char*)fc_malloc(len);
	memcpy(pData, data, len);
	pushOutputOperation(key, P2POperationCMD::P2P_RECV_KCP_DATA, pData, len);
}

void P2PPeer::onPipeNewSessionCallback(uint64_t key)
{
	if (m_turnAddrInfo.key != key)
	{
		auto it = m_sessionManager.find(key);
		if (it == m_sessionManager.end())
		{
			SessionData sessionData;
			sessionData.state = DISCONNECT;
			sessionData.tryConnectCount = 0;
			sessionData.isClient = false;
			m_sessionManager[key] = sessionData;
			NET_UV_LOG(NET_UV_L_INFO, "new session %llu  new connect", key);
		}
	}
}

void P2PPeer::onPipeNewKcpCreateCallback(uint64_t key)
{
	if (m_turnAddrInfo.key != key)
	{
		auto it = m_sessionManager.find(key);
		if (it != m_sessionManager.end())
		{
			it->second.state = SessionState::CONNECT;
			if (it->second.isClient)
			{
				pushOutputOperation(key, P2POperationCMD::P2P_CONNECT_PEER_SUC, NULL, 0);
			}
			else
			{
				pushOutputOperation(key, P2POperationCMD::P2P_NEWCONNECT, NULL, 0);
			}
		}
	}
}

void P2PPeer::onPipeRemoveSessionCallback(uint64_t key)
{
	if (m_turnAddrInfo.key == key)
	{
		m_isConnectTurn = false;
		m_isStopConnectToTurn = true;
		pushOutputOperation(0, P2POperationCMD::P2P_DISCONNECT_TURN, NULL, 0);
	}
	else
	{
		pushOutputOperation(key, P2POperationCMD::P2P_DISCONNECT_PEER, NULL, 0);
	}

	auto it = m_sessionManager.find(key);
	if (it != m_sessionManager.end())
	{
		m_sessionManager.erase(it);
	}
}

void P2PPeer::pushInputOperation(uint64_t key, uint32_t what, void* data, uint32_t datalen)
{
	OperationData opData;
	opData.key = key;
	opData.what = what;
	opData.data = data;
	opData.datalen = datalen;

	m_inputLock.lock();
	m_inputQue.emplace(opData);
	m_inputLock.unlock();
}

void P2PPeer::pushOutputOperation(uint64_t key, uint32_t what, void* data, uint32_t datalen)
{
	OperationData opData;
	opData.key = key;
	opData.what = what;
	opData.data = data;
	opData.datalen = datalen;

	m_outputLock.lock();
	m_outputQue.emplace(opData);
	m_outputLock.unlock();
}

void P2PPeer::runInputOperation()
{
	if (m_inputLock.trylock() != 0)
	{
		return;
	}

	if (m_inputQue.empty())
	{
		m_inputLock.unlock();
		return;
	}

	while (!m_inputQue.empty())
	{
		m_inputQueCache.push(m_inputQue.front());
		m_inputQue.pop();
	}

	m_inputLock.unlock();

	while (!m_inputQueCache.empty())
	{
		auto& opData = m_inputQueCache.front();
		switch (opData.what)
		{
		case P2POperationCMD::P2P_CONNECT_TO_PEER:
		{
			rapidjson::StringBuffer s;
			rapidjson::Writer<rapidjson::StringBuffer> writer(s);

			writer.StartObject();
			writer.Key("toKey");
			writer.Uint64(opData.key);
			writer.EndObject();

			SessionData sessionData;
			sessionData.state = DISCONNECT;
			sessionData.tryConnectCount = 0;
			sessionData.isClient = true;
			sessionData.sendData = std::string(s.GetString(), s.GetLength());
			m_sessionManager[opData.key] = sessionData;

			NET_UV_LOG(NET_UV_L_INFO, "new session %llu  client", opData.key);

			startBurrow(opData.key);
		}break;
		case P2POperationCMD::P2P_CONNECT_TO_TURN:
		{
			m_tryConnectTurnCount = 0;
			if (m_isConnectTurn == false)
			{
				m_isStopConnectToTurn = false;
				doConnectToTurn();
			}
		}break;
		case P2POperationCMD::P2P_SEND_TO_PEER:
		{
			auto it = m_sessionManager.find(opData.key);
			if (it != m_sessionManager.end())
			{
				m_pipe.kcpSend((char*)opData.data, opData.datalen, opData.key);
			}
			fc_free(opData.data);
		}break;
		case P2POperationCMD::P2P_DISCONNECT_TO_PEER:
		{
			m_pipe.disconnect(opData.key);
		}break;
		default:
			break;
		}
		m_inputQueCache.pop();
	}
}

void P2PPeer::startBurrow(uint64_t toKey)
{
	auto it = m_burrowManager.find(toKey);
	if (it == m_burrowManager.end())
	{
		AddrInfo info;
		info.key = toKey;

		char * ipaddr = NULL;
		char addr[20];
		in_addr inaddr;
		inaddr.s_addr = info.ip;
		ipaddr = inet_ntoa(inaddr);
		strcpy(addr, ipaddr);

		BurrowData burrowData;
		burrowData.sendCount = 0;
		uv_ip4_addr(addr, info.port, &burrowData.targetAddr);

		m_burrowManager.insert(std::make_pair(toKey, burrowData));

		m_pipe.send(P2PMessageID::P2P_MSG_ID_C2C_HELLO, P2P_NULL_JSON, P2P_NULL_JSON_LEN, (const struct sockaddr*)&burrowData.targetAddr);
	}
	else
	{
		it->second.sendCount = 0;
	}
}

void P2PPeer::doConnectToTurn()
{
	if (m_isStopConnectToTurn)
		return;

	if (m_tryConnectTurnCount > 10)
	{
		m_isStopConnectToTurn = true;
		pushOutputOperation(0, P2POperationCMD::P2P_CONNECT_TURN_FAIL, NULL, 0);
		return;
	}

	m_tryConnectTurnCount++;
	m_pipe.send(P2PMessageID::P2P_MSG_ID_C2T_CLIENT_LOGIN, P2P_NULL_JSON, P2P_NULL_JSON_LEN, m_turnAddrInfo.ip, m_turnAddrInfo.port);
}

void P2PPeer::doSendCreateKcp(uint64_t toKey)
{
	AddrInfo info;
	info.key = toKey;
	m_pipe.send(P2PMessageID::P2P_MSG_ID_CREATE_KCP, P2P_NULL_JSON, P2P_NULL_JSON_LEN, info.ip, info.port);
}

void P2PPeer::clearData()
{
	m_inputLock.lock();

	while (!m_inputQue.empty())
	{
		if (m_inputQue.front().data != NULL)
		{
			fc_free(m_inputQue.front().data);
		}
		m_inputQue.pop();
	}

	m_inputLock.unlock();

	m_outputLock.lock();

	while (!m_outputQue.empty())
	{
		if (m_outputQue.front().data != NULL)
		{
			fc_free(m_outputQue.front().data);
		}
		m_outputQue.pop();
	}

	m_outputLock.unlock();
}

void P2PPeer::uv_on_idle_run(uv_idle_t* handle)
{
	((P2PPeer*)handle->data)->onIdleRun();
}

void P2PPeer::uv_on_timer_run(uv_timer_t* handle)
{
	((P2PPeer*)handle->data)->onTimerRun();
}

NS_NET_UV_END
