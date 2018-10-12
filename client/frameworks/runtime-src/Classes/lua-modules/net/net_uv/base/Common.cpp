#include "Common.h"
#include <time.h>


NS_NET_UV_BEGIN

#if OPEN_NET_MEM_CHECK == 1
#include "Mutex.h"
#endif

typedef void(*uvOutputLoggerType)(int, const char*);
uvOutputLoggerType uvOutputLogger = 0;


NET_UV_EXTERN std::string getUVError(int errcode)
{
	if (0 == errcode)
	{
		return "";
	}
	std::string err;
	auto tmpChar = uv_err_name(errcode);
	if (tmpChar)
	{
		err = tmpChar;
		err += ":";
	}
	else
	{
		char szCode[16];
		sprintf(szCode, "%d:", errcode);
		err = "unknown system errcode ";
		err.append(szCode);
	}
	tmpChar = uv_strerror(errcode);
	if (tmpChar)
	{
		err += tmpChar;
	}
	return std::move(err);
}

NET_UV_EXTERN string getTime_UV()
{
	time_t timep;
	time(&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	return tmp;
}

static const char* net_uv_log_name[NET_UV_L_FATAL + 1] =
{
	"HEART",
	"INFO",
	"WARNING",
	"ERROR",
	"FATAL"
};

NET_UV_EXTERN void net_uvLog(int level, const char* format, ...)
{
	if (level < NET_UV_L_MIN_LEVEL)
	{
		return;
	}

	va_list args;
	char buf[1024];

	va_start(args, format);
	vsnprintf(buf, sizeof(buf), format, args);
	va_end(args);

	std::string str = getTime_UV();
	str.append("[NET-UV]-[");
	str.append(net_uv_log_name[level]);
	str.append("] ");
	str.append(buf);
	str.append("\n");
	if (uvOutputLogger == NULL)
	{
		printf("%s", str.c_str());
	}
	else
	{
		uvOutputLogger(level, buf);
	}

	//va_list list;
	//va_start(list, format);
	//vprintf(format, list);
	//va_end(list);
	//printf("\n");
}

NET_UV_EXTERN void setNetUVLogPrintFunc(void(*func)(int, const char*))
{
	uvOutputLogger = func;
}




///////////////////////////////////////////////////////////////////////////////////////////////////
#if OPEN_NET_MEM_CHECK == 1
struct mallocBlockInfo
{
	unsigned int len;
	std::string file;
	int line;
};

Mutex block_mutex;
unsigned int block_size = 0;
std::map<void*, mallocBlockInfo> block_map;

NET_UV_EXTERN void* fc_malloc_s(unsigned int len, const char* file, int line)
{
	mallocBlockInfo info;
	info.file = file;
	info.line = line;
	info.len = len;

	block_mutex.lock();

	void* p = malloc(len);

	if (p == NULL)
	{
		NET_UV_LOG(NET_UV_L_FATAL, "ÉêÇëÄÚ´æÊ§°Ü!!!");
#if defined (WIN32) || defined(_WIN32)
		MessageBox(NULL, TEXT("ÉêÇëÄÚ´æÊ§°Ü!!!"), TEXT("ERROR"), MB_OK);
		assert(0);
#else
		printf("ÉêÇëÄÚ´æÊ§°Ü!!!\n");
		assert(0);
#endif
		block_mutex.unlock();
		return NULL;
	}

	block_size++;
	block_map.insert(std::make_pair(p, info));

	block_mutex.unlock();

	return p;
}

NET_UV_EXTERN void fc_free(void* p)
{
	if (p == NULL)
	{
		assert(0);
		return;
	}
	block_mutex.lock();

	auto it = block_map.find(p);
	if (it == block_map.end())
	{
		assert(p == NULL);
		NET_UV_LOG(NET_UV_L_WARNING, "fc_free: [%p] not find", p);
	}
	else
	{
		block_size--;
		block_map.erase(it);
	}
	free(p);

	block_mutex.unlock();
}



NET_UV_EXTERN void printMemInfo()
{
	block_mutex.lock();
	NET_UV_LOG(NET_UV_L_INFO, "block size = %d\n", block_size);
	auto it = block_map.begin();
	for (; it != block_map.end(); ++it)
	{
		NET_UV_LOG(NET_UV_L_INFO, "[%p] : [%d] [%s  %d]\n", it->first, it->second.len, it->second.file.c_str(), it->second.line);
	}
	block_mutex.unlock();
}

#else
#endif

NS_NET_UV_END

