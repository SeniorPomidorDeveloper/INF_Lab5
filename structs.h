#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>

typedef struct detail 
{
    char id[9];
    char *name;
    unsigned long long int count;
} detail;

typedef struct arr_detail
{
    detail *arr;
    size_t len;
}arr_detail;

#endif
