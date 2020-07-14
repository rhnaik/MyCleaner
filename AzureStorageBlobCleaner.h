#pragma once

#include <vector>

#include "MyCleaner.h"
#include "AzureStorageApi.h"

#define JSON_TAG_INSTANCES                      "instances"
#define JSON_TAG_AZURE_STORAGE_BLOB_INSTANCES   "azure_storage_blob_instances"
#define JSON_TAG_RULES                          "rules"

/**
 * Class for cleaning Azure storage blob objects.
 *
 *
 * @author Rahul Naik
 */
class CAzureStorageBlobCleaner :
    public CMyCleaner
{
private:
	CAzureStorageApi m_azureStorageBlobApi;
	std::vector<CRule*> m_ruleList;

public:
	/**
	 * CAzureStorageBlobCleaner
	 *
	 * @author Rahul Naik
	 *
	 * Default constructor
	 *
	 */
	CAzureStorageBlobCleaner();

	/**
	 * loadConfiguration
	 *
	 * Load instance configuration of cleaner instance configuration file. 
	 * Each instance type has a unique configuration JSON format.
	 * This function has a mechanism to parse Azure storage blob specific
	 * configuration and load it in instance object.
	 *
	 * @author Rahul Naik
	 *
	 * @param[in] instanceName           :  Name of the cleaner Azure storage blob instance
	 * @param[in] configurationFilePath  :  Configuration file path
	 *
	 * @return: Return E_SUCCESS if successful. Error code if it fails
	 *
	 */
	int loadConfiguration(
		const std::string& instanceName,
		const std::string& configurationFilePath);

	/**
	 * cleanElgibileObjectList
	 *
	 * Travers the list of all azure storage blob objects in all
	 * containers and identify which objects
	 * are eligible for deletion based on list of rules.
	 * If preview flag is set then display those objects
	 * else delete those objects directly
	 *
	 * @author Rahul Naik
	 *
	 * @param[in] preview         : Preview flag
	 *
	 * @return: Return E_SUCCESS if successful. Error code if it fails
	 *
	 */
	int cleanElgibileObjectList(bool preview = false);

	~CAzureStorageBlobCleaner();
};

