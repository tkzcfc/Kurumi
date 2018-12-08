#include "P2PTurn.h"

NS_NET_UV_BEGIN

P2PTurn::P2PTurn()
	: m_state(TurnState::STOP)
{
	memset(&m_loop, 0, sizeof(m_loop));
	memset(&m_idle, 0, sizeof(m_idle));

	m_pipe.setRecvJsonCallback(std::bind(&P2PTurn::onPipeRecvJsonCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_pipe.setRecvKcpCallback(std::bind(&P2PTurn::onPipeRecvKcpCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_pipe.setNewSessionCallback(std::bind(&P2PTurn::onPipeNewSessionCallback, this, std::placeholders::_1));
	m_pipe.setNewKcpCreateCallback(std::bind(&P2PTurn::onPipeNewKcpCreateCallback, this, std::placeholders::_1));
	m_pipe.setRemoveSessionCallback(std::bind(&P2PTurn::onPipeRemoveSessionCallback, this, std::placeholders::_1));
}

P2PTurn::~P2PTurn()
{
	stop();
	this->join();
}

bool P2PTurn::start(const char* ip, uint32_t port)
{
	if (m_state != TurnState::STOP)
	{
		return false;
	}
	
	uv_loop_init(&m_loop);

	if (m_pipe.bind(ip, port, &m_loop) == false)
	{
		uv_run(&m_loop, UV_RUN_DEFAULT);
		uv_loop_close(&m_loop);
		return false;
	}
	m_state = TurnState::START;

	startThread();

	return true;
}

void P2PTurn::stop()
{
	m_state = TurnState::WILL_STOP;
}

/// Runnable
void P2PTurn::run()
{
	uv_idle_init(&m_loop, &m_idle);
	m_idle.data = this;
	uv_idle_start(&m_idle, P2PTurn::uv_on_idle_run);
	
	uv_run(&m_loop, UV_RUN_DEFAULT);
	uv_loop_close(&m_loop);

	m_state = TurnState::STOP;
}

void P2PTurn::onIdleRun()
{
	m_pipe.update(iclock());
	if (m_state == TurnState::WILL_STOP)
	{
		m_pipe.close();
		uv_idle_stop(&m_idle);
	}
	ThreadSleep(1);
}

void P2PTurn::onPipeRecvJsonCallback(P2PMessageID msgID, rapidjson::Document& document, uint64_t key, const struct sockaddr* addr)
{
	switch (msgID)
	{
	case net_uv::P2P_MSG_ID_C2T_CLIENT_LOGIN:
	{
		rapidjson::StringBuffer s;
		rapidjson::Writer<rapidjson::StringBuffer> writer(s);

		writer.StartObject();
		writer.Key("key");
		writer.Uint64(key);
		writer.EndObject();

		m_pipe.send(P2PMessageID::P2P_MSG_ID_T2C_CLIENT_LOGIN_RESULT, s.GetString(), s.GetLength(), addr);
	}
		break;
	case net_uv::P2P_MSG_ID_C2T_WANT_TO_CONNECT:
	{
		if (document.HasMember("toKey"))
		{
			rapidjson::Value& key_value = document["toKey"];
			if (key_value.IsUint64())
			{
				rapidjson::StringBuffer s;
				rapidjson::Writer<rapidjson::StringBuffer> writer(s);

				writer.StartObject();
				writer.Key("key");
				writer.Uint64(key);
				writer.EndObject();

				AddrInfo info;
				info.key = key_value.GetUint64();

				m_pipe.send(P2PMessageID::P2P_MSG_ID_T2C_START_BURROW, s.GetString(), s.GetLength(), info.ip, info.port);
			}
		}
	}
		break;
	default:
		break;
	}
}

void P2PTurn::onPipeRecvKcpCallback(char* data, uint32_t len, uint64_t key, const struct sockaddr* addr)
{}

void P2PTurn::onPipeNewSessionCallback(uint64_t key)
{
	NET_UV_LOG(NET_UV_L_INFO,"%llu\t½øÈë", key);
}

void P2PTurn::onPipeNewKcpCreateCallback(uint64_t key)
{}

void P2PTurn::onPipeRemoveSessionCallback(uint64_t key)
{
	NET_UV_LOG(NET_UV_L_INFO, "%llu\tÀë¿ª\n", key);
}

void P2PTurn::uv_on_idle_run(uv_idle_t* handle)
{
	((P2PTurn*)handle->data)->onIdleRun();
}

NS_NET_UV_END
