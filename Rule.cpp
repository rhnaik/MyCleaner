
#include <iostream>

#include "Rule.h"
#include "Logger.h"
#include "ErrorCode.h"
#include "RulePatternCheck.h"
#include "RuleCheckLastModifiedTime.h"

CRule* createRuleObject(ERuleType ruleType)
{
	switch (ruleType)
	{
	case RT_PREFIX_CHECK:
		return new CPatternCheckRule();

	case RT_LAST_MODIFIED_TIME_CHECK:
		return new CLastModifiedTimeCheckRule();

	default:
		return nullptr;
	}
}

CRule::CRule()
{
}