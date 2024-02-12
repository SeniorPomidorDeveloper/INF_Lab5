#include "files_detail.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../structs.h"
#include "my_readline.h"

arr_detail read_detail(char *path_file) {
    FILE *file = fopen(path_file, "r");
    arr_detail details = {NULL, 0};
    if (!file) {
        return details;
    }
    short int result = fscanf(file, "%zd", &(details.len));
    if (!result) {
        return details;
    }
    if (details.len > 0) {
        details.arr = (detail *) malloc(details.len * sizeof(detail));
    }
    for (size_t i = 0; i < details.len; ++i) {
        detail det;
        char *id = file_readLine(file);
        det.name = file_readLine(file);
        result = fscanf(file, "%llu", &(det.count));
        if (strlen(id) == 8 && result) {
            details.arr[i] = det;
            memcpy(details.arr[i].id, id, 9);
        } else {
            i--;
            details.len--;
            free(det.name);
            printf("Данные невозможно прочитать!\n");
        }
        free(id);
    }
    if (details.len > 0) {
        details.arr = (detail *) realloc(details.arr, details.len * sizeof(detail));
    } else {
        free(details.arr);
        details.arr = NULL;
    }
    fclose(file);
    return details;
}

short int write_detail(char *path_file, arr_detail details) {
    FILE *file = fopen(path_file, "w");
    if (!file) {
        return ERROR_OPEN_FILE;
    }
    fprintf(file, "%ld\n", details.len);
    for (size_t i = 0; i < details.len; ++i) {
        detail *det = details.arr + i;
        fprintf(file, "%s\n", (*det).id);
        fprintf(file, "%s\n", (*det).name);
        fprintf(file, "%lld\n", (*det).count);
    }
    fclose(file);
    return OK;
}

short int bin_write_detail(char *path_file, arr_detail details)
{
    FILE *file = fopen(path_file, "wb");
    if (!file) {
        return ERROR_OPEN_FILE;
    }
    fwrite(&(details.len), sizeof(size_t), 1, file);
    for (size_t i = 0; i < details.len; ++i) {
        detail det = details.arr[i];
        size_t len = strlen(det.id);
        fwrite(&len, sizeof(size_t), 1, file);
        fwrite(det.id, sizeof(char), len + 1, file);
        len = strlen(det.name);
        fwrite(&len, sizeof(size_t), 1, file);
        fwrite(det.name, sizeof(char), len + 1, file);
        fwrite(&(det.count), sizeof(unsigned  long int), 1, file);
    }
    fclose(file);
    return OK;
}

arr_detail bin_read_detail(char *path_file)
{
    FILE *file = fopen(path_file, "rb");
    arr_detail details = {NULL, 0};
    if (!file) {
        return details;
    }
    fread(&(details.len), sizeof(size_t), 1, file);
    details.arr = (detail *) malloc(details.len * sizeof(detail));
    for (size_t i = 0; i < details.len; ++i) {
        detail *det = &details.arr[i];
        size_t len;
        fread(&len, sizeof(size_t), 1, file);
        if (len != 8) {
            printf("Данные не возможно прочитать!\n");
            i--;
            details.len--;
            continue;
        }
        fread((*det).id, sizeof(char), len + 1, file);
        fread(&len, sizeof(size_t), 1, file);
        (*det).name = (char *) malloc((len + 1) * sizeof(char));
        fread((*det).name, sizeof(char), len + 1, file);
        fread(&((*det).count), sizeof(unsigned long int), 1, file);
    }
    fclose(file);
    return details;
}