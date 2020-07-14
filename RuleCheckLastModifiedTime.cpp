#include <nlohmann/json.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "RuleCheckLastModifiedTime.h"
#include "ErrorCode.h"
#include "Object.h"

CLastModifiedTimeCheckRule::CLastModifiedTimeCheckRule()
{
}

int CLastModifiedTimeCheckRule::parseRuleJson(std::string& jsonString)
{
	try
	{
		nlohmann::json jsonData = nlohmann::json::parse(jsonString);
		std::string startLastModifiedTime = jsonData["start_last_modified_time"];
		std::string endLastModfiedTime = jsonData["end_last_modified_time"];

		m_startLastModifiedTime = getEpochTimeFromString(startLastModifiedTime);
		m_endLastModifiedTime = getEpochTimeFromString(endLastModfiedTime);
	}
	catch (std::exception& e)
	{
		std::cerr << __func__ << ":Failed to parse JSON rule. Error:" << e.what();
		return E_FAILED_TO_PARSE_JSON_RULE;
	}
	return E_SUCCESS;
}

std::time_t CLastModifiedTimeCheckRule::getEpochTimeFromString(std::string& strTime)
{
	struct std::tm tm;
	std::istringstream iss;
	iss.str(strTime);
	iss >> std::get_time(&tm, "%Y:%m:%d %H:%M:%S");

	return mktime(&tm);
}
bool CLastModifiedTimeCheckRule::checkRule(CObject& object)
{
	if (object.getLastModifiedTime() > m_startLastModifiedTime &&
		object.getLastModifiedTime() < m_endLastModifiedTime)
	{
		std::cerr << "Object Name:[" << object.getObjectName().c_str()
			<< "]. Object last modified time:[" << object.getLastModifiedTime()
			<< "]. Start last modified time:[" << m_startLastModifiedTime
			<< "]. End last modified time:[" << m_endLastModifiedTime << "]. Status:[PASS]" << std::endl;

		return true;
	}
	return false;
}
