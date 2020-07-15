#ifndef BCC_ENUMERATOR_H
#define BCC_ENUMERATOR_H

#include <stdbool.h>

struct enumerator;

#include "../expression/expression.h"

struct enumerator {};

struct enumerator *enumerator_new(const char *name,
                                  bool have_value,
                                  const struct expression *const_expr);

#endif // BCC_ENUMERATOR_H
