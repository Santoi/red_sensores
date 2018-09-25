#include <iostream>
using namespace std;

#include "Error.hpp"

void PrintError (status_t &st) {
	static string error [MAX_ERROR_STR] = {
		MSG_NO_ERROR,
		MSG_ERROR_NULL_PTR,
		MSG_ERROR_FILE_CORRUPTED,
		MSG_ERROR_NO_MEMORY,
		MSG_MISSING_DATA_FILE
	};

	if (st != ST_OK)
		cerr << MSG_ERROR_PREFIX
		     << ": "
		     << error[st]
		     << endl;
}