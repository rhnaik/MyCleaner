#pragma once
#include <vector>

#include <was/storage_account.h>
#include <was/blob.h>

#include "Rule.h"
#include "Object.h"

/**
 * Class for invoking Azure Storage REST APIs
 *
 * @author Rahul Naik
 */
class CAzureStorageApi
{
private:
	azure::storage::cloud_storage_account m_storageAccount;
	azure::storage::cloud_blob_client m_blobClient;

public:
	/**
	 * CAzureStorageApi
	 *
	 * @author Rahul Naik
	 *
	 * Default constructor
	 *
	 */
	CAzureStorageApi();

	/**
	 * CAzureStorageApi
	 *
	 * Constructor
	 *
	 * @author Rahul Naik
	 *
	 * @param[in] storageAcounntConnectionString  :  Connection string used to access storage account
	 *
	 */

	CAzureStorageApi(const std::wstring& storageAcounntConnectionString);

	/**
	 * CreateBlob
	 *
	 * Create blob in container with blob name.
	 * Uses the  content of source file to create a blob
	 *
	 * @author Rahul Naik
	 *
	 * @param[in] containerName  :  Name of the container where blob is to be created
	 * @param[in] blobName       :  Name of the blob to be create
	 * @param[in] sourceFilePath :  Path of the local file which is to be uplaoded
	 *
	 * @return: Return E_SUCCESS if successful. Error code if it fails
	 *
	 */
	int createBlob(
		const std::wstring& containerName,
		const std::wstring& blobName,
		const std::wstring& sourceFilePath);

	/**
	 * listContainers
	 *
	 * List the container in the storage account.
	 *
	 * @author Rahul Naik
	 *
	 * @param[out] containerList  :  Vector containing name of of all containers in list
	 *
	 * @return: Return E_SUCCESS if successful. Error code if it fails
	 *
	 */
	int listContainers(
		std::vector<std::wstring>& containerList);

	/**
	 * listBlobs
	 *
	 * List the blobs in the container.
	 *
	 * @author Rahul Naik
	 *
	 * Input:
	 * @param[in]  containerName  :  Name of the container where blobs are stored
	 * @param[out] blobList       :  Vector containing name of of all blobs in container
	 *
	 * @return: Return E_SUCCESS if successful. Error code if it fails
	 *
	 */
	int listBlobs(
		const std::wstring& containerName,
		std::vector<std::wstring>& blobList);

	/**
	 * deleteBlob
	 *
	 * Delete the blob in the container.
	 *
	 * @author Rahul Naik
	 *
	 * @param[in] containerName  :  Name of the container where blob is stored
	 * @param[in] blobName       :  Name of the blob to be deleted
	 *
	 * @return : Return E_SUCCESS if successful. Error code if it fails
	 *
	 */
	int deleteBlob(
		const std::wstring& containerName,
		const std::wstring& blobName);

	/**
	 * deleteBlobsWhichMatchRules
	 *
	 * Delete blobs which matches configured rule in rules file.
	 *
	 * @author Rahul Naik
	 *
	 * @param[in] containerName  :  Name of the container where blob is stored
	 * @param[in] ruleList       :  List of rules which is used to check eligibility
	 *                              of blob for deletion
	 *
	 * @return : Return E_SUCCESS if successful. Error code if it fails
	 *
	 */
	int deleteBlobsWhichMatchRules(
		const std::wstring& containerName,
		std::vector<CRule*>& rulesList);

	/**
	 * listBlobsWhichMatchRules
	 *
	 * List blobs which matches configured rule in rules file.
	 *
	 * @author Rahul Naik
	 *
	 * @param[in] containerName  :  Name of the container where blob is stored
	 * @param[in] ruleList       :  List of rules which is used to check eligibility
	 *                              of blob for deletion
	 *
	 * @return : Return E_SUCCESS if successful. Error code if it fails
	 *
	 */
	int listBlobsWhichMatchRules(
		const std::wstring& containerName,
		std::vector<CRule*>& ruleList);
};
