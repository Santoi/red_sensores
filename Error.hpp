#ifndef _ERROR_HPP_INCLUDED_
#define _ERROR_HPP_INCLUDED_

#define MAX_ERROR_STR 50
#define MSG_NO_ERROR "There is no error"
#define MSG_ERROR_PREFIX "Error"
#define MSG_ERROR_NULL_PTR "null pointer"
#define MSG_ERROR_FILE_CORRUPTED "file corrupted"
#define MSG_ERROR_NO_MEMORY "not enough memory"
#define MSG_MISSING_DATA_FILE "data file is missing"


typedef enum {
	ST_OK,
	ST_ERROR_NULL_PTR,
	ST_ERROR_FILE_CORRUPTED,
	ST_ERROR_NO_MEMORY,
	ST_NO_DATA_FILE
} status_t;

void PrintError (status_t &st);

#endif