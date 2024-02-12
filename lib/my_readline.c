#include "my_readline.h"

#include <stdlib.h>
#include <string.h>

char *readLine(const char *promt)
{
    char *str = (char *) malloc((BUF_SIZE + 1) * sizeof(char));
    str[0] = 0;
    short int result;
    printf("%s", promt);
    scanf("%*[\n]");
    do {
        result = scanf("%10[^\n]", str + strlen(str));
        if (result == EOF) {
            free(str);
            return NULL;
        }
        if (result) {
            str = (char *) realloc(str, (strlen(str) + BUF_SIZE + 1) * sizeof(char));
        }
    } while(result);
    str = (char *) realloc(str, (strlen(str) + 1) * sizeof(char));
    return str;
}

char *file_readLine(FILE *file)
{
    char *str = (char *) malloc((BUF_SIZE + 1) * sizeof(char));
    str[0] = 0;
    short int result;
    fscanf(file, "%*[\n]");
    do {
        result = fscanf(file, "%10[^\n]", str + strlen(str));
        if (result == EOF) {
            free(str);
            return NULL;
        }
        if (result) {
            str = (char *) realloc(str, (strlen(str) + BUF_SIZE + 1) * sizeof(char));
        }
    } while(result);
    str = (char *) realloc(str, (strlen(str) + 1) * sizeof(char));
    return str;
}