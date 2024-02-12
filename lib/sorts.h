#ifndef SORTS_H
#define SORTS_H

#include "../structs.h"
#include <stddef.h>

void comb_sort(detail *, size_t, int(*)(const void *, const void *));
void double_sort(detail *, size_t, int(*)(const void *, const void *));

#endif