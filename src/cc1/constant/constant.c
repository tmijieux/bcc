#include <string.h>

#include "./constant.h"
#include "./string_literal.h"
#include "../type/type.h"
#include "../util/error.h"

static struct constant *constant_new(enum constant_type type)
{
    struct constant *c;
    c = calloc(sizeof*c, 1);
    c->constant_type = type;
    return c;
}

static struct constant *constant_str_integer(const char *string)
{
    long value = 0;
    struct constant *cst = NULL;

    value = strtol(string, NULL, 0);
    cst = constant_new(CONSTANT_INT);
    cst->type = type_int;
    cst->integer.longv.signed_ = value;

    return cst;
}

struct constant *constant_hex_integer(const char *string)
{
    return constant_str_integer(string);
}

struct constant *constant_oct_integer(const char *string)
{
    return constant_str_integer(string);
}

struct constant *constant_dec_integer(const char *string)
{
    return constant_str_integer(string);
}

struct constant *constant_string_literal(const char *string)
{
    struct constant *cst = NULL;
    struct literal *lit = NULL;
    char *str = strdup(string);

    cst = constant_new(CONSTANT_STRING);
    struct pointer *ptr = pointer_new(list_new(0), NULL);

    cst->type = type_get_pointer_type(ptr, type_char);
    lit = string_get_or_create_literal(str);
    cst->stringv = lit->value;
    cst->strliteral = lit;

    return cst;
}

struct constant *constant_integer_long(long integer)
{
    struct constant *cst = NULL;

    cst = constant_new(CONSTANT_LONG);
    cst->type = type_long;
    cst->integer.longv.signed_ = integer;
    return cst;
}


struct constant *constant_integer_int(int integer)
{
    struct constant *cst = NULL;

    cst = constant_new(CONSTANT_INT);
    cst->type = type_int;
    cst->integer.intv.signed_ = integer;
    return cst;
}

struct constant *constant_floating_point(const char *input_string)
{
    struct constant *cst = constant_new(CONSTANT_FLOAT);
    size_t len = strlen(input_string);
    if (input_string[len-1] == 'f'
        || input_string[len-1] == 'F')
    {
        cst->type = type_float;
        cst->floatv = strtof(input_string, NULL);
    }
    else
    {
        cst->constant_type = CONSTANT_DOUBLE;
        cst->type = type_double;
        cst->floatv = strtod(input_string, NULL);
    }
    return cst;
}

