
#include "Logger.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <chrono>

void logMessage(ELogSeverity severity,
	const char* funcName,
	const wchar_t* msg)
{
	using std::chrono::system_clock;

	system_clock::time_point timeNow = system_clock::now();

	std::time_t timeTNow = system_clock::to_time_t(timeNow);

	char str[26] = { 0 };

#ifdef __STDC_LIB_EXT1__
	ctime_s(str, sizeof str, &timeTNow);
	printf("%s", str);
#endif

	std::wcout << str << " [" << severity << "] " << funcName << " " << msg << std::endl;
}