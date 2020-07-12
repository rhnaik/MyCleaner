#pragma once

#include <string>
#include <wchar.h>

/**
 * Log verbose levels
 */
enum ELogSeverity
{
	M_DEBUG = 1,
	M_INFO,
	M_WARN,
	M_ERROR,
	M_CRITICAL
};
 
#define LOG_MESSAGE(severity, funcName, msg)                         \
			std::wstringstream logStream;                             \
			logStream << msg;                                        \
            logMessage(severity, funcName, logStream.str().c_str());

//TODO:: Need to create logger thread safe and file based
/**
 * logMessage
 *
 * Log message on console with timestamp, severity, function name and log message
 *
 *
 * Input:
 * @param severity  :  Severity of log message
 * @paran funcName  :  Name of function from function is called.
 * @param msg       :  Log message to be added.
 */
void logMessage(ELogSeverity severity,
	const char* funcName,
	const wchar_t* msg);