#include "GLog.h"
#include "GameMacro.h"

namespace flog
{
#if G_TARGET_SERVER
	static const int MAX_LOG_LENGTH = 16 * 1024;


	void log_i(const char * format, ...)
	{
		int bufferSize = MAX_LOG_LENGTH;
		char* buf = nullptr;
		int nret = 0;
		va_list args;
		do
		{
			buf = new (std::nothrow) char[bufferSize];
			if (buf == nullptr)
				return;
			/*
			pitfall: The behavior of vsnprintf between VS2013 and VS2015/2017 is different
			VS2013 or Unix-Like System will return -1 when buffer not enough, but VS2015/2017 will return the actural needed length for buffer at this station
			The _vsnprintf behavior is compatible API which always return -1 when buffer isn't enough at VS2013/2015/2017
			Yes, The vsnprintf is more efficient implemented by MSVC 19.0 or later, AND it's also standard-compliant, see reference: http://www.cplusplus.com/reference/cstdio/vsnprintf/
			*/
			va_start(args, format);
			nret = vsnprintf(buf, bufferSize - 3, format, args);
			va_end(args);

			if (nret >= 0)
			{ // VS2015/2017
				if (nret <= bufferSize - 3)
				{// success, so don't need to realloc
					break;
				}
				else
				{
					bufferSize = nret + 3;
					delete[] buf;
				}
			}
			else // < 0
			{	// VS2013 or Unix-like System(GCC)
				bufferSize *= 2;
				delete[] buf;
			}
		} while (true);
		//buf[nret] = '\n';
		buf[++nret] = '\0';

		LOG(INFO) << "[FIGHT] " << buf;

		delete[] buf;
	}

	void log_w(const char * format, ...)
	{
		int bufferSize = MAX_LOG_LENGTH;
		char* buf = nullptr;
		int nret = 0;
		va_list args;
		do
		{
			buf = new (std::nothrow) char[bufferSize];
			if (buf == nullptr)
				return;
			/*
			pitfall: The behavior of vsnprintf between VS2013 and VS2015/2017 is different
			VS2013 or Unix-Like System will return -1 when buffer not enough, but VS2015/2017 will return the actural needed length for buffer at this station
			The _vsnprintf behavior is compatible API which always return -1 when buffer isn't enough at VS2013/2015/2017
			Yes, The vsnprintf is more efficient implemented by MSVC 19.0 or later, AND it's also standard-compliant, see reference: http://www.cplusplus.com/reference/cstdio/vsnprintf/
			*/
			va_start(args, format);
			nret = vsnprintf(buf, bufferSize - 3, format, args);
			va_end(args);

			if (nret >= 0)
			{ // VS2015/2017
				if (nret <= bufferSize - 3)
				{// success, so don't need to realloc
					break;
				}
				else
				{
					bufferSize = nret + 3;
					delete[] buf;
				}
			}
			else // < 0
			{	// VS2013 or Unix-like System(GCC)
				bufferSize *= 2;
				delete[] buf;
			}
		} while (true);
		//buf[nret] = '\n';
		buf[++nret] = '\0';

		LOG(WARNING) << "[FIGHT] " << buf;

		delete[] buf;
	}

	void log_e(const char * format, ...)
	{
		int bufferSize = MAX_LOG_LENGTH;
		char* buf = nullptr;
		int nret = 0;
		va_list args;
		do
		{
			buf = new (std::nothrow) char[bufferSize];
			if (buf == nullptr)
				return;
			/*
			pitfall: The behavior of vsnprintf between VS2013 and VS2015/2017 is different
			VS2013 or Unix-Like System will return -1 when buffer not enough, but VS2015/2017 will return the actural needed length for buffer at this station
			The _vsnprintf behavior is compatible API which always return -1 when buffer isn't enough at VS2013/2015/2017
			Yes, The vsnprintf is more efficient implemented by MSVC 19.0 or later, AND it's also standard-compliant, see reference: http://www.cplusplus.com/reference/cstdio/vsnprintf/
			*/
			va_start(args, format);
			nret = vsnprintf(buf, bufferSize - 3, format, args);
			va_end(args);

			if (nret >= 0)
			{ // VS2015/2017
				if (nret <= bufferSize - 3)
				{// success, so don't need to realloc
					break;
				}
				else
				{
					bufferSize = nret + 3;
					delete[] buf;
				}
			}
			else // < 0
			{	// VS2013 or Unix-like System(GCC)
				bufferSize *= 2;
				delete[] buf;
			}
		} while (true);
		//buf[nret] = '\n';
		buf[++nret] = '\0';

		LOG(ERROR) << "[FIGHT] " << buf;

		delete[] buf;
	}

	void log_f(const char * format, ...)
	{
		int bufferSize = MAX_LOG_LENGTH;
		char* buf = nullptr;
		int nret = 0;
		va_list args;
		do
		{
			buf = new (std::nothrow) char[bufferSize];
			if (buf == nullptr)
				return;
			/*
			pitfall: The behavior of vsnprintf between VS2013 and VS2015/2017 is different
			VS2013 or Unix-Like System will return -1 when buffer not enough, but VS2015/2017 will return the actural needed length for buffer at this station
			The _vsnprintf behavior is compatible API which always return -1 when buffer isn't enough at VS2013/2015/2017
			Yes, The vsnprintf is more efficient implemented by MSVC 19.0 or later, AND it's also standard-compliant, see reference: http://www.cplusplus.com/reference/cstdio/vsnprintf/
			*/
			va_start(args, format);
			nret = vsnprintf(buf, bufferSize - 3, format, args);
			va_end(args);

			if (nret >= 0)
			{ // VS2015/2017
				if (nret <= bufferSize - 3)
				{// success, so don't need to realloc
					break;
				}
				else
				{
					bufferSize = nret + 3;
					delete[] buf;
				}
			}
			else // < 0
			{	// VS2013 or Unix-like System(GCC)
				bufferSize *= 2;
				delete[] buf;
			}
		} while (true);
		//buf[nret] = '\n';
		buf[++nret] = '\0';

		LOG(FATAL) << "[FIGHT] " << buf;

		delete[] buf;
	}
#else
	void log_i(const char * format, ...) {}
	void log_w(const char * format, ...) {}
	void log_e(const char * format, ...) {}
	void log_f(const char * format, ...) {}
#endif
}
