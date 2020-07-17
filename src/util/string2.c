#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "./string2.h"

#define HEURISTIC_SIZE 11

char *strdup(const char *s)
{
    char *d = calloc(strlen(s) + 1, 1);
    strcpy(d, s);
    return d;
}

int asprintf(char **strp, const char *fmt, ...)
{
    va_list ap;

    char *buf = calloc(HEURISTIC_SIZE, 1);

    va_start(ap, fmt);
    int n = vsnprintf(buf, HEURISTIC_SIZE, fmt, ap);
    if (n >= HEURISTIC_SIZE) {
	buf = realloc(buf, n + 1);
	va_start(ap, fmt);	// important !!
	vsnprintf(buf, n + 1, fmt, ap);
    }

    *strp = buf;
    return n;
}

char *strstrip(const char *input_str)
{
    char *str = strdup(input_str);
    size_t len = strlen(str);
    if (len == 0)
    {
        return str;
    }

    if (str[len - 1] == '\n')
    {
	str[len - 1] = '\0';
    }

    for (unsigned i = 0; i < len - 1; ++i)
    {
	if (str[i] == '\t')
        {
	    str[i] = ' ';
        }
    }
    return str;
}

char *strstrip2(const char *input_str)
{
    char *str = strdup(input_str);
    size_t len = strlen(str);
    if (len == 0)
    {
        return str;
    }

    if (str[len - 1] == '"')
    {
	str[len - 1] = '\0';
    }

    return str;
}
