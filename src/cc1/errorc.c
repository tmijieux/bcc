#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


#include "type/type.h"

#include "scanner.h"
#include "parser.tab.h"

#include "util/error.h"
#include "util/color.h"
#include "util/string2.h"

#include "errorc.h"

extern int yycolno, yylineno;
extern char *yytext, *yyfilename;
extern const char *old_yytext[];
extern unsigned int old_yytext_index;
static int errc = 0;

int error_count(void)
{
    return errc;
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


