#include "program_2.h"

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "program_1.h"
#include "structs.h"
#include "lib/gets.h"

arr_detail generator(size_t count)
{
    srand(time(NULL));
    arr_detail details = {NULL, count};
    details.arr = (detail *) malloc(count * sizeof(detail));
    for (size_t i = 0; i < count; i++) {
        detail *det = details.arr + i;
        for (size_t j = 0; j < 8; j++) {
            (*det).id[j] = rand() % 127;
        }
        (*det).id[8] = 0;
        size_t len = (size_t) (rand()) % 100;
        (*det).name = (char *) calloc(len + 1, sizeof(char));
        for (size_t j = 0; j < len; j++) {
            (*det).name[j] = (int) (rand()) % 127;
        }
        (*det).count = rand() % 18446744073709551615ULL;
    }
    return details;
}

void *program_2(settings prog_settings)
{
    prog_settings.timing = YES;
    long long int count_mas, count;
    short int result = getLLInt(&count_mas, "Введите кол-во массивов: ", check_pol);
    if (result == EOF) {
        return NULL;
    }
    result = getLLInt(&count, "Введите кол-во эллементов: ", check_pol);
    if (result == EOF) {
        return NULL;
    }
    for (long long int i = 0; i < count_mas; i++) {
        arr_detail details = generator((size_t) count);
        if (!point_2(&details, prog_settings)) {
            for (size_t j = 0; j < details.len; ++j) {
                free(details.arr[j].name);
            }
            free(details.arr);
            return NULL;
        }
        for (size_t j = 0; j < details.len; ++j) {
                free(details.arr[j].name);
        }
        free(details.arr);
    }
    return NULL;
}
