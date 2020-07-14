#include <nlohmann/json.hpp>
#include <iomanip>
#include <iostream>
#include <regex>

#include "RulePatternCheck.h"
#include "ErrorCode.h"
#include "Object.h"

CPatternCheckRule::CPatternCheckRule()
{
}

int CPatternCheckRule::parseRuleJson(std::string& jsonString)
{
	try
	{
		nlohmann::json jsonData = nlohmann::json::parse(jsonString);
		std::string pattern = jsonData["pattern"];
		m_pattern = pattern;
	}
	catch (std::exception& e)
	{
		std::cerr << __func__ << ": Failed to parse JSON rule. Error:" << e.what();
		return E_FAILED_TO_PARSE_JSON_RULE;
	}
	return E_SUCCESS;
}

bool CPatternCheckRule::checkRule(CObject& object)
{
	std::regex ruleRegex(m_pattern);
	std::string objectName(object.getObjectName().begin(), object.getObjectName().end());

	if (regex_match(objectName, ruleRegex))
	{
		std::cout << __func__ << ": Pattern:[" << m_pattern << "] with name:[" << objectName << std::endl;
		return true;
	}

	return false;
}
