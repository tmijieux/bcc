#include "constant.h"
#include "type.h"

static struct constant *constant_new(void)
{
    return calloc(sizeof*cst, 1);
}

static struct constant *constant_str_integer(const char *string)
{
    long value = 0;
    struct constant *cst = NULL;
    
    value = strtol(string, NULL, 0);
    cst = constant_new();
    cst->type = type_long;
    cst->integer->longv.signed_ = value;
    
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
    char *str = strdup(string);

    const struct type *char_type = type_get("char");
    cst->type = type_get_pointer_type(char_type);
    
    struct constant *cst;
    cst->stringv = str;
    return cst;
}
