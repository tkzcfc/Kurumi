#include "KcpUtils.h"

NS_NET_UV_BEGIN


#define NET_KCP_CONNECT_PACKET "kcp_connect_package get_conv"
#define NET_KCP_SEND_BACK_CONV_PACKET "kcp_connect_back_package"
#define NET_KCP_SVR_CONNECT_PACKET "kcp_svr_connect_package conv:"
#define NET_KCP_SVR_SEND_BACK_CONV_PACKET "kcp_connect_svr_back_package conv:"
#define NET_KCP_DISCONNECT_PACKET "kcp_disconnect_package"
#define NET_KCP_HEART_PACKET "kcp_heart_package"
#define NET_KCP_HEART_BACK_PACKET "kcp_heart_back_package"

std::string kcp_making_connect_packet(void)
{
	return std::string(NET_KCP_CONNECT_PACKET, sizeof(NET_KCP_CONNECT_PACKET));
}

bool kcp_is_connect_packet(const char* data, size_t len)
{
	return (len == sizeof(NET_KCP_CONNECT_PACKET) &&
		memcmp(data, NET_KCP_CONNECT_PACKET, sizeof(NET_KCP_CONNECT_PACKET) - 1) == 0);
}

bool kcp_is_send_back_conv_packet(const char* data, size_t len)
{
	return (len > sizeof(NET_KCP_SEND_BACK_CONV_PACKET) &&
		memcmp(data, NET_KCP_SEND_BACK_CONV_PACKET, sizeof(NET_KCP_SEND_BACK_CONV_PACKET) - 1) == 0);
}

std::string kcp_making_send_back_conv_packet(uint32_t conv, uint32_t port)
{
	char str_send_back_conv[256] = "";
	size_t n = snprintf(str_send_back_conv, sizeof(str_send_back_conv), "%s conv:%u newport:%u", NET_KCP_SEND_BACK_CONV_PACKET, conv, port);
	return std::string(str_send_back_conv, n);
}

bool kcp_grab_conv_from_send_back_conv_packet(const char* data, size_t len, uint32_t& out_conv, uint32_t& out_port)
{
	std::string str(data, len);

	const char* conv_key = "conv:";
	const char* port_key = "newport:";

	std::size_t pos = 0;
	pos = str.find(conv_key);
	if (pos != std::string::npos)
	{
		std::string str_value;
		for (size_t i = pos + strlen(conv_key); i <= str.size(); ++i)
		{
			if ('0' <= str[i] && str[i] <= '9')
				str_value.push_back(str[i]);
			else
				break;
		}
		if (str_value.empty())
		{
			return false;
		}
		out_conv = atol(str_value.c_str());
	}

	pos = str.find(port_key);
	if (pos != std::string::npos)
	{
		std::string str_value;
		for (size_t i = pos + strlen(port_key); i <= str.size(); ++i)
		{
			if ('0' <= str[i] && str[i] <= '9')
				str_value.push_back(str[i]);
			else
				break;
		}
		if (str_value.empty())
		{
			return false;
		}
		out_port = atol(str_value.c_str());
	}
	return true;
}




std::string kcp_making_svr_connect_packet(uint32_t conv)
{
	char str_send_back_conv[256] = "";
	size_t n = snprintf(str_send_back_conv, sizeof(str_send_back_conv), "%s %u", NET_KCP_SVR_CONNECT_PACKET, conv);
	return std::string(str_send_back_conv, n);
}

bool kcp_is_svr_connect_packet(const char* data, size_t len)
{
	return (len > sizeof(NET_KCP_SVR_CONNECT_PACKET) &&
		memcmp(data, NET_KCP_SVR_CONNECT_PACKET, sizeof(NET_KCP_SVR_CONNECT_PACKET) - 1) == 0);
}

uint32_t kcp_grab_conv_from_svr_connect_packet(const char* data, size_t len)
{
	uint32_t conv = atol(data + sizeof(NET_KCP_SVR_CONNECT_PACKET));
	return conv;
}

std::string kcp_making_svr_send_back_conv_packet(uint32_t conv)
{
	char str_send_back_conv[256] = "";
	size_t n = snprintf(str_send_back_conv, sizeof(str_send_back_conv), "%s %u", NET_KCP_SVR_SEND_BACK_CONV_PACKET, conv);
	return std::string(str_send_back_conv, n);
}

bool kcp_is_svr_send_back_conv_packet(const char* data, size_t len)
{
	return (len > sizeof(NET_KCP_SVR_SEND_BACK_CONV_PACKET) &&
		memcmp(data, NET_KCP_SVR_SEND_BACK_CONV_PACKET, sizeof(NET_KCP_SVR_SEND_BACK_CONV_PACKET) - 1) == 0);
}

