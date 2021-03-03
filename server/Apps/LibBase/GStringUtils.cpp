#include "GStringUtils.h"
#include <stdarg.h>
#include <assert.h>

namespace StringUtils
{
	std::string format(const char* format, ...)
	{
#define CC_VSNPRINTF_BUFFER_LENGTH 512
		va_list args;
		std::string buffer(CC_VSNPRINTF_BUFFER_LENGTH, '\0');

		va_start(args, format);
		int nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
		va_end(args);

		if (nret >= 0) {
			if ((unsigned int)nret < buffer.length()) {
				buffer.resize(nret);
			}
			else if ((unsigned int)nret > buffer.length()) { // VS2015/2017 or later Visual Studio Version
				buffer.resize(nret);

				va_start(args, format);
				nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
				va_end(args);

				assert(nret == buffer.length());
			}
			// else equals, do nothing.
		}
		else { // less or equal VS2013 and Unix System glibc implement.
			do {
				buffer.resize(buffer.length() * 3 / 2);

				va_start(args, format);
				nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
				va_end(args);

			} while (nret < 0);

			buffer.resize(nret);
		}

		return buffer;
	}

	std::string msgKey(uint32_t msgID)
	{
		char szbuf[64];
		sprintf(szbuf, "%u", msgID);
		return szbuf;
	}
}

