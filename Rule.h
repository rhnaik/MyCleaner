#pragma once

#include <string>

#include "Object.h"

enum ERuleType
{
	RT_PREFIX_CHECK = 1,
	RT_LAST_MODIFIED_TIME_CHECK,
	RT_BLOB_TYPE_CHECK
};

class CRule
{
private:
	ERuleType m_ruleType;
	std::string m_jsonString;

public:
	ERuleType getRuleType()
	{
		return m_ruleType;
	}

	CRule(ERuleType ruleType);
	virtual int parseRuleJson(std::string& jsonString) = 0;
	virtual bool checkRule(CObject& object) = 0;
};

class CLastModifiedTimeCheckRule : public CRule
{
private:
	std::time_t m_startLastModifiedTime;
	std::time_t m_endLastModifiedTime;

public:
	CLastModifiedTimeCheckRule(
		ERuleType ruleType,
		std::time_t& startLastModifiedTime,
		std::time_t& endLastModifiedTime);

	int parseRuleJson(std::string& jsonString);

	bool checkRule(CObject& object);
};