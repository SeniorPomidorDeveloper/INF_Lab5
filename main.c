#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "settings.h"
#include "program_1.h"
#include "program_2.h"
#include "structs.h"

#define END_FLAGS -1

enum prog_statuses 
{
    SUCCESSFULLY = 0,
    ARG_ERROR = 1,
    EXECUTION_ERROR = 2
};

int main(int argc, char *argv[])
{
    if (argc == 2) {
        if (!strcmp(argv[1], "--help")) {   // Вызов описания флагов программы
            usage(argv[0]);
            return SUCCESSFULLY;
        }
    }
    char flag = getopt(argc, argv, "p:ts:d:");
    settings prog_settings = {PROGRAM_1, NO, QSORT, LR};   // {<program>, <timing>, <sort_type>, <side_sort>}
    short int flag_index = 1;
    while(flag != END_FLAGS) 
    {
        switch (flag) {
            case 'p':   // Аргумент выбора программы
                if (!check_falg_p(optarg, &prog_settings.program)) {
                    return ARG_ERROR;   // ERROR
                }
                break;
            case 't':   // Аргумент тайминирования
                prog_settings.timing = YES;
                break;
            case 's':   // Аргумент выбора типа сортировки
                if (!check_falg_s(optarg, &prog_settings.sort_type)) {
                    return ARG_ERROR;   // ERROR
                }
                break;
            case 'd':   // Аргумент выбра направления сортировки
                if (!check_falg_d(optarg, &prog_settings.side_sort)) {
                    return ARG_ERROR;   // ERROR
                }
                break;
            case '?':   // Что-то пошло не так
                if (!isdigit(argv[flag_index])) {
                    check_error(argv[flag_index], argv[0]);
                    return ARG_ERROR;   // ERROR
                }
        }
        flag = getopt(argc, argv, "p:ts:d:");
        flag_index++;
    }
    switch (prog_settings.program)
    {
    case PROGRAM_1:
        program_1(prog_settings);
        break;
    case PROGRAM_2:
        program_2(prog_settings);
        break;
    }
    return SUCCESSFULLY;    // Удачное завершение программы
}
