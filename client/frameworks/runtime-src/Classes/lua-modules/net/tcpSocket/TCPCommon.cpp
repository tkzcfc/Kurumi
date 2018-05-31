#include "TCPCommon.h"
#include "md5.h"
#include <time.h>

#if OPEN_TCP_UV_DEBUG == 1
#include<mutex>
#endif

typedef void(*uvOutputLoggerType)(const char*);
uvOutputLoggerType uvOutputLogger = 0;


std::string getUVError(int errcode)
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

string getTime_UV()
{
	time_t timep;
	time(&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    return tmp;
}



#if OPEN_TCP_UV_DEBUG == 1
struct mallocBlockInfo
{
	unsigned int len;
	std::string file;
	int line;
};

std::mutex block_mutex;
unsigned int block_size = 0;
std::map<void*, mallocBlockInfo> block_map;

void* fc_malloc_s(unsigned int len, const char* file, int line)
{
	mallocBlockInfo info;
	info.file = file;
	info.line = line;
	info.len = len;

	block_mutex.lock();

	void* p = malloc(len);

	if (p == NULL)
	{
#if defined (WIN32) || defined(_WIN32)
		MessageBox(NULL, TEXT("Allocated memory failure!!!"), TEXT("ERROR"), MB_OK);
		assert(0);
#else
		printf("ERROR: Allocated memory failure!!!\n");
		assert(0);
#endif
	}

	block_size++;
	block_map.insert(std::make_pair(p, info));

	block_mutex.unlock();

	return p;
	//return malloc(len);
}
void fc_free(void* p)
{
	if (p == NULL)
		return;
	block_mutex.lock();

	auto it = block_map.find(p);
	if (it == block_map.end())
	{
		assert(p == NULL);
		UV_LOG("fc_free warning : [%p] not find", p);
	}
	else
	{
		block_size--;
		block_map.erase(it);
	}
	free(p);

	block_mutex.unlock();
}



void printMemInfo()
{
	block_mutex.lock();
	UV_LOG("block size = %d\n", block_size);
	auto it = block_map.begin();
	for (; it != block_map.end(); ++it)
	{
		UV_LOG("[%p] : [%d] [%s  %d]\n", it->first, it->second.len, it->second.file.c_str(), it->second.line);
	}
	block_mutex.unlock();
}

void tcp_uvLog(const char* format, ...)
{
	va_list args;
	char buf[16386];

	va_start(args, format);
	vsnprintf(buf, sizeof(buf), format, args);
	va_end(args);

	std::string str = getTime_UV();
	str.append("[TCP-UV]: ");
	str.append(buf);
	str.append("\n");
	if (uvOutputLogger == NULL)
	{
		printf("%s", str.c_str());
	}
	else
	{
		uvOutputLogger(str.c_str());
	}

	//va_list list;
	//va_start(list, format);
	//vprintf(format, list);
	//va_end(list);
	//printf("\n");
}

#else


#endif


void setUVLogPrintFunc(void(*func)(const char*))
{
	uvOutputLogger = func;
}












