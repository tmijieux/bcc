#include <stdlib.h>

#include "../util/error.h"
#include "./enumerator.h"

#include "../errorc.h"


struct enumerator *enumerator_new(const char *name, const struct expression *const_expr)
{
    struct enumerator *enumerator = calloc(sizeof*enumerator, 1);
    if (const_expr && const_expr->expression_type != EXPR_CONSTANT)
    {
        error("expression must be contant in enum");
    }
    enumerator->expr = const_expr;
    enumerator->identifier = name;
    return enumerator;
}
