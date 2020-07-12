
#include <boost/program_options.hpp>
#include <iostream>

#include "AzureStorageApi.h"
#include "Logger.h"
#include "ErrorManager.h"
#include "Rule.h"
#include "Defines.h"

int main(int argc, const char*argv[])
{
    try
    {
        // Parse Command line options
        boost::program_options::options_description desc{ "Options" };
        desc.add_options()
            ("help,h", "Help Screen")
            ("config_file_path, cnf", boost::program_options::value<std::string>()->default_value(DEFAULT_CONFIG_FILE_PATH), "Config File Path")
            ("rules_file_path, rfp", boost::program_options::value<std::string>()->default_value(DEFAULT_RULES_FILE_PATH), "Rule File Path")
            ("instance_name, in", boost::program_options::value<std::string>()->default_value(DEFAULT_INSTANCE_NAME), "Instance Name")
            ("instance_type, it", boost::program_options::value<int>()->default_value(DEFAULT_INTANCE_TYPE), "Instance Type");

        // Variables for storing command line options
        std::string configFilePath;
        std::string rulesFilePath;
        std::string instanceName;
        int instanceType;

        boost::program_options::variables_map variablesMap;
        store(parse_command_line(argc, argv, desc), variablesMap);

        notify(variablesMap);

        // Extract command line options values
        if (variablesMap.count("help"))
        {
            std::cout << desc;
        }
        
        if (variablesMap.count("config_file_path"))
        {
            configFilePath = variablesMap["config_file_path"].as<std::string>();
            std::cout << "config_file_path:" <<configFilePath << std::endl;    
        }

        if (variablesMap.count("rules_file_path"))
        {
            rulesFilePath = variablesMap["rules_file_path"].as<std::string>();
            std::cout << "rules_file_path:" << rulesFilePath << std::endl;
        }
        
        if (variablesMap.count("instance_name"))
        {
            instanceName = variablesMap["instance_name"].as<std::string>();
            std::cout << "instance_name:" << instanceName << std::endl;
        }
        
        if (variablesMap.count("instance_type"))
        {
            instanceType = variablesMap["instance_type"].as<int>();
            std::cout << "instance_type:" << instanceType << std::endl;
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Failed to parse input arguments. Error:" << ex.what() << '\n';
    }

	return 0;
}
