#include "AzureStorageApi.h"
#include "ErrorCode.h"

#include <cpprest/filestream.h>  
#include <cpprest/containerstream.h>
#include "Logger.h"

CAzureStorageApi::CAzureStorageApi()
{
}

CAzureStorageApi::CAzureStorageApi(const std::wstring& storageAcounntConnectionString)
{
    // Define the connection-string with your values.
    const utility::string_t storage_connection_string(storageAcounntConnectionString);

    // Retrieve storage account from connection string.
    m_storageAccount = azure::storage::cloud_storage_account::parse(storage_connection_string);

    // Create the blob client.
    m_blobClient = m_storageAccount.create_cloud_blob_client();
}

int CAzureStorageApi::createBlob(
    const std::wstring& containerName,
    const std::wstring& blobName,
    const std::wstring& sourceFilePath)
{
    int retValue = E_SUCCESS;
    
    //TODO:: Input validation
    try
    {
        // Retrieve a reference to a container.
        azure::storage::cloud_blob_container container =
            m_blobClient.get_container_reference(containerName);

        // Retrieve reference to a blob
        azure::storage::cloud_block_blob blockBlob =
            container.get_block_blob_reference(blobName);

        // Create or overwrite blob with contents from a local file.
        blockBlob.upload_from_file(sourceFilePath);
    }
    catch (std::exception& e)
    {
        std::wcerr << "Failed to create blob. Container:[" << containerName
            << "]. Blob:[" << blobName << "]. Source file path:[" 
            << sourceFilePath << "]. Error:" << e.what();
        return E_FAILED;
    }

    BOOST_LOG_TRIVIAL(info) <<
        "Blob created. Container:[" << containerName
        << "]. Blob:[" << blobName << "]. Source file path:[" << sourceFilePath << "]";

    return retValue;
}

int CAzureStorageApi::listContainers(std::vector<std::wstring>& containerList)
{
    try
    {
        // Output URI of each item.
        azure::storage::container_result_iterator endOfResults;

        // Get the list of container using blob client
        for (auto it = m_blobClient.list_containers(); it != endOfResults; ++it)
        {
            containerList.push_back(it->name());
        }
    }
    catch (std::exception& e)
    {
        std::wcerr << "Failed to list containers." << ". Error:" << e.what();
        return E_FAILED;
    }

    return E_SUCCESS;
}

int CAzureStorageApi::listBlobs(
    const std::wstring& containerName,
    std::vector<std::wstring>& blobList)
{
    //TODO:: Input validation
    try
    {
        // Retrieve a reference to a container.
        azure::storage::cloud_blob_container container =
            m_blobClient.get_container_reference(utility::conversions::to_string_t(containerName));

        // Output URI of each item.
        azure::storage::list_blob_item_iterator endOfResults;

        for (auto it = container.list_blobs(); it != endOfResults; ++it)
        {
            if (it->is_blob())
            {
                std::wcout << ("Blob: ") << it->as_blob().uri().primary_uri().to_string() << std::endl;
            }
            else
            {
                std::wcout << ("Directory: ") << it->as_directory().uri().primary_uri().to_string() << std::endl;
            }
        }
    }
    catch (std::exception& e)
    {
        std::wcerr << "Failed to list blobs. Container:[" << containerName << ". Error:" << e.what();
        return E_FAILED;
    }

    return E_SUCCESS;
}

int CAzureStorageApi::deleteBlob(
    const std::wstring& containerName,
    const std::wstring& blobName)
{
    //TODO:: Input validation
    try
    {
        // Retrieve a reference to a previously created container.
        azure::storage::cloud_blob_container container = 
            m_blobClient.get_container_reference(containerName);

        // Retrieve reference to a blob.
        azure::storage::cloud_block_blob blockBlob =
            container.get_block_blob_reference(blobName);

        blockBlob.delete_blob_if_exists_async();
    }
    catch (std::exception& e)
    {
        std::wcerr << "Failed to delete blob. Container:["
            << containerName.c_str() << "]. Blob:[" << blobName.c_str() << "]. Error:" << e.what();
        return E_FAILED;
    }

    BOOST_LOG_TRIVIAL(info) << "Blob deleted. Container:[" << containerName.c_str() << "]. " << "Blob name[" << blobName.c_str() << "].";

    return E_SUCCESS;
}

int CAzureStorageApi::deleteBlobsWhichMatchRules(
    const std::wstring& containerName,
    std::vector<CRule*>& ruleList)
{
    //TODO:: Input validation
    try
    {
        // Retrieve a reference to a container.
        azure::storage::cloud_blob_container container =
            m_blobClient.get_container_reference(containerName);

        // Output URI of each item.
        azure::storage::list_blob_item_iterator endOfResults;

        for (auto it = container.list_blobs(); it != endOfResults; ++it)
        {
            std::wstring blobName = it->as_blob().name().c_str();

            CObject blobObject(blobName, it->as_blob().properties().last_modified().utc_timestamp());
            
            for (auto rule = ruleList.begin(); rule != ruleList.end(); ++rule)
            {
                if ((*rule)->checkRule(blobObject))
                { 
                    deleteBlob(containerName, blobName);
                    BOOST_LOG_TRIVIAL(debug) <<
                        "Blob deleted. Container:[" << containerName.c_str() << "]. " << "Blob name[" << blobName.c_str() << "].";
                }
                else
                {
                    BOOST_LOG_TRIVIAL(info) << "Rule check:[FAIL]. Container:[" << containerName.c_str() << "]. "
                        << "Blob name[" << blobName.c_str() << "].";
                }
            }
        }
    }
    catch (std::exception& e)
    {
        std::wcerr << "Failed to delete blobs. Container:[" << containerName.c_str() << "]. " << " Error:[" << e.what() << "].";
        return E_FAILED;
    }

    return E_SUCCESS;
}

int CAzureStorageApi::listBlobsWhichMatchRules(
    const std::wstring& containerName,
    std::vector<CRule*>& ruleList)
{
    //TODO:: Input validation
    try
    {
        // Retrieve a reference to a container.
        azure::storage::cloud_blob_container container =
            m_blobClient.get_container_reference(containerName);

        // Output URI of each item.
        azure::storage::list_blob_item_iterator endOfResults;

        std::wcout << "------------------------------------------" << std::endl;
        std::wcout << "|       List of eligible blobs            |" << std::endl;
        std::wcout << "------------------------------------------" << std::endl;

        for (auto it = container.list_blobs(); it != endOfResults; ++it)
        {
            std::wstring blobName = it->as_blob().name().c_str();

            CObject blobObject(blobName, it->as_blob().properties().last_modified().utc_timestamp());

            for (auto rule = ruleList.begin(); rule != ruleList.end(); ++rule)
            {
                if ((*rule)->checkRule(blobObject))
                {
                    std::wcout << blobName.c_str() << std::endl;
                    BOOST_LOG_TRIVIAL(info) <<
                        "Eligible Blob. Container:[" << containerName.c_str() << "]. " << "Blob name[" << blobName.c_str() << "].";
                }
                else
                {
                    BOOST_LOG_TRIVIAL(info) <<
                        "Rule check:[FAIL]. Container:[" << containerName.c_str() << "]. " << "Blob name[" << blobName.c_str() << "].";
                }
            }
        }
        std::wcout << "------------------------------------------" << std::endl;
    }
    catch (std::exception& e)
    {
        std::wcerr << "Failed to delete blobs. Container:[" << containerName.c_str() << "]. " << " Error:[" << e.what() << "].";
        return E_FAILED;
    }

    return E_SUCCESS;
}
