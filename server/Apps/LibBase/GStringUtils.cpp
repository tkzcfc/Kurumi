#include "GStringUtils.h"
#include <stdarg.h>
#include <assert.h>
#include "GPlatformMacros.h"

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
		char szbuf[32];
		sprintf(szbuf, "%u", msgID);
		return szbuf;
	}

	void split(const std::string& str, const std::string& delimiter, std::vector<std::string>& result)
	{
		std::string strTmp = str;
		size_t cutAt;
		while ((cutAt = strTmp.find_first_of(delimiter)) != strTmp.npos)
		{
			if (cutAt > 0)
			{
				result.push_back(strTmp.substr(0, cutAt));
			}
			strTmp = strTmp.substr(cutAt + 1);
		}

		if (!strTmp.empty())
		{
			result.push_back(strTmp);
		}
	}


#if UNICODE
	static std::wstring stringUtf8ToWideChar(const std::string& strUtf8)
	{
#if G_TARGET_PLATFORM == G_PLATFORM_WIN32
		std::wstring ret;
		if (!strUtf8.empty())
		{
			int nNum = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, nullptr, 0);
			if (nNum)
			{
				WCHAR* wideCharString = new WCHAR[nNum + 1];
				wideCharString[0] = 0;

				nNum = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, wideCharString, nNum + 1);

				ret = wideCharString;
				delete[] wideCharString;
			}
			else
			{
				printf("Wrong convert to WideChar code:0x%x", GetLastError());
			}
		}
		return ret;
#else
		return std::wstring();
#endif
	}

	static std::string stringWideCharToUtf8(const std::wstring& strWideChar)
	{
#if G_TARGET_PLATFORM == G_PLATFORM_WIN32
		std::string ret;
		if (!strWideChar.empty())
		{
			int nNum = WideCharToMultiByte(CP_UTF8, 0, strWideChar.c_str(), -1, nullptr, 0, nullptr, FALSE);
			if (nNum)
			{
				char* utf8String = new char[nNum + 1];
				utf8String[0] = 0;

				nNum = WideCharToMultiByte(CP_UTF8, 0, strWideChar.c_str(), -1, utf8String, nNum + 1, nullptr, FALSE);

				ret = utf8String;
				delete[] utf8String;
			}
			else
			{
				printf("Wrong convert to Utf8 code:0x%x", GetLastError());
			}
		}

		return ret;
#else
		return std::string();
#endif
	}
#else

#endif



	bool endswith(const std::string& str, const std::string& end)
	{
		int srclen = str.size();
		int endlen = end.size();
		if (srclen >= endlen)
		{
			std::string temp = str.substr(srclen - endlen, endlen);
			if (temp == end)
				return true;
		}

		return false;
	}
	std::string trim(const std::string& str)
	{
		std::string ret;
		//find the first position of not start with space or '\t'
		std::string::size_type pos_begin = str.find_first_not_of(" \t");
		if (pos_begin == std::string::npos)
			return str;

		//find the last position of end with space or '\t'
		std::string::size_type pos_end = str.find_last_not_of(" \t");
		if (pos_end == std::string::npos)
			return str;

		ret = str.substr(pos_begin, pos_end - pos_begin);

		return ret;
	}

	bool startswith(const std::string& str, const std::string& start)
	{
		int srclen = str.size();
		int startlen = start.size();
		if (srclen >= startlen)
		{
			std::string temp = str.substr(0, startlen);
			if (temp == start)
				return true;
		}

		return false;
	}

	std::string replaceString(const std::string& str, const std::string& targetstr, const std::string& replacestr)
	{
		std::string outstr(str);
		while (true)
		{
			std::size_t pos = outstr.find(targetstr.c_str());
			if (pos == std::string::npos)
			{
				break;
			}
			else
			{
				outstr.replace(outstr.begin() + pos, outstr.begin() + pos + targetstr.size(), replacestr.c_str());
			}
		}
		return outstr;
	}

}

