#pragma once

#include <vector>

#include "MyCleaner.h"
#include "AzureStorageConfiguration.h"

class CAzureStorageBlobCleaner :
    public CMyCleaner
{
private:
	std::vector<CAzureStorageConfiguration> m_configurationList;
	std::string m_eligibileObjectListFilePath;

public:
	int readConfiguration() = 0;
	int intitializeRuleList() = 0;
	int getEligibleObjectList() = 0;
	int displayEligibleObjectList() = 0;
	int cleanElgibileObjectList() = 0;
};

