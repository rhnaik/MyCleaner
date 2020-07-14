#pragma once

#include <vector>
#include "Rule.h"
#include "Object.h"

/**
 * Instance type
 */
constexpr auto INSTANCE_TYPE_INVALID = 0;
constexpr auto INSTANCE_TYPE_AZURE_BLOB_CLEANER = 1;
constexpr auto INSTANCE_TYPE_FILE_SYSTEM_CLEANER = 2;

// Always update this value whenever new instance type is added
constexpr auto INSTANCE_TYPE_MAX = INSTANCE_TYPE_FILE_SYSTEM_CLEANER;


class CMyCleaner
{
private:
	std::vector<CRule> m_ruleList;
	std::string m_instanceName;

public:
	/**
	 * loadConfiguration
	 *
	 * Pure virtual function.
	 * Load instance configuration of cleaner instance configuration file.
	 * Each instance type has a unique configuration JSON format.
	 * This function should have a mechanism to parse instance type specific
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
	virtual int loadConfiguration(
		const std::string& instanceName,
		const std::string& configurationFilePath) = 0;

	/**
	 * cleanElgibileObjectList
	 *
	 * Travers the list of all objects and identify which objects
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
	virtual int cleanElgibileObjectList(bool preview = false) = 0;

	/**
	 * intitializeRulesList
	 *
	 * Parse the JSON file of rules and populate it in rules list
	 *
	 * Each rule type has a unique rule configuration JSON format.
	 * Based on rule type, it creates different rule class object
	 * using factory function. Invoke the parse configuration function of
	 * each rule class to get each rule specific configuration.
	 *
	 * @author Rahul Naik
	 *
	 * @param[in] rulesListFilePath      :  Rules file path
	 *
	 * @return: Return E_SUCCESS if successful. Error code if it fails
	 *
	 */
	virtual int intitializeRulesList(const std::string& rulesListFilePath);

	/**
	 * setCleanerInstanceName
	 *
	 * Set cleaner instance name
	 *
	 * @author Rahul Naik
	 *
	 * @param[in] instanceName       : Name of cleaner instance
	 *
	 * @return: Return none
	 *
	 */
	virtual void setCleanerInstanceName(const std::string& instanceName);
};

/**
 * createMyCleanerInstance
 *
 * Based on input instance type create the cleaner instance object
 * @author Rahul Naik
 *
 * @param[in] cleanerInstanceType      :  Type of cleaner instance
 *
 * @return:  If successful, Pointer child class instance  else nullptr
 *
 */
CMyCleaner* createMyCleanerInstance(int cleanerInstanceType);

