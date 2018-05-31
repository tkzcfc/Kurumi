#include "TCPUtils.h"
#include "TCPCommon.h"
#include "md5.h"


// 加密Key
const char* tcp_uv_encodeKey = TCP_UV_ENCODE_KEY;
const int tcp_uv_encodeKeyLen = strlen(tcp_uv_encodeKey);

const int tcp_uv_hashlen = sizeof(uint32);




// 加密
// 加密前 ：|-DATA-|
// 加密后 ：|-（DATA+加密key）的hash值-|-DATA-|
char* tcp_uv_encode(const char* data, unsigned int len, unsigned int &outLen)
{
	MD5 M;

	outLen = tcp_uv_hashlen + len;

	char* r = (char*)fc_malloc(outLen + tcp_uv_encodeKeyLen);

	memcpy(r + tcp_uv_hashlen, data, len);
	memcpy(r + outLen, tcp_uv_encodeKey, tcp_uv_encodeKeyLen);

	M.reset();
	M.update(r + tcp_uv_hashlen, len + tcp_uv_encodeKeyLen);

	auto md5s = M.toString();

	auto hashvalue = GetBufHash(md5s.c_str(), md5s.size());
	memcpy(r, &hashvalue, tcp_uv_hashlen);

	return r;
}

// 解密
char* tcp_uv_decode(const char* data, unsigned int len, unsigned int &outLen)
{
	outLen = 0;

	MD5 M;

	int datalen = len - tcp_uv_hashlen;

	char* p = (char*)fc_malloc(datalen + tcp_uv_encodeKeyLen + 1);

	memcpy(p, data + tcp_uv_hashlen, datalen);
	memcpy(p + datalen, tcp_uv_encodeKey, tcp_uv_encodeKeyLen);

	M.reset();
	M.update(p, datalen + tcp_uv_encodeKeyLen);

	auto md5s = M.toString();

	auto hashvalue = GetBufHash(md5s.c_str(), md5s.size());
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

// hash
uint32 GetBufHash(const void *buf, uint32 len)
{
	uint32 seed = 131; // 31 131 1313 13131 131313 etc..
	uint32 hash = 0;
	uint32 i = 0;
	char *str = (char *)buf;
	while (i < len)
	{
		hash = hash * seed + (*str++);
		++i;
	}

	return (hash & 0x7FFFFFFF);
}
