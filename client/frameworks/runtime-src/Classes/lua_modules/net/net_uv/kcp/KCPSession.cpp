#include "KCPSession.h"
#include "KCPSocket.h"

NS_NET_UV_BEGIN

KCPSession* KCPSession::createSession(SessionManager* sessionManager, KCPSocket* socket)
{
	KCPSession* session = (KCPSession*)fc_malloc(sizeof(KCPSession));
	new(session)KCPSession(sessionManager);

	if (session == NULL)
	{
		socket->~KCPSocket();
		fc_free(socket);
		return NULL;
	}
	session->init(socket);
	return session;
}

KCPSession::KCPSession(SessionManager* sessionManager)
	: Session(sessionManager)
	, m_socket(NULL)
	, m_recvBuffer(NULL)
{
	assert(sessionManager != NULL);

#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
	m_resetHeartCount = -1;
	m_curHeartCount = -1;
	m_curHeartTime = 0;
	m_sendHeartMsg = NET_HEARTBEAT_MSG_C2S;
	m_curHeartMaxCount = KCP_HEARTBEAT_MAX_COUNT_CLIENT;
#endif
}

KCPSession::~KCPSession()
{
	if (m_recvBuffer)
	{
		m_recvBuffer->~Buffer();
		fc_free(m_recvBuffer);
		m_recvBuffer = NULL;
	}

	if (m_socket)
	{
		m_socket->~KCPSocket();
		fc_free(m_socket);
		m_socket = NULL;
	}
}

void KCPSession::init(KCPSocket* socket)
{
	assert(socket != 0);
	m_socket = socket;
	m_socket->setCloseCallback(std::bind(&KCPSession::on_socket_close, this, std::placeholders::_1));
	m_socket->setRecvCallback(std::bind(&KCPSession::on_socket_recv, this, std::placeholders::_1, std::placeholders::_2));

	m_recvBuffer = (Buffer*)fc_malloc(sizeof(Buffer));
	new (m_recvBuffer)Buffer(1024 * 1);
}

void KCPSession::executeSend(char* data, uint32_t len)
{
	if (data == NULL || len <= 0)
		return;

	if (isOnline())
	{
		m_socket->send(data, len);
	}
	fc_free(data);
}

void KCPSession::executeDisconnect()
{
	if (isOnline())
	{
		setIsOnline(false);
		getKCPSocket()->disconnect();
	}
}

bool KCPSession::executeConnect(const char* ip, uint32_t port)
{
	return getKCPSocket()->connect(ip, port);
}

void KCPSession::setIsOnline(bool isOnline)
{
	Session::setIsOnline(isOnline);
	m_recvBuffer->clear();
#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
	m_curHeartCount = m_resetHeartCount;
	m_curHeartTime = 0;
#endif
}

void KCPSession::on_socket_close(Socket* socket)
{
	this->setIsOnline(false);
	if (m_sessionCloseCallback)
	{
		m_sessionCloseCallback(this);
	}
}

