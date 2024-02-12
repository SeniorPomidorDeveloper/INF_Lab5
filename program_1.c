#include "program_1.h"

#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include "lib/my_readline.c"
#include "lib/getstring.h"
#include "lib/gets.h"
#include "lib/files_detail.h"
#include "lib/sorts.h"
#include "lib/compares.h"

#include "settings.h"
#include "structs.h"

unsigned short int check_pol(const long long int num)
{
    return num > 0;
}

unsigned short int str_is_digit(const char *str)
{
    for (size_t i = 0; i < strlen(str); ++i) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

unsigned short int check_id(const char *str)
{
    return strlen(str) == 8 && str_is_digit(str);
}

arr_detail console_input() {
    long long int count_structs;
    arr_detail EOF_struct = {NULL, 0};
    if (getLLInt(&count_structs, "Введите кол-во эллементов массива: ", check_pol) == EOF) {
        return EOF_struct;
    }
    arr_detail arr;
    arr.arr = (detail *) malloc(count_structs * sizeof(detail));
    arr.len = count_structs;
    for (size_t i = 0; i < (size_t) count_structs; ++i) {
        printf("№%ld:\n", i);
        char *id_detail = get_string("  Введите ID детали: ", check_id);
        if (!id_detail) {
            free(arr.arr);
            return EOF_struct;
        }
        for (size_t j = 0; j <= strlen(id_detail); ++j) {
            arr.arr[i].id[j] = id_detail[j];
        } 
        if (!id_detail) {
            free(arr.arr);
            return EOF_struct;    // EOF
        }
        arr.arr[i].name = readLine("  Введите название детали: ");
        if (!arr.arr[i].name) {
            free(arr.arr);
            free(id_detail);
            return EOF_struct;    // EOF
        }
        if (getULLInt(&(arr.arr[i].count), "  Введите кол-во этих деталей: ", standartCheckULLInt) == EOF) {
            free(arr.arr[i].name);
            free(arr.arr);
            free(id_detail);
            return EOF_struct;    // EOF
        }
        free(id_detail);
    }
    return arr;
}

void print_point_1() 
{
    printf("Ввод массива:\n");
    printf("  (a) из стандартного потока ввода («с клавиатуры»)\n");
    printf("  (b) из текстового файла\n");
    printf("  (c) из бинарного файла\n");
}

unsigned short int check_point_1(const char *str)
{
    return str[1] == 0 && strstr("abc", str);
}

int point_1(arr_detail *arr) 
{
    print_point_1();
    char *point = get_string("Как вы хотите вводить данные в массив: ", check_point_1);
    if (!point) {
        return 0;
    }
    char *path;
    switch (point[0])
    {
        case 'a':
            *arr = console_input();
            if (!((*arr).len)) {
                free(point);
                return 0;
            } 
            break;
        case 'b':
            path = readLine("Введите путь до файла: ");
            if (!path) {
                free(point);
                return 0;
            }
            *arr = read_detail(path);
            free(path);
            if (!(*arr).arr) {
                printf("Файл не удалось прочитать!\n");
                free((*arr).arr);
                free(point);
                return 0;
            }
            break;
        case 'c':
            path = readLine("Введите путь до файла: ");
            if (!path) {
                free(point);
                return 0;
            }
            *arr = bin_read_detail(path);
            free(path); 
            if (!(*arr).arr) {
                free((*arr).arr);
                printf("Файл не удалось прочитать!\n");
                return 0;
            }
            break;
    }
    free(point);
    return 1;
}

void print_point_2() 
{
    printf("Поля структуры:\n");
    printf("  (a) id\n");
    printf("  (b) name\n");
    printf("  (c) кол-во\n");
}

int point_2(arr_detail *arr, settings prog_settings)
{
    print_point_2();
    char *point = get_string("По какому полю вы хотите сортировать: ", check_point_1);
    if (!point) {
        return 0;
    }
    int (*compare) (const void *, const void *);
    switch (point[0]) 
    {
        case 'a':
            if (prog_settings.side_sort == LR) {
                compare = id_compare;
            } else {
                compare = id_rcompare;
            }
            break;
        case 'b':
            if (prog_settings.side_sort == LR) {
                compare = name_compare;
            } else {
                compare = name_rcompare;
            }   
            break;
        case 'c':
            if (prog_settings.side_sort == LR) {
                compare = count_compare;
            } else {
                compare = count_rcompare;
            }
            break;
    }
    free(point);
    clock_t start;
    switch (prog_settings.sort_type) 
    {
        case QSORT:
        	printf("qsort\n");
            start = clock();
            qsort((*arr).arr, (*arr).len, sizeof(detail), compare);
            if (prog_settings.timing == YES) {
                printf("Waiting time %0.16lf ms\n", (double) (clock() - start) / CLOCKS_PER_SEC);
            }
            break;
        case BRUSH_SORT:
        	printf("comb sort\n");
            start = clock();
            comb_sort((*arr).arr, (*arr).len, compare);
            if (prog_settings.timing == YES) {
                printf("Waiting time %0.16lf ms\n", (double) (clock() - start) / CLOCKS_PER_SEC);
            }
            break;
        case CHOICE_SORT:
        	printf("D sort\n");
            start = clock();
            double_sort((*arr).arr, (*arr).len, compare);
            if (prog_settings.timing == YES) {
                printf("Waiting time %0.16lf ms\n", (double) (clock() - start) / CLOCKS_PER_SEC);
            }
            break;
    }
    return 1;
}

void print_point_3() 
{
    printf("Вывод массива:\n");
    printf("  (a) в стандартный поток ввода («с клавиатуры»)\n");
    printf("  (b) в текстовый файл\n");
    printf("  (c) в бинарный файл\n");
}

int point_3(arr_detail *arr)
{
    print_point_3();
    char *point = get_string("Куда вы хотите вывести результат: ", check_point_1);
    if (!point) {
        free(point);
        return 0;
    }
    short int result;
    char *path;
    switch (point[0]) 
    {
        case 'a':
            for (size_t i = 0; i < (*arr).len; ++i) {
                detail *det = (*arr).arr + i;
                printf("№%ld:\n", i);
                printf("id: %s\n", (*det).id);
                printf("name: %s\n", (*det).name);
                printf("count: %llu\n", (*det).count);
            }
            break;
        case 'b':
            path = readLine("Введите путь до файла: ");
            result = write_detail(path, *arr);
            free(path);
            if (!result) {
                printf("Не удалось записать в файл!");
                return 0;
            }
            break;
        case 'c':
            path = readLine("Введите путь до файла: ");
            result = bin_write_detail(path, *arr);
            free(path);
            if (!result) {
                printf("Не удалось записать в файл!");
                return 0;
            }
            break;
    }
    free(point);
    return 1;
}    

void *program_1(settings prog_settings)
{
    arr_detail arr;
    if (!(point_1(&arr))) {
        return NULL;
    }
    if (!point_2(&arr, prog_settings)) {
        for (size_t i = 0; i < arr.len; ++i) {
            free(arr.arr[i].name);
        }
        free(arr.arr);
        return NULL;
    }
    if (!point_3(&arr)) {
        for (size_t i = 0; i < arr.len; ++i) {
            free(arr.arr[i].name);
        }
        free(arr.arr);
        return NULL;
    };
    for (size_t i = 0; i < arr.len; ++i) {
        free(arr.arr[i].name);
    }
    free(arr.arr);
    return NULL;
}
