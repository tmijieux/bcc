#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "./error.h"
#include "./color.h"
#include "./string2.h"

static const char *program_name;

void error_set_program_name(const char *program_name_)
{
    program_name = color("bold", basename(strdup(program_name_)));
}

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
