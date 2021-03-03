#pragma once

#include <string>

namespace StringUtils
{
	std::string format(const char* format, ...);

	std::string msgKey(uint32_t msgID);
}
