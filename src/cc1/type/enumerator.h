#ifndef ENUMERATOR_H
#define ENUMERATOR_H


struct enumerator;

#include <stdbool.h>
#include "../expression/expression.h"

struct enumerator {
    
};

struct enumerator *enumerator_new(const char *name, bool have_value,
                                  const struct expression *const_expr);

#endif //ENUMERATOR_H
