#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "scanner.h"
#include "color.h"
#include "error.h"
#include "util/string2.h"

extern int yycolno, yylineno;
extern char *yytext, *yyfilename;

static int errc = 0;

enum error {
    ERR_COMPILATION,
    ERR_OTHER
};

static void
error_(enum error errt, const char *format, va_list ap, const char *error_type)
{
    fprintf(ERROR_OUTPUT, "%s: ", yyfilename);
    if (ERR_COMPILATION == errt)
	fprintf(ERROR_OUTPUT, "%d:%d: ", yylineno, yycolno);
    fprintf(ERROR_OUTPUT, "%s: ", error_type);
    vfprintf(ERROR_OUTPUT, color("light blue", format), ap);
}

int error_count(void)
{
    return errc;
}

void warning(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    error_(ERR_COMPILATION, format, ap, color("yellow", "warning"));
}

void error(const char *format, ...)
{
    errc++;
    va_list ap;
    va_start(ap, format);
    error_(ERR_COMPILATION, format, ap, color("red", "error"));
}

static void fatal_error__(int error_type, const char *format, va_list ap)
{
    ++errc;
    error_(error_type, format, ap, color("red", "fatal error"));
    exit(EXIT_FAILURE);
}

void fatal_error(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    fatal_error__(ERR_COMPILATION, format, ap);
}

void internal_error(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    fatal_error__(ERR_OTHER, format, ap);
}


void debugi(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
}

extern const char *old_yytext[];
extern unsigned int old_yytext_index;

int yyerror(const char *s)
{
    int len;
    errc++;
    fflush(stdout);
    fprintf(ERROR_OUTPUT, "%s:%d:%d: %s\n",
	    yyfilename, yylineno, yycolno, color("red", s));
    len = fprintf(ERROR_OUTPUT, "near ");

    char *source_code = "";
    for (int i = old_yytext_index + 1 % YYOLDTEXT_SIZE;
	 i != old_yytext_index; i = (i + 1) % YYOLDTEXT_SIZE) {
	asprintf(&source_code, "%s%s", source_code, old_yytext[i]);
    }
    asprintf(&source_code, "%s%s", source_code, yytext);
    len +=
	fprintf(ERROR_OUTPUT, "%s\n",
		strstrip(color("green", source_code))) - COLOR_LEN;
    for (int i = 0; i < len - 2; ++i)
	fputc(' ', ERROR_OUTPUT);
    fputs(color("fushia", "^\n"), ERROR_OUTPUT);
    return 0;
}
