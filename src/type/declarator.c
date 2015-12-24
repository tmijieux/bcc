
#include <stdbool.h>
#include <stdlib.h>
#include "declarator.h"


enum declarator_type {
    DECLARATOR_UNEXPECTED_ERROR = 0,
    DECLARATOR_IDENTIFIER = 58,
    DECLARATOR_ARRAY,
    DECLARATOR_POINTER,
    DECLARATOR_FUNCTION,
    DECLARATOR_FUNCTION_OLD, // old style
    DECLARATOR_STRUCT_FIELD,
    DECLARATOR_SPECIFIER,
    DECLARATOR_INITIALIZER,
};

struct declarator {
    enum declarator_type declarator_type;

    union declarator_value {
        const char *identifier;
        const struct list *declaration_specifiers;
        const struct list *parameter_list;
        const struct list *identifier_list;
        struct pointer *pointer;
        const struct expression *const_expr_array_size;
        const struct expression *const_expr_bitcount;
        struct initializer *initializer;
    } value;
        
    const struct type *type;
    struct declarator *next;
};


static struct declarator *declarator_new(enum declarator_type dt,
                                         struct declarator *next)
{
    struct declarator *d = calloc(sizeof*d, 1);
    d->declarator_type = dt;
    d->next = next;
    return d;
}

bool declarator_is_abstract(const struct declarator *de)
{
    return ((DECLARATOR_IDENTIFIER != de->declarator_type) &&
            (NULL == de->next));
}

struct declarator *
declarator_identifier(const char *identifier)
{
    struct declarator *d = declarator_new(DECLARATOR_IDENTIFIER, NULL);
    d->value.identifier = identifier;
    return d;
}

struct declarator *
declarator_pointer(struct declarator *de, struct pointer *ptr)
{
    struct declarator *d = declarator_new(DECLARATOR_POINTER, de);
    d->value.pointer = ptr;
    return d;
}

struct declarator *
declarator_array(struct declarator *de,
                 const struct expression *const_expr_array_size)
{
    struct declarator *d = declarator_new(DECLARATOR_ARRAY, de);
    d->value.const_expr_array_size = const_expr_array_size;
    return d;
}

struct declarator *
declarator_function(struct declarator *de, struct list *parameter_list)
{
    struct declarator *d = declarator_new(DECLARATOR_FUNCTION, de);
    d->value.parameter_list = parameter_list;
    return d;
}


struct declarator *
declarator_function_old(struct declarator *de, struct list *identifier_list)
{
    struct declarator *d = declarator_new(DECLARATOR_FUNCTION_OLD, de);
    d->value.identifier_list = identifier_list;
    return d;
}

struct declarator*
declarator_struct_field(struct declarator *de,
                        const struct expression *const_expr_bitcount)
{
    struct declarator *d = declarator_new(DECLARATOR_STRUCT_FIELD, de);
    d->value.const_expr_bitcount = const_expr_bitcount;
    return d;
}

struct declarator*
declarator_specifier(struct declarator *de,
                     const struct list *declaration_specifiers)
{
    struct declarator *d = declarator_new(DECLARATOR_SPECIFIER, de);
    d->value.declaration_specifiers = declaration_specifiers;
    return d;
}

struct declarator*
declarator_initializer(struct declarator *de,
                       struct initializer *initializer)
{
    struct declarator *d = declarator_new(DECLARATOR_SPECIFIER, de);
    d->value.initializer = initializer;
    return d;
}
