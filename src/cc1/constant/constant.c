#include <string.h>
#include "constant.h"
#include "string_literal.h"
#include "../type/type.h"
#include "../util/error.h"

static struct constant *constant_new(void)
{
    struct constant *c;
    c = calloc(sizeof*c, 1);
    return c;
}

static struct constant *constant_str_integer(const char *string)
{
    long value = 0;
    struct constant *cst = NULL;

    value = strtol(string, NULL, 0);
    cst = constant_new();
    cst->type = type_long;
    cst->integer.longv.signed_ = value;

    return cst;
}

struct constant *make_constant(const char *string)
{
    return constant_str_integer(string);
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

    cst = constant_new();
    struct pointer *ptr = pointer_new(list_new(0), NULL);
    cst->type = type_get_pointer_type(ptr, type_char);
    lit = string_get_or_create_literal(str);
    cst->stringv = lit->value;
    return cst;
}

struct constant *constant_integer_long(long integer)
{
    struct constant *cst = NULL;

    cst = constant_new();
    cst->type = type_long;
    cst->integer.longv.signed_ = integer;
    return cst;
}


struct constant *constant_integer_int(int integer)
{
    struct constant *cst = NULL;

    cst = constant_new();
    cst->type = type_int;
    cst->integer.intv.signed_ = integer;
    return cst;
}


bool constant_is_zero(const struct constant *cst)
{
    internal_warning("constant_is_zero not implemented");
    return true;
}
