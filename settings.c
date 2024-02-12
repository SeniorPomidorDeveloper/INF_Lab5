#include "settings.h"

#include <stdio.h>
#include <string.h>

void usage(char *prog_name) {
    printf("USAGE: %s [-p:value] [-t] [-s:value] [-d:value]\n", prog_name);
    printf("  -p:\n");
    printf("    1 - first program\n");
    printf("    2 - second program\n");
    printf("  -t - timing\n");
    printf("  -s:\n");  
    printf("    1 - brush sort\n");
    printf("    2 - choice sort\n");
    printf("    3 - qsort\n");
    printf("  -d:\n");
    printf("    A - sort in ascending order\n");
    printf("    D - sort in descending order\n");

}

void help_message() 
{
    printf("Set the --help flag to see which flags are available.\n");
}

void bad_arg_message(char flag, char *value)
{
    printf("Flag -%c has no value %s!", flag, value);
    help_message();
}

short int check_falg_p(char *optarg, unsigned short int *value)
{
    if (!strcmp(optarg, "1")) {
        *value = PROGRAM_1;
    } else if (!strcmp(optarg, "2")) {
        *value = PROGRAM_2;
    } else {
        bad_arg_message('p', optarg);
        return 0;   // ERROR
    }
    return 1;
}

short int check_falg_s(char *optarg, unsigned short int *value)
{
    if (!strcmp(optarg, "1")) {
        *value = BRUSH_SORT;
    } else if (!strcmp(optarg, "2")) {
        *value = CHOICE_SORT;
    } else if (!strcmp(optarg, "3")) {
        *value = QSORT;
    } else {
        bad_arg_message('s', optarg);
        return 0;   // ERROR
    }
    return 1;
}

short int check_falg_d(char *optarg, short int *value)
{
    if (!strcmp(optarg, "A")) {
        *value = LR;
    } else if (!strcmp(optarg, "D")) {
        *value = RL;
    } else {
        bad_arg_message('d', optarg);
        return 0;   // ERROR
    }
    return 1;
}

void check_error(char *optarg, char *prog_name)
{
    if (optarg[2] == 0 && strstr("ptsd", optarg + 1)) {
        printf("The -%c flag needs an argument!\n", optarg[1]);
        help_message();
    } else {
        printf("Program %s does not have a flag %s!\n", prog_name, optarg);
        help_message();
    }
}
