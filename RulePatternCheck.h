#pragma once

#include <string>
#include "Rule.h"

class CPatternCheckRule : public CRule
{
private:
	std::string m_pattern;

public:
	/**
	 * CPatternCheckRule
	 *
	 * Default constructor
	 *
	 * @author Rahul Naik
	 */
	CPatternCheckRule();

	/**
	 * parseRuleJson
	 *
	 * Parse the input JSON string and get the file name matching
	 * pattern
	 *
	 * @param[in] jsonString  : JSON string from rule configuration file.
	 *
	 * @return: Return E_SUCCESS if successful. Error code if it fails
	 */
	int parseRuleJson(std::string& jsonString);

	/**
	 * checkRule
	 *
	 * Checks that is given object has a name matching to
	 * configured pattern
	 *
	 * @param[in] object  : Object on which rule need to be checked.
	 *
	 * @return: Return E_SUCCESS if successful. Error code if it fails
	 */
	bool checkRule(CObject& object);
};