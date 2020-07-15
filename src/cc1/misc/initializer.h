#ifndef BCC_INITIALIZER_H
#define BCC_INITIALIZER_H

struct initializer;

#include "../expression/expression.h"
#include "../util/list.h"

struct initializer *
initializer_expression(const struct expression *expression);

struct initializer *
initializer_list(const struct list *initializer_list);

#endif // BCC_INITIALIZER_H
