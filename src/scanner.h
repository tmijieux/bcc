#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>

#define YYOLDTEXT_SIZE 15

extern FILE *yyin;
int yylex(void);

#endif //SCANNER_H
