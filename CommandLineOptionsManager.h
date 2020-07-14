#pragma once
#include <string>
#include <boost/program_options.hpp>

/**
 * Information of command line options
 */
#define INFO_CONFIG_FILE_PATH     "Instance Configuration file path"
#define INFO_RULES_FILE_PATH      "Cleanup rules file path"
#define INFO_INSTANCE_NAME        "Name of cleaner instance"
#define INFO_INSTANCE_TYPE        "Type of cleaner instance.\n1-Azure Blob cleaner, 2-File system cleaner"
#define INFO_LOG_FILE_PATH        "Log file path"

/**
 * Command line arguments option
 */
#define OPTION_HELP               "help, h"
#define OPTION_CONFIG_FILE_PATH   "config_file_path"
#define OPTION_RULES_FILE_PATH    "rules_file_path"
#define OPTION_INSTANCE_NAME      "instance_name"
#define OPTION_INSTANCE_TYPE      "instance_type"
#define OPTION_PREVIEW            "preview"
#define OPTION_LOG_FILE_PATH      "log_file_path"

/**
 * Default values for command line options
 */
#define DEFAULT_CONFIG_FILE_PATH  "c:\\my_cleaner_config.json"
#define DEFAULT_RULES_FILE_PATH   "c:\\my_cleaner_rules.json"
#define DEFAULT_INSTANCE_NAME     "MY_INSTANCE"
#define DEFAULT_INSTANCE_TYPE     INSTANCE_TYPE_INVALID

/**/
class CCommandLineOptionsManager
{
private:
    std::string m_configFilePath;
    std::string m_rulesFilePath;
    std::string m_instanceName;
    std::string m_logFilePath;

    int m_instanceType;
    bool m_previewFlag;

    boost::program_options::options_description m_usageDescription;

public:
    /**
     * CCommandLineOptionsManager
     *
     * @author Rahul Naik
     *
     * Default constructor
     *
     */
    CCommandLineOptionsManager();

    /**
     * initializeArgumentValues
     *
     * Based on command line arguments, initialize the required
     * arguments.
     *
     * @author Rahul Naik
     *
     * @param[in] argc  :  Command line argument count
     * @param[in] argv  :  Array of all command line arguments.
     *
     * @return: Return E_SUCCESS if successful. Error code if it fails
     *
     */
    int initializeArgumentValues(int argc, const char* argv[]);

    /**
     * validateArguments
     *
     * Validate all input arguments
     *
     * @author Rahul Naik
     *
     * @return: Return E_SUCCESS if successful. Error code if it fails
     *
     */
    int validateArguments();

    /**
     * printUsage
     *
     * Print command line usage
     *
     * @author Rahul Naik
     *
     */
    void printUsage();

    /**
     * getCleanerInstanceType
     *
     * Get the cleaner instance type which is provided as a argument
     *
     * @author Rahul Naik
     *
     * @return integer for cleaner instance type
     */
    int getCleanerInstanceType();

    /**
     * getInstanceName
     *
     * Get the cleaner instance name which is provided as a argument
     *
     * @author Rahul Naik
     *
     * @return string for cleaner instance name
     */
    std::string& getInstanceName();

    /**
    * getConfigFilePath
    *
    * Get the configuration file path which is provided as a argument
    *
    * @author Rahul Naik
    *
    * @return string configuration file path
    */
    std::string& getConfigFilePath();

   /**
    * getRulesFilePath
    *
    * Get the rules file path which is provided as a argument
    *
    * @author Rahul Naik
    *
    * @return string configuration file path
    */
    std::string& getRulesFilePath();

    /**
    * getPreviewFlag
    *
    * Get the value of preview flag which is provided as a argument
    *
    * @author Rahul Naik
    *
    * @return bool value for preview flag
    */
    bool getPreviewFlag();

    /**
    * getLogFilePath
    *
    * Get the value of log file path which is provided as a argument
    *
    * @author Rahul Naik
    *
    * @return string  value for log file path
    */
    std::string& getLogFilePath();
};

