#include <iostream>

#undef U

#include <iostream>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/expressions.hpp>

#define DEFAULT_LOG_FILE_PATH      "c:\\my_cleaner.log"

//Use Boost logging framework for logging

/**
 * initLogging
 *
 * Initialize logging framework
 *
 * @param[in] logFilePath : Log file path
 *
 */
void initLogging(std::string& logFilePath);