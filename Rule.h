#pragma once

#include <string>
#include <map>

#include "Object.h"

/**
 * Enum for types of rule
 */
enum ERuleType
{
	RT_PREFIX_CHECK = 1,
	RT_LAST_MODIFIED_TIME_CHECK
};

/**
 * Map for getting integer value for string rule type
 */
static std::map<std::string, ERuleType> MapRuleStringToRuleType
{
	{"check_name_regex", RT_PREFIX_CHECK},
	{"check_last_modified_time", RT_LAST_MODIFIED_TIME_CHECK}
};

/**
 * Class for defining rule to be checked on object
 * and identify that it is eligible for deletion or not
 */
class CRule
{
public:
	/**
	 * CRule
	 *
	 * Default constructor
	 *
	 * @author Rahul Naik
	 */
	CRule();

	/**
	 * parseRuleJson
	 *
	 * Pure virtual function
	 * Parse the input JSON string and get the  configuration for rule.
	 *
	 * @param[in] jsonString  : JSON string from rule configuration file.
	 *
	 * @return: Return E_SUCCESS if successful. Error code if it fails
	 */
	virtual int parseRuleJson(std::string& jsonString) = 0;

	/**
	 * checkRule
	 *
	 * Pure virtual function
	 * Check the rule configuration on input object
	 *
	 * @param[in] object  : Object of CObject which is need to be evaluated.
	 *
	 * @return: Return E_SUCCESS if successful. Error code if it fails
	 */
	virtual bool checkRule(CObject& object) = 0;
};

/**
 * createRuleObject
 * Factory function for creating rule object
 *
 * @param[in] ruleType :  Rule type of rule of type ERuleType
 * 
 * @return: If successful, Pointer to child rule type else nullptr;
 */
CRule* createRuleObject(ERuleType ruleType);