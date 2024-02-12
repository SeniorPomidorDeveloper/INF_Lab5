#ifndef SETTINGS_H
#define SETTINGS_H

enum setting_optinons 
{
    PROGRAM_1 = 0,
    PROGRAM_2 = 1,
    YES = 1,
    NO = 0,
    BRUSH_SORT = 0,
    CHOICE_SORT = 1,
    QSORT = 2,
    LR = -1,
    RL = 1
};

typedef struct settings 
{
    unsigned short int program;    // Выбор программы
    unsigned short int timing;    // Таймирование
    unsigned short int sort_type;  // Выбор типа сортировки
    short int side_sort;  // Выбор направление сортирвки
} settings;

void usage(char *);
void help_message();

short int check_falg_p(char *, unsigned short int *);
short int check_falg_s(char *, unsigned short int *);
short int check_falg_d(char *, short int *);
void check_error(char *, char *);

#endif