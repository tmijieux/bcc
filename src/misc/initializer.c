#include <stdlib.h>
#include "initializer.h"

enum initializer_type {
    INITIALIZER_UNEXPECTED_ERROR = 0,
    INITIALIZER_EXPRESSION = 22,
    INITIALIZER_LIST,
};

struct initializer {
    enum initializer_type initializer_type;

    union initializer_value {
        const struct expression *expression;
        const struct list *initializer_list;
    } value;
};

static struct initializer *initializer_new(enum initializer_type initializer_type)
{
    struct initializer *i = calloc(sizeof*initializer_new, 1);
    i->initializer_type = initializer_type;
    return i;
}

struct initializer *
initializer_expression(const struct expression *expression)
{
    struct initializer *i = initializer_new(INITIALIZER_EXPRESSION);
    i->value.expression = expression;
    return i;
}

struct initializer *
initializer_list(const struct list *initializer_list)
{
    struct initializer *i = initializer_new(INITIALIZER_LIST);
    i->value.initializer_list = initializer_list;
    return i;
}
