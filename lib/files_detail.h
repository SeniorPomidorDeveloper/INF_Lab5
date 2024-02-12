#ifndef FILES_DETAIL_H
#define FILES_DETAIL_H

#include "../structs.h"

enum file_statuses
{
    ERROR_OPEN_FILE = 0,
    OK = 1
};

short int bin_write_detail(char *, arr_detail);
arr_detail bin_read_detail(char *);
arr_detail read_detail(char *);
short int write_detail(char *, arr_detail);

#endif