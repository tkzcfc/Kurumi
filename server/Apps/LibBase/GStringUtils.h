#pragma once

#include <string>
#include <vector>

namespace StringUtils
{
	std::string format(const char* format, ...);

	std::string msgKey(uint32_t msgID);

	void split(const std::string& str, const std::string& delimiter, std::vector<std::string>& result);
}
