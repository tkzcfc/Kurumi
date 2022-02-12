#pragma once

#include <string>
#include <vector>

namespace StringUtils
{
	std::string format(const char* format, ...);

	std::string msgKey(uint32_t msgID);

	void split(const std::string& str, const std::string& delimiter, std::vector<std::string>& result);

#if UNICODE
	static std::wstring stringUtf8ToWideChar(const std::string& strUtf8);

	static std::string stringWideCharToUtf8(const std::wstring& strWideChar);
#else
	static std::string stringUtf8ToWideChar(const std::string& strUtf8)
	{
		return strUtf8;
	}

	static std::string stringWideCharToUtf8(const std::string& strWideChar)
	{
		return strWideChar;
	}
#endif

	bool endswith(const std::string& str, const std::string& end);

	std::string trim(const std::string& str);

	bool startswith(const std::string& str, const std::string& start);

	std::string replaceString(const std::string& str, const std::string& targetstr, const std::string& replacestr);
}