uint32_t kcp_grab_conv_from_svr_send_back_conv_packet(const char* data, size_t len)
{
	uint32_t conv = atol(data + sizeof(NET_KCP_SVR_SEND_BACK_CONV_PACKET));
	return conv;
}




std::string kcp_making_disconnect_packet(uint32_t conv)
{
	char str_disconnect_packet[256] = "";
	size_t n = snprintf(str_disconnect_packet, sizeof(str_disconnect_packet), "%s %u", NET_KCP_DISCONNECT_PACKET, conv);
	return std::string(str_disconnect_packet, n);
}

bool kcp_is_disconnect_packet(const char* data, size_t len)
{
	return (len > sizeof(NET_KCP_DISCONNECT_PACKET) &&
		memcmp(data, NET_KCP_DISCONNECT_PACKET, sizeof(NET_KCP_DISCONNECT_PACKET) - 1) == 0);
}

uint32_t kcp_grab_conv_from_disconnect_packet(const char* data, size_t len)
{
	uint32_t conv = atol(data + sizeof(NET_KCP_DISCONNECT_PACKET));
	return conv;
}



std::string kcp_making_heart_packet()
{
	return std::string(NET_KCP_HEART_PACKET, sizeof(NET_KCP_HEART_PACKET));
}

bool kcp_is_heart_packet(const char* data, size_t len)
{
	return (len == sizeof(NET_KCP_HEART_PACKET) &&
		memcmp(data, NET_KCP_HEART_PACKET, sizeof(NET_KCP_HEART_PACKET) - 1) == 0);
}

std::string kcp_making_heart_back_packet()
{
	return std::string(NET_KCP_HEART_BACK_PACKET, sizeof(NET_KCP_HEART_BACK_PACKET));
}

bool kcp_is_heart_back_packet(const char* data, size_t len)
{
	return (len == sizeof(NET_KCP_HEART_BACK_PACKET) &&
		memcmp(data, NET_KCP_HEART_BACK_PACKET, sizeof(NET_KCP_HEART_BACK_PACKET) - 1) == 0);
}




// 加密Key
const char* kcp_uv_encodeKey = KCP_UV_ENCODE_KEY;
const uint32_t kcp_uv_encodeKeyLen = (uint32_t)strlen(kcp_uv_encodeKey);

const static uint32_t kcp_uv_hashlen = sizeof(uint32_t);


const static uint32_t kcp_msg_headlen = sizeof(KCPMsgHead);



// 加密
// 加密前 ：|-DATA-|
// 加密后 ：|-（MD5（DATA+加密key））的hash值-|-DATA-|
char* kcp_uv_encode(const char* data, uint32_t len, uint32_t &outLen)
{
	MD5 M;

	outLen = kcp_uv_hashlen + len;

	char* r = (char*)fc_malloc(outLen + kcp_uv_encodeKeyLen);

	memcpy(r + kcp_uv_hashlen, data, len);
	memcpy(r + outLen, kcp_uv_encodeKey, kcp_uv_encodeKeyLen);

	M.reset();
	M.update(r + kcp_uv_hashlen, len + kcp_uv_encodeKeyLen);

	auto md5s = M.toString();

	auto hashvalue = net_getBufHash(md5s.c_str(), (uint32_t)md5s.size());
	memcpy(r, &hashvalue, kcp_uv_hashlen);

	return r;
}

// 解密
char* kcp_uv_decode(const char* data, uint32_t len, uint32_t &outLen)
{
	outLen = 0;

	MD5 M;

	int32_t datalen = len - kcp_uv_hashlen;

	char* p = (char*)fc_malloc(datalen + kcp_uv_encodeKeyLen + 1);

	memcpy(p, data + kcp_uv_hashlen, datalen);
	memcpy(p + datalen, kcp_uv_encodeKey, kcp_uv_encodeKeyLen);

	M.reset();
	M.update(p, datalen + kcp_uv_encodeKeyLen);

	auto md5s = M.toString();

	uint32_t hashvalue = net_getBufHash(md5s.c_str(), (uint32_t)md5s.size());
	if (hashvalue == *(uint32_t*)(data))
	{
		outLen = datalen;
	}

	//该数据不合法
	if (outLen == 0)
	{
		fc_free(p);
		p = NULL;
	}
	else
	{
		p[datalen] = '\0';
	}
	return p;
}





