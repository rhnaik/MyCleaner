#include "AzureStorageBlobCleaner.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include "ErrorCode.h"
#include <fstream>
#include <iomanip>

CAzureStorageBlobCleaner::CAzureStorageBlobCleaner()
{
}

CAzureStorageBlobCleaner::~CAzureStorageBlobCleaner()
{
	// Delete all rule objects
	for (auto it : m_ruleList)
	{
		delete it;
		it = nullptr;
	}
}

int CAzureStorageBlobCleaner::loadConfiguration(
	const std::string& instanceName,
	const std::string& configurationFilePath)
{
	try
	{
		// Read instance data from JSON configuration file
		std::ifstream jsonfile(configurationFilePath);
		nlohmann::json jsonData;
		jsonfile >> jsonData;

		// Locate instance with given instance name
		bool isRequiredInstanceFound = false;

		for (auto& array : jsonData[JSON_TAG_INSTANCES])
		{
			for (auto& subArray : array[JSON_TAG_AZURE_STORAGE_BLOB_INSTANCES])
			{
				std::string currentInstanceName = subArray["instance_name"];

				if (instanceName.compare(currentInstanceName) == 0)
				{
					isRequiredInstanceFound = true;

					std::string connectionString = subArray["configuration"]["connection_string"];
					std::wstring wconnectionString(connectionString.begin(), connectionString.end());

					// Initialize Azure storage API object using connection string
					m_azureStorageBlobApi = CAzureStorageApi(wconnectionString);
					break;
				}
			}
		}

		// If it failed to locate instance name in configuration file, error out
		if (isRequiredInstanceFound == false)
		{
			std::cerr << "Failed to find configuration for instance:" << instanceName << std::endl;
			return E_FAILED_TO_GET_INSTANCE_CONF_FROM_FILE;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Failed to get configuration for instance:" << instanceName
			<< ". Exception:" << e.what() << std::endl;
		return E_FAILED_TO_GET_INSTANCE_CONF_FROM_FILE;
	}

	return E_SUCCESS;
}

int CAzureStorageBlobCleaner::cleanElgibileObjectList(bool preview)
{
	try
	{
		int retval = E_SUCCESS;

		// Get the list of all containers
		std::vector<std::wstring> containerList;

		retval = m_azureStorageBlobApi.listContainers(containerList);

		if (retval != E_SUCCESS)
		{
			std::cerr << "Failed to get the list of containers. Error:[" 
				<< retval << "]" << std::endl;
			return retval;
		}

		// Iterate over all containers and delete eligible objects
		for (auto container : containerList)
		{
			if (preview)
			{
				retval = m_azureStorageBlobApi.listBlobsWhichMatchRules(container, m_ruleList);
			}
			else
			{ 
				retval = m_azureStorageBlobApi.deleteBlobsWhichMatchRules(container, m_ruleList);
			}
			if (retval != E_SUCCESS)
			{
				std::cerr << "Failed to delete blobs which matches rules. Error:["
					<< retval << "]" << std::endl;
				return retval;
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Failed to delete eligible objects list."
			<< ". Exception:" << e.what() << std::endl;
		return E_FAILED_TO_GET_INSTANCE_CONF_FROM_FILE;
	}

	return E_SUCCESS;
}

