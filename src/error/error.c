#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "error.h"
#include "../scanner.h"
#include "../grammar.tab.h"
#include "../util/color.h"
#include "../util/string2.h"

extern int yycolno, yylineno;
extern char *yytext, *yyfilename;

static char *program_name;

static int errc = 0;

int error_count(void)
{
    return errc;
}

void error_set_program_name(const char *program_name_)
{
    program_name = strdup(program_name_);
}

/* compilation start */

static void
compile_error_(const char *format, va_list ap, const char *error_type)
{
    fprintf(ERROR_OUTPUT, "%s:%d:%d: %s ",
            yyfilename, yylineno, yycolno,  error_type);
    vfprintf(ERROR_OUTPUT, format, ap);
}

void warning(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    compile_error_(format, ap, color("warning", "warning:"));
}

void error(const char *format, ...)
{
    errc++;
    va_list ap;
    va_start(ap, format);
    compile_error_(format, ap, color("error", "error:"));
}

void fatal_error(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    compile_error_(format, ap, color("error", "fatal error:"));
    exit(EXIT_FAILURE);
}

/* compilation end */
/* internal start */

static void
internal_error_(const char *format, va_list ap, const char *error_type)
{
    fprintf(ERROR_OUTPUT, "%s: %s ", program_name, error_type);
    vfprintf(ERROR_OUTPUT, format, ap);
}

void internal_warning(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    internal_error_(format, ap, color("warning", "warning:"));
}

void internal_error(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    internal_error_(format, ap, color("error", "error:"));
}

void internal_fatal_error(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    internal_error_(format, ap, color("error", "fatal error:"));
    exit(EXIT_FAILURE);
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
    int len = 0 ;
    errc++;
    fflush(stdout);
    fprintf(ERROR_OUTPUT, "%s:%d:%d: %s\n",
	    yyfilename, yylineno, yycolno, color("error", s));
//    len = fprintf(ERROR_OUTPUT, "near ");
    
    char *source_code = "";
    for (int i = old_yytext_index + 1 % YYOLDTEXT_SIZE;
	 i != old_yytext_index; i = (i + 1) % YYOLDTEXT_SIZE) {
	asprintf(&source_code, "%s%s", source_code, old_yytext[i]);
    }
    asprintf(&source_code, "%s%s", source_code, yytext);
    
    len +=
	fprintf(ERROR_OUTPUT, "\t%s\n",
		strstrip(color("green", source_code))) - COLOR_LEN;

    char *pointer = "\t";
    for (int i = 0; i < len - 3; ++i)
	asprintf(&pointer, "%s ", pointer);

    fputs(color("fushia", pointer), ERROR_OUTPUT);
    fputs(color("fushia", "^\n"), ERROR_OUTPUT);
    
    return 0;
}


