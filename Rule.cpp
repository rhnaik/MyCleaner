#include "Rule.h"
#include "Logger.h"
#include <iostream>

CRule::CRule(ERuleType ruleType)
	: m_ruleType(ruleType)
{
	
}

CLastModifiedTimeCheckRule::CLastModifiedTimeCheckRule(
	ERuleType ruleType,
	std::time_t& startLastModifiedTime,
	std::time_t& endLastModifiedTime) :
	CRule(ruleType),
	m_startLastModifiedTime (startLastModifiedTime),
	m_endLastModifiedTime(endLastModifiedTime)
{
}

int CLastModifiedTimeCheckRule::parseRuleJson(std::string& jsonString)
{
	return 0;
}

bool CLastModifiedTimeCheckRule::checkRule(CObject& object)
{
	if (object.getLastModifiedTime() > m_startLastModifiedTime &&
		object.getLastModifiedTime() < m_endLastModifiedTime)
	{
		std::cout << "Object Name:[" << object.getObjectName().c_str()
			<< "]. Object last modified time:[" << object.getLastModifiedTime() 
			<< "]. Start last modified time:[" << m_startLastModifiedTime
			<< "]. End last modifed time:[" << m_endLastModifiedTime << "]. Status:[PASS]" << std::endl;

		return true;
	}
	return false;
}
