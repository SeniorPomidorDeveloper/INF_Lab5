#include "getstring.h"

#include <stdio.h>
#include <stdlib.h>

#include "my_readline.h"

char *get_string(char *promt, unsigned short int (*check_function)(const char *check_str))
{
    char *str = NULL;
    unsigned short int check;
    do {
        free(str);
        str = readLine(promt);
        if (!str) {
            return str; // EOF
        }
        check = !check_function(str);
        if (check) {
            printf("Вы ввели значение некорректно!\n");
            printf("Попробуйте ещё раз.\n");
        }
    } while (check);
    return str;
}