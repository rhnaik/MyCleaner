# MyCleaner

In a cloud test environment, engineers create test data and forget to delete it after they are done with testing. In cloud environment, as everything is chargable,
the stale data may incur lots of charges. Especially in case of snapshots of VM and database instances.

This utility helps user to cleanup test data which is no longer required. Right now, this utility has a support for Azure storage blobs. 
This application can easily extended for other cloud vendors, cloud objects, array vendors and file systems.

The user can delete files by defining variaous combination of data filter rules in JSON file. Right now, this utility support 2 types of rule

1. Last modified time:
   User can define start_last_modified_time and end_last_modified_time in rule configuration. When utility will run,
   it will delete all objects which has last modified time between provided start_last_modified_time and end_last_modified_time

2. Pattern match:
   User can specify regex pattern in rule configuration. When utility will run, it will delete all objects for which pattern matches 
   with object name.
   
This utility also support preview option. Based on rule configuration,  user can view list of all eligible objects for deleteion.

Following is the command line usage of MyCleaner utility
```
# Usage:
Options:
  --help                                Help Screen
  --config_file_path arg (=c:\my_cleaner_config.json)
                                        Instance Configuration file path
  --rules_file_path arg (=c:\my_cleaner_rules.json)
                                        Cleanup rules file path
  --instance_name arg (=MY_INSTANCE)    Name of cleaner instance
  --log_file_path arg (=c:\my_cleaner.log)
                                        Log file path
  --instance_type arg (=0)              Type of cleaner instance.
                                        1-Azure Blob cleaner, 2-File system
                                        cleaner
  --preview                             preview
  ```
  
  Following is the sample configuration json file
  # Sample configuration JSON file
  ```
  {
    "instances": [
      {
        "azure_storage_blob_instances": [
          {
            "configuration": {
              "connection_string": "<connection_string>"
            },
            "instance_name": "my_azure_storage_blob"
          }
        ]
      }
    ]
  }
 ```
 
Following is the sample rule json file

# Sample rules JSON file
```
{
  "rules" :
  [
    {
      "rule_type": "check_last_modified_time",
      "rule_config": {
        "start_last_modified_time": "2020:07:13 09:27:06",
        "end_last_modified_time": "2020:07:13 09:28:06"
      }
    },
    {
      "rule_type": "check_name_regex",
      "rule_config": {
        "pattern": "AZURE*"
      }
    }
  ]
}
```


