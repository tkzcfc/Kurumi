#pragma once

#include <stdint.h>

class GEnableHighPrecisionTimer final
{
public:

	GEnableHighPrecisionTimer() = delete;

	GEnableHighPrecisionTimer(uint32_t uPeriod = 1);

	~GEnableHighPrecisionTimer();

private:

	uint32_t m_uPeriod;
};

