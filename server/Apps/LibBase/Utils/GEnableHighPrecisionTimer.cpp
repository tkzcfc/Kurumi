#include "GEnableHighPrecisionTimer.h"
#include "GPlatformMacros.h"


#if G_TARGET_PLATFORM == G_PLATFORM_WIN32

// https://randomascii.wordpress.com/2013/07/08/windows-timer-resolution-megawatts-wasted/
// https://randomascii.wordpress.com/2020/10/04/windows-timer-resolution-the-great-rule-change/
// https://docs.microsoft.com/en-us/windows/win32/api/timeapi/nf-timeapi-timebeginperiod
#include <timeapi.h>
#pragma comment(lib, "Winmm.lib")

GEnableHighPrecisionTimer::GEnableHighPrecisionTimer(uint32_t uPeriod)
{
	m_uPeriod = uPeriod;
	timeBeginPeriod(m_uPeriod);
}

GEnableHighPrecisionTimer::~GEnableHighPrecisionTimer()
{
	timeEndPeriod(m_uPeriod);
}

#else

GEnableHighPrecisionTimer::GEnableHighPrecisionTimer(uint32_t uPeriod)
{
	m_uPeriod = uPeriod;
}

GEnableHighPrecisionTimer::~GEnableHighPrecisionTimer()
{}

#endif



