#include "compares.h"

#include <string.h>

#include "../structs.h"

int count_compare(const void *det_1, const void *det_2)
{
    const detail *detl_1 = (detail *) det_1;
    const detail *detl_2 = (detail *) det_2;
    return (*detl_1).count > (*detl_2).count;
}

int id_compare(const void *det_1, const void *det_2) 
{
    const detail *detl_1 = (detail *) det_1;
    const detail *detl_2 = (detail *) det_2;
    return strcmp((*detl_1).id, (*detl_2).id) > 0;
}

int name_compare(const void *det_1, const void *det_2) 
{
    const detail *detl_1 = (detail *) det_1;
    const detail *detl_2 = (detail *) det_2;
    return strcmp((*detl_1).name, (*detl_2).name) > 0;
}

int count_rcompare(const void *det_1, const void *det_2)
{
    const detail *detl_1 = (detail *) det_1;
    const detail *detl_2 = (detail *) det_2;
    return (*detl_1).count < (*detl_2).count;
}

int id_rcompare(const void *det_1, const void *det_2) 
{
    const detail *detl_1 = (detail *) det_1;
    const detail *detl_2 = (detail *) det_2;
    return strcmp((*detl_1).id, (*detl_2).id) < 0;
}

int name_rcompare(const void *det_1, const void *det_2) 
{
    const detail *detl_1 = (detail *) det_1;
    const detail *detl_2 = (detail *) det_2;
    return strcmp((*detl_1).name, (*detl_2).name) < 0;
}