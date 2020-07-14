#pragma once

#include <string>
#include <ctime>

#include "Rule.h"

class CLastModifiedTimeCheckRule : public CRule
{
private:
	std::time_t m_startLastModifiedTime;
	std::time_t m_endLastModifiedTime;

public:
	/**
	 * CLastModifiedTimeCheckRule
	 *
	 * Default constructor
	 *
	 * @author Rahul Naik
	 */
	CLastModifiedTimeCheckRule();

	/**
	 * parseRuleJson
	 *
	 * Parse the input JSON string and get the start last modified time
	 * and end last modified time.
	 *
	 * @param[in] jsonString  : JSON string from rule configuration file.
	 *
	 * @return: Return E_SUCCESS if successful. Error code if it fails
	 */
	int parseRuleJson(std::string& jsonString);

	/**
	 * checkRule
	 *
	 * Checks that is given object has last modified time between
	 * start last modified time and end last modified time.
	 *
	 * @param[in] object  : Object on which rule need to be checked.
	 *
	 * @return: Return E_SUCCESS if successful. Error code if it fails
	 */
	bool checkRule(CObject& object);

	/**
	 * getEpochTimeFromString
	 *
	 * Get the UNIX time-stamp for provided input day time e.g. 2020:07:13 09:27:06
	 *
	 * @param[in] strTime  : String with day time value. E.g. 2020:07:13 09:27:06
	 *
	 * @return: Return E_SUCCESS if successful. Error code if it fails
	 */
	static std::time_t getEpochTimeFromString(std::string& strTime);
};

