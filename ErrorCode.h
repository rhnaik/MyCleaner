#pragma once


/**
 * List of error codes
 */
#define E_SUCCESS                                     0
#define E_FAILED                                      1

#define E_BASE_ERROR_CODE                             1000
#define E_FAILED_TO_PARSE_COMMAND_LINE_ARGUMENTS      E_BASE_ERROR_CODE + 1;
#define E_FAILED_TO_GET_INSTANCE_CONF_FROM_FILE       E_BASE_ERROR_CODE + 2;
#define E_FAILED_TO_PARSE_JSON_RULE                   E_BASE_ERROR_CODE + 3;
#define E_INVALID_RULE_TYPE                           E_BASE_ERROR_CODE + 4;
#define E_MAX_ERROR_CODE                              E_INVALID_RULE_TYPE
