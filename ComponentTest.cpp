#include "ComponentTest.h"
#include "AzureStorageApi.h"
#include "Logger.h"
#include "ErrorCode.h"
#include "Rule.h"
#include "RulePatternCheck.h"
#include "RuleCheckLastModifiedTime.h"

int componentTest()
{
	// Define the connection-string with your values.
	const std::wstring azureStorageConnectionString = U("test_connection_string");

	// Create CAzureStorageApi object
	CAzureStorageApi azureStorageApi(azureStorageConnectionString);

	std::wstring containerName = U("my-sample-container");
	std::wstring sourceFilePath = U("c:\\AZURE_DATA_FILE.doc");
	std::wstring blobName = U("AZURE_DATA_FILE_X");

	// Create blob
	int retval = azureStorageApi.createBlob(containerName, blobName, sourceFilePath);
	if (retval != E_SUCCESS)
	{
		LOG_MESSAGE(M_ERROR, __func__, "Failed to create blob with error:" << retval);
	}

	// Delete blob
	retval = azureStorageApi.deleteBlob(containerName, blobName);
	if (retval != E_SUCCESS)
	{
		LOG_MESSAGE(M_ERROR, __func__, "Failed to delete blob with error:" << retval);
	}

	// Delete blob which matches criteria
	std::time_t startLastModifiedTime = 1594500000;
	std::time_t endLastModifiedTime = 1594505551;

	//CLastModifiedTimeCheckRule rule(RT_LAST_MODIFIED_TIME_CHECK, startLastModifiedTime, endLastModifiedTime);
	CLastModifiedTimeCheckRule rule;
	std::vector<CRule*> ruleList;
	ruleList.push_back(&rule);
	retval = azureStorageApi.deleteBlobsWhichMatchRules(containerName, ruleList);
	if (retval != E_SUCCESS)
	{
		LOG_MESSAGE(M_ERROR, __func__, "Failed to delete blobs in containers with error:" << retval);
	}


	// List Container
	std::vector<std::wstring> containerList;
	retval = azureStorageApi.listContainers(containerList);
	if (retval != E_SUCCESS)
	{
		LOG_MESSAGE(M_ERROR, __func__, "Failed to list containers with error:" << retval);
	}

    return E_SUCCESS;
}
