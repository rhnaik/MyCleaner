#include "AzureStorageConfiguration.h"

CAzureStorageConfiguration::CAzureStorageConfiguration(const std::string& instanceName, const std::string& connectionString)
	: m_instanceName(instanceName), m_connectionString(connectionString)
{
}

std::string CAzureStorageConfiguration::getInstanceName()
{
	return  m_instanceName;
}

std::string CAzureStorageConfiguration::getConnectionString()
{
	return m_connectionString;
}