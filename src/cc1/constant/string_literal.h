#ifndef BCC_STRING_LITERAL_H
#define BCC_STRING_LITERAL_H

struct literal {
    char *reg;
    char *value;
    size_t length;
};

#include "../util/list.h"

struct literal *string_get_or_create_literal(const char *literal);
struct list *string_get_literals_list(void);

#endif // BCC_STRING_LITERAL_H
