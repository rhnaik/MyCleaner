#include "Logger.h"

namespace logging = boost::log;

void initLogging(std::string& logFilePath)
{
    logging::add_file_log(logFilePath);

    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );
}