// 打包数据
uv_buf_t* kcp_packageData(char* data, uint32_t len, int32_t* bufCount)
{
	*bufCount = 0;
	if (data == NULL || len <= 0)
	{
		return NULL;
	}

	if (len > KCP_BIG_MSG_MAX_LEN)
	{
#if defined (WIN32) || defined(_WIN32)
		MessageBox(NULL, TEXT("消息超过最大限制"), TEXT("错误"), MB_OK);
#else
		printf("消息超过最大限制");
#endif
		assert(0);
		return NULL;
	}

#if KCP_UV_OPEN_MD5_CHECK == 1

	uint32_t encodelen = 0;
	char* encodedata = kcp_uv_encode(data, len, encodelen);
	if (encodedata == NULL)
	{
		assert(0);
		return NULL;
	}
	uint32_t sendlen = kcp_msg_headlen + encodelen;
	char* p = (char*)fc_malloc(sendlen);

	KCPMsgHead* h = (KCPMsgHead*)p;
	h->len = encodelen;
#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
	h->tag = NET_MSG_TYPE::MT_DEFAULT;
#endif
	memcpy(p + kcp_msg_headlen, encodedata, encodelen);

	fc_free(encodedata);
#else
	uint32_t sendlen = kcp_msg_headlen + len;
	char* p = (char*)fc_malloc(sendlen);
	KCPMsgHead* h = (KCPMsgHead*)p;
	h->len = len;
#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
	h->tag = NET_MSG_TYPE::MT_DEFAULT;
#endif
	memcpy(p + kcp_msg_headlen, data, len);
#endif
	uv_buf_t* outBuf = NULL;
	// 大文件分片
	if (sendlen > KCP_WRITE_MAX_LEN)
	{
		*bufCount = sendlen / KCP_WRITE_MAX_LEN;
		if (sendlen % KCP_WRITE_MAX_LEN != 0)
		{
			*bufCount = *bufCount + 1;
		}

		outBuf = (uv_buf_t*)fc_malloc(sizeof(uv_buf_t) * (*bufCount));

		int32_t curIndex = 0;
		int32_t curArrIndex = 0;

		while (sendlen > 0)
		{
			if (sendlen < KCP_WRITE_MAX_LEN)
			{
				char* tmp = (char*)fc_malloc(sendlen);
				memcpy(tmp, p + curIndex, sendlen);

				(outBuf + curArrIndex)->base = tmp;
				(outBuf + curArrIndex)->len = sendlen;

				curArrIndex++;
				curIndex = curIndex + sendlen;
				sendlen = 0;
			}
			else
			{
				char* tmp = (char*)fc_malloc(KCP_WRITE_MAX_LEN);
				memcpy(tmp, p + curIndex, KCP_WRITE_MAX_LEN);

				(outBuf + curArrIndex)->base = tmp;
				(outBuf + curArrIndex)->len = KCP_WRITE_MAX_LEN;

				curArrIndex++;
				sendlen = sendlen - KCP_WRITE_MAX_LEN;
				curIndex = curIndex + KCP_WRITE_MAX_LEN;
			}
		}
		fc_free(p);
	}
	else
	{
		*bufCount = 1;

		outBuf = (uv_buf_t*)fc_malloc(sizeof(uv_buf_t));
		outBuf->base = p;
		outBuf->len = sendlen;
	}
	return outBuf;
	}

// 打包心跳消息
char* kcp_packageHeartMsgData(NET_HEART_TYPE msg, uint32_t* outBufSize)
{
	*outBufSize = 0;
#if KCP_UV_OPEN_MD5_CHECK == 1
	uint32_t encodelen = 0;
	char* encodedata = kcp_uv_encode((char*)&msg, NET_HEARTBEAT_MSG_SIZE, encodelen);
	if (encodedata == NULL)
	{
		assert(0);
		return NULL;
	}
	uint32_t sendlen = kcp_msg_headlen + encodelen;
	char* p = (char*)fc_malloc(sendlen);
	if (p == NULL)
	{
		fc_free(encodedata);
		return NULL;
	}
	KCPMsgHead* h = (KCPMsgHead*)p;
	h->len = encodelen;
#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
	h->tag = NET_MSG_TYPE::MT_HEARTBEAT;
#endif
	memcpy(p + kcp_msg_headlen, encodedata, encodelen);

	fc_free(encodedata);
#else
	uint32_t sendlen = kcp_msg_headlen + NET_HEARTBEAT_MSG_SIZE;
	char* p = (char*)fc_malloc(sendlen);
	if (p == NULL)
	{
		return NULL;
	}
	KCPMsgHead* h = (KCPMsgHead*)p;
	h->len = NET_HEARTBEAT_MSG_SIZE;
#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
	h->tag = NET_MSG_TYPE::MT_HEARTBEAT;
#endif
	memcpy(p + kcp_msg_headlen, &msg, NET_HEARTBEAT_MSG_SIZE);
#endif

	*outBufSize = sendlen;

	return p;
}

NS_NET_UV_END
