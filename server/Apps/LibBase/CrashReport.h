#ifndef _CRASH_REPORT_H_
#define _CRASH_REPORT_H_


#include <string>

// https://github.com/ylmbtm/GameProject3/blob/master/Server/Src/ServerEngine/CrashReport.h

/*安放crash定位*/
void SetCrashReport(std::string strAppName);

void UnSetCrashReport();

#endif