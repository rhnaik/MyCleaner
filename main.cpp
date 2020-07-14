

#include <iostream>
#include "MyCleaner.h"
#include "Logger.h"
#include "ErrorCode.h"
#include "CommandLineOptionsManager.h"

int main(int argc, const char*argv[])
{
    try
    {
        int retval = E_SUCCESS;

        // Parse input arguments
        CCommandLineOptionsManager cliOptionsManager;
        retval = cliOptionsManager.initializeArgumentValues(argc, argv);
        if (retval != E_SUCCESS)
        {
            std::cerr << "Failed to initialize arguments. Error:[" << retval << "]";
            exit(retval);
        }

        // Validate arguments
        retval = cliOptionsManager.validateArguments();
        if (retval != E_SUCCESS)
        {
            std::cerr << "Failed to validate arguments. Error:[" << retval << "]";
            exit(retval);
        }

        // Factory function to get Cleaner instance
        std::unique_ptr<CMyCleaner> myCleanerInstance(createMyCleanerInstance(cliOptionsManager.getCleanerInstanceType()));

        // Load configuration of specific instance from configuration file
        retval = myCleanerInstance->loadConfiguration(
            cliOptionsManager.getInstanceName(),
            cliOptionsManager.getConfigFilePath());

        if (retval != E_SUCCESS)
        {
            std::cerr << "Failed to read configuration for instance. Error:[" << retval << "]";
            exit(retval);
        }

        // Initialize rule list from rules JSON file
        retval = myCleanerInstance->intitializeRulesList(cliOptionsManager.getRulesFilePath());
        if (retval != E_SUCCESS)
        {
            std::cerr << "Failed to read configuration for instance. Error:[" << retval << "]";
            exit(retval);
        }

        // Cleanup objects based on configures rules
        retval = myCleanerInstance->cleanElgibileObjectList(cliOptionsManager.getPreviewFlag());
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception caught. Error:[" << e.what() << "]";
        exit(E_FAILED);
    }
    
	return E_SUCCESS;
}
