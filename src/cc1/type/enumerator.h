#ifndef BCC_ENUMERATOR_H
#define BCC_ENUMERATOR_H

#include <stdbool.h>

struct enumerator;

#include "../expression/expression.h"

struct enumerator {
    const char *identifier;
    const struct expression *expr;
};

struct enumerator *enumerator_new(const char *name, const struct expression *constant_expr);

#endif // BCC_ENUMERATOR_H
