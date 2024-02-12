#include "gets.h"
#include <stdio.h>

unsigned short int standartCheckLLInt(const long long int num) {
	return num || 1;
}

unsigned short int standartCheckULLInt(const unsigned long long int num) {
	return num || 1;
}

short int getLLInt(long long int *num, const char *message, unsigned short int (*checkFunction)(const long long int num))
{
	short int result;
	int point = 0;
	do {
		printf("%s", message); 
		result = scanf("%lld.%d", num, &point);
		if (result == 1 && point == 0) {
			if (!checkFunction(*num)) {
				printf("Вы ввели число, неподходящее под условие!\n");
				printf("Попробуйте ещё раз.\n");
				result = 0;
			}
		} else if (result == 0 || result == 2 || point != 0) {
			printf("Вы ввели целое число некорректно!\n");
			printf("Попробуйте ещё раз.\n");
			result = 0;
			point = 0;
		}
		scanf("%*[^\n]");
	} while(result == 0);
	return result;
}

short int getULLInt(unsigned long long int *num, const char *message, unsigned short int (*checkFunction)(const unsigned long long int num))
{
	short int result;
	int point = 0;
	do {
		printf("%s", message); 
		result = scanf("%llu.%d", num, &point);
		if (result == 1 && point == 0) {
			if (!checkFunction(*num)) {
				printf("Вы ввели число, неподходящее под условие!\n");
				printf("Попробуйте ещё раз.\n");
				result = 0;
			}
		} else if (result == 0 || result == 2 || point != 0) {
			printf("Вы ввели целое число некорректно!\n");
			printf("Попробуйте ещё раз.\n");
			result = 0;
			point = 0;
		}
		scanf("%*[^\n]");
	} while(result == 0);
	return result;
}
