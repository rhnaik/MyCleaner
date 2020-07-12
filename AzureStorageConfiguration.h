#pragma once

#include <string> 
class CAzureStorageConfiguration
{
private:
	std::string m_instanceName;
	std::string m_connectionString;

public:
	CAzureStorageConfiguration(const std::string& instanceName, const std::string& connectionString);

	std::string getInstanceName();

	std::string getConnectionString();
};

