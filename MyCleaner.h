#pragma once

#include <vector>
#include "Rule.h"
#include "Object.h"

#define JSON_CONFIG_FILE_PATH  "c:\\my_cleaner_config.json"

class CMyCleaner
{
private:
	std::vector<CRule> m_ruleList;

public:
	virtual int readConfiguration() = 0;

	virtual int intitializeRuleList() = 0;

	virtual int getEligibleObjectList() = 0;

	virtual int displayEligibleObjectList() = 0;

	virtual int cleanElgibileObjectList() = 0;
};

