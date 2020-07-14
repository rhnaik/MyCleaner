#include "MyCleaner.h"
#include "AzureStorageBlobCleaner.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include "ErrorCode.h"
#include <fstream>
#include <iomanip>

// Factory method for creating MyCleanerInstance;
CMyCleaner* createMyCleanerInstance(int cleanerInstanceType)
{
	switch (cleanerInstanceType)
	{
	case INSTANCE_TYPE_AZURE_BLOB_CLEANER:
	{
		return new CAzureStorageBlobCleaner();
	}
	case INSTANCE_TYPE_FILE_SYSTEM_CLEANER:
	{
		// TODO: Need to be implemented
		// return new CFileSystemCleaner;
		return nullptr;
	}
	default:
	{
		return nullptr;
	}
	};
}

void CMyCleaner::setCleanerInstanceName(const std::string& instanceName)
{
	m_instanceName = instanceName;
}

int CMyCleaner::intitializeRulesList(const std::string& rulesListFilePath)
{
	try
	{
		// Read rules data from JSON configuration file
		std::ifstream jsonfile(rulesListFilePath);
		nlohmann::json jsonData;
		jsonfile >> jsonData;

		for (auto& array : jsonData[JSON_TAG_RULES])
		{
			// Get rule_type string for rule
			std::string currentRuleType = array["rule_type"];

			// Check if it's a valid rule type
			auto it = MapRuleStringToRuleType.find(currentRuleType);
			if (it == MapRuleStringToRuleType.end())
			{
				std::cerr << "Invalid rule type:[" << currentRuleType << "]" << std::endl;
				return E_INVALID_RULE_TYPE;
			}

			// Create object of rule based on Rule type
			CRule* currentRule = createRuleObject(MapRuleStringToRuleType[currentRuleType]);

			// Get rule configuration string and set configuration in rule
			std::string ruleConfiguration = array["rule_config"].dump();

			int retval = currentRule->parseRuleJson(ruleConfiguration);

			if (retval != E_SUCCESS)
			{
				std::cerr << "Failed to parse rule json. Error:[" << retval << "]" << std::endl;
				return retval;
			}

		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Filed to get rules from file:" << rulesListFilePath
			<< ". Exception:" << e.what() << std::endl;
		return E_FAILED_TO_GET_INSTANCE_CONF_FROM_FILE;
	}

	return E_SUCCESS;
}

