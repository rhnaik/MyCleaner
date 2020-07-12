#pragma once
#include <vector>

// Azure storage header filesss
#include <was/storage_account.h>
#include <was/blob.h>

#include "Rule.h"
#include "Object.h"

class CAzureStorageApi
{
private:
	azure::storage::cloud_storage_account m_storageAccount;
	azure::storage::cloud_blob_client m_blobClient;

public:
	/**
	 * CAzureStorageApi
	 * 
	 * Constructor
	 *
	 * Input:
	 * @param storageAcounntConnectionString  :  Connection string used to access storage account  
	 */

	CAzureStorageApi(const std::wstring& storageAcounntConnectionString);

	/**
	 * CreateBlob
	 *
	 * Create blob in container with blob name.
	 * Uses the  content of source file to create a blob 
	 *
	 * Input:
	 * @param containerName  :  Name of the container where blob is to be created
	 * @param blobName       :  Name of the blob to be create
	 * @param sourceFilePath :  Path of the local file which is to be uplaoded
	 *
	 * Output:
	 * @param Return 0 if successful. Error code if it fails
	 *
	 */
	int createBlob(
		const std::wstring& containerName,
		const std::wstring& blobName,
		const std::wstring& sourceFilePath);

	/**
	 * listContainer
	 *
	 * List the container in the storage account.
	 *
	 * Input:
	 * @param containerList  :  Vector containing name of of all containers in list
	 *
	 * Output:
	 * @param Return 0 if successful. Error code if it fails
	 *
	 */
	int listContainer(
		std::vector<std::wstring>& containerList);

	/**
	 * listBlobs
	 *
	 * List the blobs in the container.
	 *
	 * Input:
	 * @param containerName  :  Name of the container where blobs are stored
	 * @param blobList       :  Vector containing name of of all blobs in container
	 *
	 * Output:
	 * @param Return 0 if successful. Error code if it fails
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
	 * Input:
	 * @param containerName  :  Name of the container where blob is stored
	 * @param blobName       :  Name of the blob to be deleted
	 *
	 * Output:
	 * @param Return 0 if successful. Error code if it fails
	 *
	 */
	int deleteBlob(
		const std::wstring& containerName,
		const std::wstring& blobName);

	int deleteBlobsWhichMatchRules(
		const std::wstring& containerName,
		std::vector<CRule*>& ruleList);

};