void KCPSession::on_socket_recv(char* data, ssize_t len)
{
	if (!isOnline())
		return;

#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
	m_curHeartCount = m_resetHeartCount;
	m_curHeartTime = 0;
#endif
	
	if (len <= 0)
		return;

	m_recvBuffer->add(data, len);

	const static uint32_t headlen = sizeof(KCPMsgHead);

	while (m_recvBuffer->getDataLength() >= headlen)
	{
		KCPMsgHead* h = (KCPMsgHead*)m_recvBuffer->getHeadBlockData();

		//长度大于最大包长或长度小于等于零，不合法客户端
		if (h->len > KCP_BIG_MSG_MAX_LEN || h->len <= 0)
		{
#if OPEN_NET_UV_DEBUG == 1
			char* pMsg = (char*)fc_malloc(m_recvBuffer->getDataLength());
			m_recvBuffer->get(pMsg);
			std::string errdata(pMsg, m_recvBuffer->getDataLength());
			fc_free(pMsg);
			NET_UV_LOG(NET_UV_L_WARNING, errdata.c_str());
#endif
			m_recvBuffer->clear();
			NET_UV_LOG(NET_UV_L_WARNING, "数据不合法 (1)!!!!");
			executeDisconnect();
			return;
		}
		// 消息内容标记不合法
#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
		if (h->tag <= NET_MSG_TYPE::MT_MIN || h->tag > NET_MSG_TYPE::MT_MAX)
		{
			NET_UV_LOG(NET_UV_L_WARNING, "数据不合法 (2)!!!!");

#if OPEN_NET_UV_DEBUG == 1
			char* pMsg = (char*)fc_malloc(m_recvBuffer->getDataLength());
			m_recvBuffer->get(pMsg);
			std::string errdata(pMsg, m_recvBuffer->getDataLength());
			fc_free(pMsg);
			NET_UV_LOG(NET_UV_L_WARNING, errdata.c_str());
#endif
			m_recvBuffer->clear();
			executeDisconnect();
			return;
		}
#endif

		int32_t subv = m_recvBuffer->getDataLength() - (h->len + headlen);

		//消息接收完成
		if (subv >= 0)
		{
			char* pMsg = (char*)fc_malloc(m_recvBuffer->getDataLength());
			m_recvBuffer->get(pMsg);

			char* src = pMsg + headlen;

#if KCP_UV_OPEN_MD5_CHECK == 1
			uint32_t recvLen = 0;
			char* recvData = kcp_uv_decode(src, h->len, recvLen);

			if (recvData != NULL && recvLen > 0)
			{
#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
				onRecvMsgPackage(recvData, recvLen, h->tag);
#else
				onRecvMsgPackage(recvData, recvLen, NET_MSG_TYPE::MT_DEFAULT);
#endif
			}
			else//数据不合法
			{
				NET_UV_LOG(NET_UV_L_WARNING, "数据不合法 (3)!!!!");
#if OPEN_NET_UV_DEBUG == 1
				std::string errdata(pMsg, m_recvBuffer->getDataLength());
				NET_UV_LOG(NET_UV_L_WARNING, errdata.c_str());
#endif
				m_recvBuffer->clear();
				fc_free(pMsg);
				executeDisconnect();
				return;
			}
#else
			char* recvData = (char*)fc_malloc(h->len + 1);
			memcpy(recvData, src, h->len);
			recvData[h->len] = '\0';

#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
			onRecvMsgPackage(recvData, h->len, h->tag);
#else
			onRecvMsgPackage(recvData, h->len, NET_MSG_TYPE::MT_DEFAULT);
#endif
#endif
			m_recvBuffer->clear();

			if (subv > 0)
			{
				m_recvBuffer->add(data + (len - subv), subv);
			}
			fc_free(pMsg);
		}
		else
		{
			break;
		}
	}
}

void KCPSession::onRecvMsgPackage(char* data, uint32_t len, NET_HEART_TYPE type)
{
	if (type == NET_MSG_TYPE::MT_HEARTBEAT)
	{
		if (len == NET_HEARTBEAT_MSG_SIZE)
		{
			NET_HEART_TYPE msg = *((NET_HEART_TYPE*)data);
			if (msg == NET_HEARTBEAT_MSG_C2S)
			{
				uint32_t sendlen = 0;
				char* senddata = kcp_packageHeartMsgData(NET_HEARTBEAT_RET_MSG_S2C, &sendlen);
				executeSend(senddata, sendlen);
				NET_UV_LOG(NET_UV_L_HEART, "recv heart c->s");
			}
			else if (msg == NET_HEARTBEAT_MSG_S2C)
			{
				uint32_t sendlen = 0;
				char* senddata = kcp_packageHeartMsgData(NET_HEARTBEAT_RET_MSG_C2S, &sendlen);
				executeSend(senddata, sendlen);
				NET_UV_LOG(NET_UV_L_HEART, "recv heart s->c");
			}
			else if (msg > NET_HEARTBEAT_RET_MSG_S2C) // 非法心跳
			{
				this->disconnect();
				NET_UV_LOG(NET_UV_L_HEART, "收到非法心跳");
			}
		}
		fc_free(data);
	}
	else
	{
		m_sessionRecvCallback(this, data, len);
	}
}


void KCPSession::update(uint32_t time)
{
	if (!isOnline())
		return;

	m_curHeartTime += time;
	if (m_curHeartTime >= KCP_HEARTBEAT_CHECK_DELAY)
	{
		m_curHeartTime = 0;
		m_curHeartCount++;
		if (m_curHeartCount > 0)
		{
			if (m_curHeartCount > m_curHeartMaxCount)
			{
				m_curHeartCount = m_resetHeartCount;
				NET_UV_LOG(NET_UV_L_INFO, "无心跳回复，断开连接");
				executeDisconnect();
			}
			else
			{
				uint32_t sendlen = 0;
				char* senddata = kcp_packageHeartMsgData(m_sendHeartMsg, &sendlen);
				executeSend(senddata, sendlen);
				NET_UV_LOG(NET_UV_L_HEART, "kcp send heart %d", m_sendHeartMsg);
			}
		}
	}
}

void KCPSession::updateKcp(IUINT32 update_clock)
{
	getKCPSocket()->socketUpdate(update_clock);
}

uint32_t KCPSession::getPort()
{
	return getKCPSocket()->getPort();
}

std::string KCPSession::getIp()
{
	return getKCPSocket()->getIp();
}

NS_NET_UV_END