#include "sorts.h"
#include <stdio.h>
#include <stdlib.h>

#include "../structs.h"

#include "compares.h"

void comb_sort(detail *buf, size_t num, int(*compare) (const void *, const void *))
{
    if (buf && num) {
        size_t jump = num; 
        int swap = 1;
        size_t j;
        while (jump > 1 || swap) {
            jump = (int) (jump / 1.24733);
            if (jump < 1) {
                jump = 1;
            } 
            swap = 0;
            for (size_t i = 0; i < num - jump; ++i) {
                j = i + jump;
                if (compare(buf + i, buf + j)) {
                    detail val_buf = buf[i];
                    buf[i] = buf[j];
                    buf[j] = val_buf;
                    swap = 1;
                }
            }
       }
    }
}

void double_sort(detail *buf, size_t num, int(*compare) (const void *, const void *))
{
    size_t range_l = 0;
    size_t range_r = num;
    size_t min_index = 0;
    size_t max_index = 0;
    while (range_r - range_l > 1) {
        for(size_t i = range_l; i < range_r; ++i) {
            if (compare(buf + i, buf + max_index)) {
                max_index = i;  
            }
            if (compare(buf + min_index, buf + i)) {
                min_index = i;
            }
        }
        detail max_buf = buf[max_index];
        if (min_index == range_r - 1) {
            min_index = max_index;
        }
        buf[max_index] = buf[range_r - 1];
        detail min_buf = buf[min_index];
        buf[min_index] = buf[range_l];
        buf[range_r - 1] = max_buf;
        buf[range_l] = min_buf;
        range_r--;
        range_l++;
        max_index = range_l;
        min_index = range_l;
    }
}