#include "KcpUtils.h"

NS_NET_UV_BEGIN


#define NET_KCP_CONNECT_PACKET "kcp_connect_package get_conv"
#define NET_KCP_SEND_BACK_CONV_PACKET "kcp_connect_back_package get_conv:"
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

std::string kcp_making_send_back_conv_packet(uint32_t conv)
{
	char str_send_back_conv[256] = "";
	size_t n = snprintf(str_send_back_conv, sizeof(str_send_back_conv), "%s %u", NET_KCP_SEND_BACK_CONV_PACKET, conv);
	return std::string(str_send_back_conv, n);
}

uint32_t kcp_grab_conv_from_send_back_conv_packet(const char* data, size_t len)
{
	uint32_t conv = atol(data + sizeof(NET_KCP_SEND_BACK_CONV_PACKET));
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
const int kcp_uv_encodeKeyLen = strlen(kcp_uv_encodeKey);

const static unsigned int kcp_uv_hashlen = sizeof(unsigned int);


const static unsigned int kcp_msg_headlen = sizeof(KCPMsgHead);



// 加密
// 加密前 ：|-DATA-|
// 加密后 ：|-（MD5（DATA+加密key））的hash值-|-DATA-|
NET_UV_EXTERN char* kcp_uv_encode(const char* data, unsigned int len, unsigned int &outLen)
{
	MD5 M;

	outLen = kcp_uv_hashlen + len;

	char* r = (char*)fc_malloc(outLen + kcp_uv_encodeKeyLen);

	memcpy(r + kcp_uv_hashlen, data, len);
	memcpy(r + outLen, kcp_uv_encodeKey, kcp_uv_encodeKeyLen);

	M.reset();
	M.update(r + kcp_uv_hashlen, len + kcp_uv_encodeKeyLen);

	auto md5s = M.toString();

	auto hashvalue = net_getBufHash(md5s.c_str(), md5s.size());
	memcpy(r, &hashvalue, kcp_uv_hashlen);

	return r;
}

// 解密
NET_UV_EXTERN char* kcp_uv_decode(const char* data, unsigned int len, unsigned int &outLen)
{
	outLen = 0;

	MD5 M;

	int datalen = len - kcp_uv_hashlen;

	char* p = (char*)fc_malloc(datalen + kcp_uv_encodeKeyLen + 1);

	memcpy(p, data + kcp_uv_hashlen, datalen);
	memcpy(p + datalen, kcp_uv_encodeKey, kcp_uv_encodeKeyLen);

	M.reset();
	M.update(p, datalen + kcp_uv_encodeKeyLen);

	auto md5s = M.toString();

	auto hashvalue = net_getBufHash(md5s.c_str(), md5s.size());
	if (hashvalue == *(size_t*)(data))
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
NET_UV_EXTERN uv_buf_t* kcp_packageData(char* data, unsigned int len, int* bufCount)
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

	unsigned int encodelen = 0;
	char* encodedata = kcp_uv_encode(data, len, encodelen);
	if (encodedata == NULL)
	{
		assert(0);
		return NULL;
	}
	unsigned int sendlen = kcp_msg_headlen + encodelen;
	char* p = (char*)fc_malloc(sendlen);

	KCPMsgHead* h = (KCPMsgHead*)p;
	h->len = encodelen;
#if KCP_OPEN_UV_THREAD_HEARTBEAT == 1
	h->tag = NET_MSG_TYPE::MT_DEFAULT;
#endif
	memcpy(p + kcp_msg_headlen, encodedata, encodelen);

	fc_free(encodedata);
#else
	unsigned int sendlen = kcp_msg_headlen + len;
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
		*bufCount = sendlen / KCP_WRITE_MAX_LEN + 1;

		outBuf = (uv_buf_t*)fc_malloc(sizeof(uv_buf_t) * (*bufCount));

		int curIndex = 0;
		int curArrIndex = 0;

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
NET_UV_EXTERN char* kcp_packageHeartMsgData(NET_HEART_TYPE msg, unsigned int* outBufSize)
{
	*outBufSize = 0;
#if KCP_UV_OPEN_MD5_CHECK == 1
	unsigned int encodelen = 0;
	char* encodedata = kcp_uv_encode((char*)&msg, NET_HEARTBEAT_MSG_SIZE, encodelen);
	if (encodedata == NULL)
	{
		assert(0);
		return NULL;
	}
	unsigned int sendlen = kcp_msg_headlen + encodelen;
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
	unsigned int sendlen = kcp_msg_headlen + NET_HEARTBEAT_MSG_SIZE;
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
