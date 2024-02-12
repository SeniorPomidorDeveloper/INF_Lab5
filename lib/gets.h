#ifndef GETS_H
#define GETS_H

unsigned short int standartCheckLLInt(const long long int);
unsigned short int standartCheckULLInt(const unsigned long long int);

short int getLLInt(long long int *, const char *, unsigned short int (*)(const long long int));
short int getULLInt(unsigned long long int *, const char *, unsigned short int (*)(const unsigned long long int));

#endif
