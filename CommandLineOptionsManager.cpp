#include <iostream>

#include "CommandLineOptionsManager.h"
#include "ErrorCode.h"
#include "MyCleaner.h"
#include "Logger.h"

CCommandLineOptionsManager::CCommandLineOptionsManager():
    m_usageDescription("Options"),
    m_logFilePath(DEFAULT_LOG_FILE_PATH)
{
    m_instanceType = DEFAULT_INSTANCE_TYPE;
    m_previewFlag = false;

    // Add all supported options with default values and description
    m_usageDescription.add_options()
        (OPTION_HELP, "Help Screen")
        (OPTION_CONFIG_FILE_PATH, boost::program_options::value<std::string>()->default_value(DEFAULT_CONFIG_FILE_PATH), INFO_CONFIG_FILE_PATH)
        (OPTION_RULES_FILE_PATH, boost::program_options::value<std::string>()->default_value(DEFAULT_RULES_FILE_PATH), INFO_RULES_FILE_PATH)
        (OPTION_INSTANCE_NAME, boost::program_options::value<std::string>()->default_value(DEFAULT_INSTANCE_NAME), INFO_INSTANCE_NAME)
        (OPTION_LOG_FILE_PATH, boost::program_options::value<std::string>()->default_value(DEFAULT_LOG_FILE_PATH), INFO_LOG_FILE_PATH)
        (OPTION_INSTANCE_TYPE, boost::program_options::value<int>()->default_value(DEFAULT_INSTANCE_TYPE), INFO_INSTANCE_TYPE)
        (OPTION_PREVIEW, OPTION_PREVIEW);
        

}

void CCommandLineOptionsManager::printUsage()
{
    // Parse Command line options
    std::cout << "Usage:" << std::endl << m_usageDescription << std::endl;
}

int CCommandLineOptionsManager::getCleanerInstanceType()
{
    return m_instanceType;
}

std::string& CCommandLineOptionsManager::getInstanceName()
{
    return m_instanceName;
}

std::string& CCommandLineOptionsManager::getConfigFilePath()
{
    return m_configFilePath;
}

std::string& CCommandLineOptionsManager::getRulesFilePath()
{
    return m_rulesFilePath;
}

bool CCommandLineOptionsManager::getPreviewFlag()
{
    return m_previewFlag;
}

std::string& CCommandLineOptionsManager::getLogFilePath()
{
    return m_logFilePath;
}

int CCommandLineOptionsManager::initializeArgumentValues(int argc, const char* argv[])
{
    try
    {
        boost::program_options::variables_map variablesMap;
        store(parse_command_line(argc, argv, m_usageDescription), variablesMap);
        notify(variablesMap);

        // Extract command line options values
        if (variablesMap.count("help"))
        {
            printUsage();
            exit(0);
        }

        if (variablesMap.count(OPTION_INSTANCE_TYPE))
        {
            m_instanceType = variablesMap[OPTION_INSTANCE_TYPE].as<int>();
        }

        if (variablesMap.count(OPTION_CONFIG_FILE_PATH))
        {
            m_configFilePath = variablesMap[OPTION_CONFIG_FILE_PATH].as<std::string>();
        }

        if (variablesMap.count(OPTION_RULES_FILE_PATH))
        {
            m_rulesFilePath = variablesMap[OPTION_RULES_FILE_PATH].as<std::string>();
        }

        if (variablesMap.count(OPTION_INSTANCE_NAME))
        {
            m_instanceName = variablesMap[OPTION_INSTANCE_NAME].as<std::string>();
        }

        if (variablesMap.count(OPTION_PREVIEW))
        {
            m_previewFlag = true;
        }

        if (variablesMap.count(OPTION_LOG_FILE_PATH))
        {
            m_logFilePath = variablesMap[OPTION_LOG_FILE_PATH].as<std::string>();
        }

    }
    catch (const std::exception& ex)
    {
        std::cerr << "Failed to parse input arguments. Error:" << ex.what() << '\n';
        return E_FAILED_TO_PARSE_COMMAND_LINE_ARGUMENTS;
    }

	return E_SUCCESS;
}

int CCommandLineOptionsManager::validateArguments()
{
    if (m_instanceType <= INSTANCE_TYPE_INVALID
        || m_instanceType > INSTANCE_TYPE_MAX)
    {
        std::cout << "Invalid instance type:" << m_instanceType << std::endl;
        printUsage();
    }

    if (m_instanceName.empty()
        || m_configFilePath.empty()
        || m_rulesFilePath.empty())
    {
        std::cout << "One of the provided option is empty." << std::endl;
        printUsage();
    }

    return E_SUCCESS; 
}